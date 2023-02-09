#include "Matrix.h"

using std::endl; using std::vector;

Matrix::Matrix(){
    rows = 0;
    columns = 0;
}
Matrix::Matrix(const Matrix& b){
    rows = b.rows;
    columns = b.columns;
    matrix = new double*[rows];
    for (unsigned int i = 0; i < rows; i++){
        matrix[i] = new double[columns];
        for (unsigned int j = 0; j < columns; j++){
            matrix[i][j] = b.matrix[i][j];
        }
    }
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
Matrix::~Matrix(){
    clear();
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
        double* row_values = new double[columns];
        for (unsigned int i = 0; i < columns; i++){
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
        double* column_values = new double[rows];
        for (unsigned int i = 0; i < rows; i++){
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
    unsigned int row_size;
    unsigned int column_size;
    if (rows == 1 && columns == 1){
        Matrix all(1,1,0);
        all.set(0,0,matrix[0][0]);
        all_matrix[0] = all;
        all_matrix[1] = all;
        all_matrix[2] = all;
        all_matrix[3] = all;
        return all_matrix;
    }
    if (rows == 1){
        row_size = 1;
        if (columns%2 == 0){
            column_size = columns / 2;
        } else {
            column_size = (columns/2) + 1;
        }
        Matrix upper_left(row_size, column_size, 0);
            for (unsigned int j = 0; j < column_size; j++){
                upper_left.set(0,j,matrix[0][j]);
            }
        all_matrix[0] = upper_left;
        all_matrix[2] = upper_left;

        if (columns%2 == 0){
            Matrix upper_right(row_size,column_size,0);
                for (unsigned int j = (column_size); j < (column_size)+column_size; j++){
                    upper_right.set(0,j-column_size,matrix[0][j]);
                }
            all_matrix[1] = upper_right;
            all_matrix[3] = upper_right;
        } else {
            Matrix upper_right(row_size,column_size,0);
                for (unsigned int j = (column_size-1); j < (column_size-1)+column_size; j++){
                    upper_right.set(0,j-column_size+1,matrix[0][j]);
                }
            all_matrix[1] = upper_right;
            all_matrix[3] = upper_right;
        }
        return all_matrix;
    } 

    if (columns == 1){
        column_size = 1;
        if (rows%2 == 0){
            row_size = rows / 2;
        } else {
            row_size = (rows/2) + 1;
        }

        Matrix upper_left(row_size, column_size, 0);
        for (unsigned int i = 0; i < row_size; i++){
            upper_left.set(i,0,matrix[i][0]);
        }
        all_matrix[0] = upper_left;
        all_matrix[1] = upper_left;

        if (rows%2 == 0){
            Matrix lower_left(row_size,column_size,0);
            for (unsigned int i = (row_size); i < (row_size+row_size); i++){
                lower_left.set(i-row_size,0,matrix[i][0]);
            }
            all_matrix[2] = lower_left;
            all_matrix[3] = lower_left;
        } else {
            Matrix lower_left(row_size,column_size,0);
            for (unsigned int i = (row_size-1); i < (row_size-1+row_size); i++){
                lower_left.set(i-row_size+1,0,matrix[i][0]);
            }
            all_matrix[2] = lower_left;
            all_matrix[3] = lower_left;
        }
        return all_matrix;
    }

    if (rows%2 == 0){
        row_size = rows / 2;
    } else {
        row_size = (rows/2) + 1;
    }
    if (columns%2 == 0){
        column_size = columns / 2;
    } else {
        column_size = (columns/2) + 1;
    }
    
    Matrix upper_left(row_size, column_size, 0);
    for (unsigned int i = 0; i < row_size; i++){
        for (unsigned int j = 0; j < column_size; j++){
            upper_left.set(i,j,matrix[i][j]);
        }
    }
    all_matrix[0] = upper_left;

    if (columns%2 == 0){
        Matrix lower_left(row_size,column_size,0);
        for (unsigned int i = 0; i < row_size; i++){
            for (unsigned int j = (column_size); j < (column_size)+column_size; j++){
                lower_left.set(i,j-column_size,matrix[i][j]);
            }
        }
        all_matrix[1] = lower_left;
    } else {
        Matrix lower_left(row_size,column_size,0);
        for (unsigned int i = 0; i < row_size; i++){
            for (unsigned int j = (column_size-1); j < (column_size-1)+column_size; j++){
                lower_left.set(i,j-column_size+1,matrix[i][j]);
            }
        }
        all_matrix[1] = lower_left;
    }
     
    if (rows%2 == 0){
        Matrix upper_right(row_size,column_size,0);
        for (unsigned int i = (row_size); i < (row_size+row_size); i++){
            for (unsigned int j = 0; j < column_size; j++){
                upper_right.set(i-row_size,j,matrix[i][j]);
            }
        }
        all_matrix[2] = upper_right;
    } else {
        Matrix upper_right(row_size,column_size,0);
        for (unsigned int i = (row_size-1); i < (row_size-1+row_size); i++){
            for (unsigned int j = 0; j < column_size; j++){
                upper_right.set(i-row_size+1,j,matrix[i][j]);
            }
        }
        all_matrix[2] = upper_right;
    }

    if (rows%2 == 0 && columns%2 == 0){
         Matrix lower_right(row_size, column_size, 0);
        for (unsigned int i = (row_size); i < (row_size+row_size); i++){
            for (unsigned int j = (column_size); j < (column_size)+column_size; j++){
                lower_right.set(i-row_size,j-column_size,matrix[i][j]);
            }
        }
        all_matrix[3] = lower_right;
    } else if (rows%2 != 0 && columns%2 == 0) {
        Matrix lower_right(row_size, column_size, 0);
        for (unsigned int i = (row_size-1); i < (row_size-1+row_size); i++){
            for (unsigned int j = (column_size); j < (column_size)+column_size; j++){
                lower_right.set(i-row_size+1,j-column_size,matrix[i][j]);
            }
        }
        all_matrix[3] = lower_right;
    } else if (rows%2 == 0 && columns%2 != 0) {
        Matrix lower_right(row_size, column_size, 0);
        for (unsigned int i = (row_size); i < (row_size+row_size); i++){
            for (unsigned int j = (column_size-1); j < (column_size-1)+column_size; j++){
                lower_right.set(i-row_size,j-column_size+1,matrix[i][j]);
            }
        }
        all_matrix[3] = lower_right;
    } else {
        Matrix lower_right(row_size, column_size, 0);
        for (unsigned int i = (row_size-1); i < (row_size-1+row_size); i++){
            for (unsigned int j = (column_size-1); j < (column_size-1)+column_size; j++){
                lower_right.set(i-row_size+1,j-column_size+1,matrix[i][j]);
            }
        }
        all_matrix[3] = lower_right;
    } 
    return all_matrix;
}   

void Matrix::clear() {
    if (rows > 0){
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    rows = 0;
    columns = 0;
    }
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
        double* filler = matrix[row1];
        matrix[row2] = matrix[row1];
        matrix[row1] = filler;
        return true;
    } else {
        return false; 
    }
}
void Matrix::transpose(){
    unsigned int new_rows = columns;
    unsigned int new_columns = rows;
    double** new_matrix = new double*[new_rows];
    for (unsigned int i = 0; i < new_rows; i++){
        new_matrix[i] = new double[new_columns];
    }
    for (unsigned int i = 0; i < new_rows; i++){
        for (unsigned int j = 0; j < new_columns; j++){
            new_matrix[i][j] = matrix[j][i];
        }
    }
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    rows = new_rows;
    columns = new_columns;
    matrix = new_matrix;

}
bool Matrix::add(const Matrix& b){
    if (rows == b.rows && columns == b.columns){
        for (unsigned int i = 0; i < rows; i++){
            for (unsigned int j = 0; j < columns; j++){
                matrix[i][j] = matrix[i][j] + b.matrix[i][j];
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
                matrix[i][j] = matrix[i][j] - b.matrix[i][j];
            }
        }
        return true;
    } else {
        return false;
    }
}
void Matrix::resize(unsigned new_rows, unsigned new_columns, double fill){
    double** new_matrix = new double*[new_rows];
    for (unsigned int i = 0; i < new_rows; i++ ){
        new_matrix[i] = new double[new_columns];
    }
    for (unsigned int i = 0; i < new_rows; i++){
        for (unsigned int j = 0; j < new_columns; j++){
            if (i >= rows || j >= columns){
                new_matrix[i][j] = fill;
            } else {
                new_matrix[i][j] = matrix[i][j];
            }
        }
    }
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    rows = new_rows;
    columns = new_columns;
    matrix = new_matrix;
} 



bool operator== (const Matrix& m1, const Matrix& m2){
    if (m1.num_rows() != m2.num_rows() || m1.num_cols() != m2.num_cols()){
        return false;
    } else {
        for (unsigned int i = 0; i < m1.num_rows(); i++){
            for (unsigned int j = 0; j < m1.num_cols(); j++){
                if (m1.get_matrix()[i][j] != m2.get_matrix()[i][j]){
                    return false;
                }
            }
        }
    }
    return true;
}
bool operator!= (const Matrix& m1, const Matrix& m2){
    if (m1.num_rows() != m2.num_rows() || m1.num_cols() != m2.num_cols()){
        return true;
    } else {
        for (unsigned int i = 0; i < m1.num_rows(); i++){
            for (unsigned int j = 0; j < m1.num_cols(); j++){
                if (m1.get_matrix()[i][j] != m2.get_matrix()[i][j]){
                    return true;
                }
            }
        }
    }
    return false;
}
std::ostream& operator<< (std::ostream& out, const Matrix& m){
    out << m.num_rows() << " x " << m.num_cols() << " matrix:" << endl;
    out << "[ ";
    if (m.num_rows() == 0){
        out << "]";
        out << endl;
    }
    for (unsigned int i = 0; i < m.num_rows(); i++){
        for (unsigned int j = 0; j < m.num_cols(); j++){
            if (j == 0 && i != 0){
                out << "  ";
            }

            out << m.get_matrix()[i][j] << " ";

            if (i == m.num_rows()-1 && j == m.num_cols()-1 ){
                out << "]";
            }
        }
        out << endl;
    }
    return out;
}
Matrix& Matrix::operator= (const Matrix& m){
    rows = m.rows;
    columns = m.columns;
    matrix = new double*[rows];
    for (unsigned int i = 0; i < rows; i++){
        matrix[i] = new double[columns];
        for (unsigned int j = 0; j < columns; j++){
            matrix[i][j] = m.matrix[i][j];
        }
    }
    return *this;
}