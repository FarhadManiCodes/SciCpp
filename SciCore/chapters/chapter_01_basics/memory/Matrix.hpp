#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cstddef>
#include <stdexcept>

// -----------------------------------------------------------------------------
// LIBRARY CONFIGURATION
// -----------------------------------------------------------------------------
// We use the path exactly as shown in your file tree:
#pragma GCC system_header 
#include <experimental/mdspan> 

namespace Scientific {
    // mdspan is in std::experimental (reference impl), dextents is in std:: (C++23)
    using std::experimental::mdspan;
    using std::dextents;
    using std::experimental::layout_right;

    // Define the View Type
    using MatrixView = mdspan<double, std::dextents<size_t, 2>>;
}

// -----------------------------------------------------------------------------
// MATRIX CLASS (Safe Wrapper)
// -----------------------------------------------------------------------------
class Matrix {
private:
    std::vector<double> data;
    size_t rows_;
    size_t cols_;

public:
    Matrix(size_t rows, size_t cols) 
        : rows_(rows), cols_(cols) 
    {
        data.resize(rows * cols); 
    }

    // High-Performance View (Read-Write)
    auto view() {
        return Scientific::mdspan<double, Scientific::dextents<size_t, 2>>(
            data.data(), rows_, cols_
        );
    }

    // Read-Only View
    auto view() const {
        return Scientific::mdspan<const double, Scientific::dextents<size_t, 2>>(
            data.data(), rows_, cols_
        );
    }

    // Safe Accessor (Bounds Checked)
    double& operator()(size_t i, size_t j) {
        if (i >= rows_ || j >= cols_) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i * cols_ + j];
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }
};

#endif // MATRIX_HPP
