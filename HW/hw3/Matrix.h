#ifndef __Matrix_h_
#define __Matrix_h_
#include <ostream>
#include <iostream>
#include <vector>

class Matrix{
public:
    //Constructors
    Matrix();
    Matrix(const Matrix& b);
    Matrix(unsigned int Rows, unsigned int Columns, double fill);

    ~Matrix();

    unsigned int num_rows() const;
    unsigned int num_cols() const;
    double** get_matrix() const;

    bool get(unsigned int row, unsigned int column, double& value) const;

    double* get_row(unsigned int row) const;
    double* get_column(unsigned int column) const;
    Matrix* quarter() const;

    void clear();

    bool set(unsigned int row, unsigned int column, double value);

    void multiply_by_coefficient(double coefficient);

    bool swap_row(unsigned int row1, unsigned int row2);

    void transpose();

    bool add(const Matrix& b);

    bool subtract(const Matrix& b);

    Matrix& operator=(const Matrix& m);


private:
    unsigned int rows;
    unsigned int columns;
    double** matrix;

};

bool operator== (const Matrix& m1, const Matrix& m2);

bool operator!= (const Matrix& m1, const Matrix& m2);

std::ostream& operator<< (std::ostream& out, const Matrix& m);

#endif