#include "Matrix.h"

using std::endl; using std::vector;

Matrix::Matrix(){
    rows = 0;
    columns = 0;
}
Matrix::Matrix(unsigned int Rows, unsigned int Columns, double fill){
    if (Rows == 0 || Columns == 0){
        rows = 0;
        columns = 0;
    } else {
        rows = Rows;
        columns = Columns;
        matrix = new double*[rows];
        for (unsigned int i = 0; i < rows; i++){
            matrix[i] = new double[columns];
        }
        for (unsigned int i = 0; i < rows; i++){
            for (unsigned int j = 0; j < columns; j++){
                matrix[i][j] = fill;
            }
        }
    }
}
unsigned int Matrix::num_rows() const {
    return rows;
}
unsigned int Matrix::num_cols() const {
    return columns;
}
double** Matrix::get_matrix() const {
    return matrix;
}
bool Matrix::get(unsigned int row, unsigned int column, double& value) const {
    if ((row >= 0 && row < rows) && (column >= 0 && column < columns)){
        value = matrix[row][column];
        return true;
    } else {
        return false;
    }
}
double* Matrix::get_row(unsigned int row) const{
    if (row >= 0 && row < rows){
        double* row_values = new double[rows];
        for (unsigned int i = 0; i < rows; i++){
            row_values[i] = matrix[row][i];
        }
        return row_values;
    } else {
        double* row_values = NULL;
        return row_values;
    }
}
double* Matrix::get_column(unsigned int column) const {
    if (column >= 0 && column < columns){
        double* column_values = new double[columns];
        for (unsigned int i = 0; i < columns; i++){
            column_values[i] = matrix[i][column];
        }
        return column_values;
    } else {
        double* column_values = NULL;
        return column_values;
    }
}
Matrix* Matrix::quarter() const{
    Matrix* all_matrix = new Matrix[4];

    
}

void Matrix::clear() {
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    rows = 0;
    columns = 0;
}
bool Matrix::set(unsigned int row, unsigned int column, double value){
    if ((row >= 0 && row < rows) && (column >= 0 && column < columns)){
        matrix[row][column] = value;
        return true;
    } else {
        return false;
    }
}
void Matrix::multiply_by_coefficient(double coefficient){
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            matrix[i][j] = matrix[i][j] * coefficient;
        }
    }
}
bool Matrix::swap_row(unsigned int row1, unsigned int row2){
    if ((row1 >= 0 && row1 < rows) && (row2 >= 0 && row2 < rows)){
        vector<double> swap1;
        vector<double> swap2;
        for (unsigned int i = 0; i < columns; i++){
            swap1.push_back(matrix[row1][i]);
            swap2.push_back(matrix[row2][i]);
        }
        for (unsigned int i = 0; i < swap1.size(); i++){
            matrix[row2][i] = swap1[i];
        }
        for (unsigned int i = 0; i < swap2.size(); i++){
            matrix[row1][i] = swap2[i];
        }
        return true;
    } else {
        return false;
    }
}
void Matrix::transpose(){
    unsigned int new_rows = columns;
    unsigned int new_columns = rows;
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    double** new_matrix = new double*[new_rows];
    for (unsigned int i = 0; i < new_rows; i++){
        new_matrix[i] = new double[new_columns];
    }
    
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            new_matrix[j][i] = matrix[i][j];
        }
    }
}
bool Matrix::add(const Matrix& b){
    if (rows == b.rows && columns == b.columns){
        for (unsigned int i = 0; i < rows; i++){
            for (unsigned int j = 0; j < columns; j++){
                matrix[i][j] == matrix[i][j] + b.matrix[i][j];
            }
        }
        return true;
    } else {
        return false;
    }
}
bool Matrix::subtract(const Matrix& b){
    if (rows == b.rows && columns == b.columns){
        for (unsigned int i = 0; i < rows; i++){
            for (unsigned int j = 0; j < columns; j++){
                matrix[i][j] == matrix[i][j] - b.matrix[i][j];
            }
        }
        return true;
    } else {
        return false;
    }
}

bool operator== (const Matrix& m1, const Matrix& m2){
    if (m1.rows != m2.rows || m1.columns != m2.columns){
        return false;
    } else {
        for (unsigned int i = 0; i < m1.rows; i++){
            for (unsigned int j = 0; j < m1.columns; j++){
                if (m1.matrix[i][j] != m2.matrix[i][j]){
                    return false;
                }
            }
        }
    }
    return true;
}
bool operator!= (const Matrix& m1, const Matrix& m2){
    if (m1.rows != m2.rows || m1.columns != m2.columns){
        return true;
    } else {
        for (unsigned int i = 0; i < m1.rows; i++){
            for (unsigned int j = 0; j < m1.columns; j++){
                if (m1.matrix[i][j] != m2.matrix[i][j]){
                    return true;
                }
            }
        }
    }
    return false;
}
std::ostream& operator<< (std::ostream& out, const Matrix& m){
    out << m.rows << " x " << m.columns << endl;
    out << "[ ";
    for (unsigned int i = 0; i < m.rows; i++){
        for (unsigned int j = 0; j < m.columns; j++){
            if (j == 0 && i != 0){
                out << "  ";
            }

            out << m.matrix[i][j] << " ";

            if (i == m.rows-1 && j == m.columns-1 ){
                out << "]";
            }
        }
        out << endl;
    }
    return out;
}