scicore_add_exercises(ch01_math)

# test_saturate.cpp uses std::saturate_cast — requires C++26
target_compile_features(ch01_math_test_saturate PRIVATE cxx_std_26)
