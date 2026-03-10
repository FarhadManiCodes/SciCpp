#include <memory>
#include <print>  // C++23: Replaces iostream for printing
#include <string>
#include <type_traits>
#include <utility>  // for std::move

// The Object
struct Baton {
  int id;
  // Format string syntax: "{}" is a placeholder
  Baton(int i) : id(i) { std::println("  [Baton] Created ID: {}", id); }
  ~Baton() { std::println("  [Baton] Dropped ID: {}", id); }
};

// The Runner
struct Runner {
  std::string name;
  std::unique_ptr<Baton> my_baton;

  // 1. Constructor
  // Note: We still keep 'noexcept' because string moves are safe.
  Runner(std::string n) : name(std::move(n)) {}

  // 2. The Move-Assignment Logic
  // STRICTNESS CHECK: We are printing inside a noexcept function.
  // In production (Release mode), we would remove the print.
  // For learning (Debug mode), this is acceptable.
  void take_baton(std::unique_ptr<Baton> incoming_baton) {
    std::println("{} grabs the baton!", name);
    my_baton= std::move(incoming_baton);
  }

  void check_hands() const {
    if (my_baton) {
      std::println("{} HAS the baton (ID: {}).", name, my_baton->id);
    } else {
      std::println("{} is empty-handed.", name);
    }
  }
};

int main() {
  std::println("Is Runner move-safe? {}", std::is_nothrow_move_constructible<Runner>::value);
  // Put this anywhere in your code.
  // If Runner is NOT noexcept, the build will fail immediately with this error message.
  static_assert(std::is_nothrow_move_constructible<Runner>::value,
                "CRITICAL ERROR: Runner must be noexcept for HPC performance!");

  Runner runner1("Bolt");
  Runner runner2("Powell");
  std::println("--- The Race Begins ---");
  runner1.take_baton(std::make_unique<Baton>(99));

  runner1.check_hands();
  runner2.check_hands();

  std::println("\n--- The Handoff ---");
  // The Move
  runner2.take_baton(std::move(runner1.my_baton));

  runner1.check_hands();
  runner2.check_hands();

  std::println("\n--- Race Over ---");
  return 0;
}
