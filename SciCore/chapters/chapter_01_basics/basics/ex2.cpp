#include <cxxabi.h>  // for __cxa_demangle

#include <cstdlib>  // for std::free
#include <print>    // C++23
#include <typeinfo>

// The helper to get the "Pretty Name"
std::string get_type_name(const char* mangled_name) {
  int status= 0;
  char* demangled= abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
  std::string result= (status == 0) ? demangled : mangled_name;
  std::free(demangled);
  return result;
}

int main() {
  // 1. The variable in question
  auto my_size= 100uz;

  // 2. Get the raw info
  const auto& info= typeid(my_size);

  // 3. Print both columns
  std::println("Variable Value: {}", my_size);
  std::println("---------------------------------");
  std::println("Raw Compiler ID : {}", info.name());  // The "Mangled" ID
  std::println("Human Type Name : {}", get_type_name(info.name()));

  return 0;
}
