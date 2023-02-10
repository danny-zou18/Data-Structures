#include "Matrix.h"

using std::endl; using std::vector;

//Initializing default constructor
Matrix::Matrix(){
    rows = 0;
    columns = 0;
}
//Copy constructor taking another matrix as the argument to be copied
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
//Basic constructor
Matrix::Matrix(unsigned int Rows, unsigned int Columns, double fill){
    if (Rows == 0 || Columns == 0){
        rows = 0;
        columns = 0; // Set the rows and columns
    } else {
        rows = Rows;
        columns = Columns;
        matrix = new double*[rows];
        for (unsigned int i = 0; i < rows; i++){ //Create the 2-d array that stores the matrix
            matrix[i] = new double[columns];
        }
        for (unsigned int i = 0; i < rows; i++){
            for (unsigned int j = 0; j < columns; j++){ //Make every spot of that 2-d array/matrix into fill
                matrix[i][j] = fill;
            }
        }
    }
}
//Deconstructor
Matrix::~Matrix(){
    clear();
}
unsigned int Matrix::num_rows() const { // Returns the number of rows
    return rows;
}
unsigned int Matrix::num_cols() const { // Returns the number of columns
    return columns;
}
double** Matrix::get_matrix() const { // Returns the 2-D array that is the matrix
    return matrix;
}
//Get function that stores the value at specified location into value
bool Matrix::get(unsigned int row, unsigned int column, double& value) const {
    if ((row >= 0 && row < rows) && (column >= 0 && column < columns)){
        value = matrix[row][column];
        return true;
    } else {
        return false;
    }
}
//Get row function that gets all the values at specified row and puts it 
//into a double pointer that gets returned
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
//Get column function that gets all the values at specified column and put its
//into a double pointer that gets returned
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
//Quarter function that splits matrix into 4 even sections, 
// upper left, upper right, lower left, lower right
Matrix* Matrix::quarter() const{
    //Matrix pointer that stores all the sections as seperate matrices
    Matrix* all_matrix = new Matrix[4];
    unsigned int row_size;
    unsigned int column_size;
    //Special case for if both row size and column size is 1
    if (rows == 1 && columns == 1){
        Matrix all(1,1,0);
        all.set(0,0,matrix[0][0]);
        all_matrix[0] = all;
        all_matrix[1] = all;
        all_matrix[2] = all;
        all_matrix[3] = all;
        return all_matrix;
    }
    //Case for if row size is 1
    if (rows == 1){
        row_size = 1;
        //Calculate section dimensions based on if original dimensions are odd or even
        if (columns%2 == 0){
            column_size = columns / 2;
        } else {
            column_size = (columns/2) + 1;
        }
        //If row is equal to 1, the upper left section is going to be equal to the upper right section
        Matrix upper_left(row_size, column_size, 0);
            for (unsigned int j = 0; j < column_size; j++){
                upper_left.set(0,j,matrix[0][j]);
            }
        all_matrix[0] = upper_left;
        all_matrix[2] = upper_left;
        
        //And also lower left section is going to be equal to the lower right section
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
    //Case for if columns is 1
    if (columns == 1){
        column_size = 1;
        //Calculate section dimensions based on if original dimensions are odd or even
        if (rows%2 == 0){
            row_size = rows / 2;
        } else {
            row_size = (rows/2) + 1;
        }
        //If columns is equal to 1, then the upper left section is going to be equal to the lower left section
        Matrix upper_left(row_size, column_size, 0);
        for (unsigned int i = 0; i < row_size; i++){
            upper_left.set(i,0,matrix[i][0]);
        }
        all_matrix[0] = upper_left;
        all_matrix[1] = upper_left;
        //Similarly, the upper right section is going to be equal to the lower right section
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
    //Calculate section dimensions based on if original dimensions are odd or even
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
    //Gets the upper left values of original matrix and puts it into the new upper left matrix
    Matrix upper_left(row_size, column_size, 0);
    for (unsigned int i = 0; i < row_size; i++){
        for (unsigned int j = 0; j < column_size; j++){
            upper_left.set(i,j,matrix[i][j]);
        }
    }
    all_matrix[0] = upper_left;

    //Gets the upper right values of original matrix and puts it into the new upper right matrix
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
    //Gets the lower left values of original matrix and puts it into the new lower left matrix
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
    //Gets the lower right values of original matrix and puts it into the new lower right matrix
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
//Clear function that clears all allocated data
void Matrix::clear() {
    if (rows > 0){
    for (unsigned int i = 0; i < rows; i++){ 
        delete [] matrix[i]; //First delete the memory inside matrix
    }
    delete [] matrix; //Then delete matrix itself
    rows = 0;
    columns = 0;
    }
}
//Set function that sets the specified matrix location as the given value
bool Matrix::set(unsigned int row, unsigned int column, double value){
    if ((row >= 0 && row < rows) && (column >= 0 && column < columns)){
        matrix[row][column] = value;
        return true;
    } else {
        return false;
    }
}
//Matrix multiplication function that multiplies all values inside a matrix with given coefficient
void Matrix::multiply_by_coefficient(double coefficient){
    for (unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < columns; j++){
            matrix[i][j] = matrix[i][j] * coefficient;
        }
    }
}
//Swap row function that swaps two givens in a matrix if the parameters are valid
bool Matrix::swap_row(unsigned int row1, unsigned int row2){
    if ((row1 >= 0 && row1 < rows) && (row2 >= 0 && row2 < rows)){
        double* filler = matrix[row2]; //Make a filler double pointer to store the first row
        matrix[row2] = matrix[row1]; //Set the values of first row into the second row
        matrix[row1] = filler; //Set the values of second row into the first row
        return true;
    } else {
        return false; 
    }
}
//Transpose function that flips the dimensions of the matrix and also the values inside of it
void Matrix::transpose(){
    unsigned int new_rows = columns;
    unsigned int new_columns = rows;
    double** new_matrix = new double*[new_rows];
    for (unsigned int i = 0; i < new_rows; i++){
        new_matrix[i] = new double[new_columns];
    }
    //Nested for loop that flips the values inside the matrix
    for (unsigned int i = 0; i < new_rows; i++){
        for (unsigned int j = 0; j < new_columns; j++){
            new_matrix[i][j] = matrix[j][i];
        }
    }
    //Deletes the old allocated memory
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    rows = new_rows;
    columns = new_columns;
    matrix = new_matrix; //Assign the newly allocated memory/values to the main matrix

}
//Function thats adds the values of given matrix into current matrix, returns true if parameters are valid
//and false if not
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
//Function that subtracts the values of given matrix from current matrix, returns true if parameters are valid
//and false if not
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
//Extra credit resize function that resizes the current matrix with the given new dimensions
//If the given dimensions are bigger than current dimensions, then fill those newly created spaces with given
//fill value
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
    //Delete old allocated space
    for (unsigned int i = 0; i < rows; i++){
        delete [] matrix[i];
    }
    delete [] matrix;

    rows = new_rows;
    columns = new_columns;
    matrix = new_matrix; 
} 
// == Operator that compares the two given matrices and returns true if they are the same
bool operator== (const Matrix& m1, const Matrix& m2){
    if (m1.num_rows() != m2.num_rows() || m1.num_cols() != m2.num_cols()){
        return false;
    } else {
        //Nested for loop that compares every single value in the two given matrices
        //if any two values are not the same, then return false
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
// != Operator that compares the two given matrices and returns true if any two values are not the same
bool operator!= (const Matrix& m1, const Matrix& m2){
    if (m1.num_rows() != m2.num_rows() || m1.num_cols() != m2.num_cols()){
        return true;
    } else {
        //Nested for loop that compares every single value in the two given matrices
        //if any two vales are not the same, return true
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
//out operator that prints the matrix in a formatted way
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
//Assignment operator that does the same thing as the copy constructor, copy the given matrix exactly into
//the wanted new matrix
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