#include <expected>
#include <memory>
#include <print>
#include <string>
#include <utility>

class Particle {
 private:
  int m_id;
  double m_energy;

  // 1. UNIQUE OWNERSHIP
  // Only THIS particle owns the next one. No sharing.
  // Zero overhead compared to a raw pointer.
  std::unique_ptr<Particle> m_next_decay;

  inline static int particle_count= 0;

  // Private constructor
  // Note: We take 'next' by VALUE (transferring ownership in)
  Particle(int id, double energy, std::unique_ptr<Particle> next)
      : m_id{id}, m_energy{energy}, m_next_decay{std::move(next)} {
    particle_count++;
  }

 public:
  struct Error {
    std::string message;
  };

  // 2. MODERN FACTORY
  // Returns a unique_ptr. You either get the whole valid object, or nothing.
  static std::expected<std::unique_ptr<Particle>, Error> create(
      int id, double energy, std::unique_ptr<Particle> next= nullptr) {
    if (energy < 0.0) {
      return std::unexpected(Error{"Physics Error: Energy cannot be negative."});
    }
    // std::make_unique is safer and cleaner than 'new'
    // We must use 'new' here only because the constructor is private.
    // But since unique_ptr doesn't have a control block, 'new' is fine here.
    return std::unique_ptr<Particle>(new Particle(id, energy, std::move(next)));
  }

  // Destructor (Virtual if we expected inheritance, but kept simple here)
  ~Particle() {
    // Recursive destruction happens automatically!
    // Destroying p1 -> destroys m_next_decay (p2) -> destroys p3...
    particle_count--;
  }

  // 3. OBSERVING POINTERS (The Critical Change)
  // We do NOT return the unique_ptr (that would transfer ownership).
  // We return a RAW pointer for "looking only".
  // This is safe because the parent (self) stays alive while we look.

  Particle* next() const { return m_next_decay.get(); }
  double energy() const { return m_energy; }
  int id() const { return m_id; }

  static int get_count() { return particle_count; }

  void print_info() const {
    std::print("Particle[ID={}]: E={} GeV", m_id, m_energy);
    if (m_next_decay) {
      std::println(" -> decays to ID={}", m_next_decay->m_id);
    } else {
      std::println(" (Stable)");
    }
  }
};

int main() {
  std::println("--- Simulation Start. Count: {} ---", Particle::get_count());

  // 4. BUILDING THE CHAIN (Monadic Move)
  // We build backwards: p3 -> p2 -> p1
  // Each step MOVES the previous pointer into the new one.

  auto chain_result= Particle::create(3, 0.5)  // Create p3
                         .and_then([](auto p3) {
                           // Move p3 into p2
                           return Particle::create(2, 1.5, std::move(p3));
                         })
                         .and_then([](auto p2) {
                           // Move p2 into p1
                           return Particle::create(1, 5.0, std::move(p2));
                         });

  if (chain_result) {
    // We now own the HEAD of the chain (p1)
    // p1 owns p2, p2 owns p3.
    std::unique_ptr<Particle> head= std::move(*chain_result);

    std::println("Chain built. Count: {}", Particle::get_count());

    // 5. TRAVERSAL (Using Raw Pointers)
    // We use raw pointers to walk the chain without taking ownership.

    Particle* current= head.get();  // Start at p1

    while (current != nullptr) {
      current->print_info();
      current= current->next();  // Hop to next (raw pointer)
    }

  } else {
    std::println("Error: {}", chain_result.error().message);
  }

  // End of Scope: 'head' is destroyed.
  // It triggers a chain reaction: ~p1 -> ~p2 -> ~p3.
  // All memory is freed instantly.

  std::println("--- Simulation End. Count: {} ---", Particle::get_count());
  return 0;
}
