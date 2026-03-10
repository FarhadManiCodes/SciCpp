#include <print>
#include <string>

int main() {
  const int iteration= 42;
  const double residual= 1.23456789e-8;
  const double runtime= 120.5;
  const std::string solver= "GMRES";

  // Header with alignment
  // {:<10} -> Left align, width 10
  // {:>10} -> Right align, width 10
  std::print("{:<10} | {:>10} | {:>15} | {:>10}\n", "Method", "Iter",
             "Residual", "Time (s)");
  std::print("{:-<52}\n", ""); // Separator line using fill character '-'

  // Data row
  // {:.3e}  -> Scientific notation, 3 decimal places
  // {:.2f}  -> Fixed point, 2 decimal places
  std::print("{:<10} | {:>10d} | {:>15.3e} | {:>10.2f}\n", solver, iteration,
             residual, runtime);
  std::print("Decimal :\t{} {} {:06} {} {:0} {:+} {:d}\n", 1, 2, 3, 0, 0, 4,
             -1);

  return 0;
}
