#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

template<typename T>
class Matrix
{
private:
    int rows;
    int columns;
    vector<vector<T>> matrix;
public:
    //дефолт конструктор
    Matrix(int curr_rows, int curr_columns)
    {
        rows = curr_rows;
        columns = curr_columns;
        matrix = vector<vector<T>>(rows, vector<T>(columns));
    }
    //скаляр конструктор
    Matrix(int curr_rows, int curr_columns, const T value)
    {
        rows = curr_rows;
        columns = curr_columns;
        matrix = vector<vector<T>>(rows, vector<T>(columns, value));
    }
    //конструктор матрица в объект класса
    Matrix(vector<vector<T>> matrix)
    {
        this->matrix = matrix;
        rows = matrix.size();
        columns = matrix[0].size();
    }
    //беру матрицу из файла
    Matrix(string filename)
    {
        ifstream fileinput(filename);
        fileinput >> rows >> columns;
        matrix = vector<vector<T>>(rows, vector<T>(columns));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                fileinput >> matrix[i][j];
            }
        }
    }
    //пустая матрица
    Matrix() : rows(0), columns(0) {}
    //вывод матрицы в файл
    void printMatrixToFile(string fileoutname)
    {
        ofstream fileout(fileoutname);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                fileout << matrix[i][j] << " ";
            }
            fileout << endl;
        }
    fileout.close();
    }
    //ввод матрицы из файла
    void inputMatrixFromFile(string fileinputname)
    {
        ifstream filein(fileinputname);
        filein >> rows >> columns;
        matrix = vector<vector<T>>(rows, vector<T>(columns));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                filein >> matrix[i][j];
            }
        }
        filein.close();
    }
    //перегрузка <<
    friend ostream& operator<<(ostream& os, const Matrix& other)
    {
        for (auto row : other.matrix)
        {
            for (auto elem : row)
            {
                os << elem << " ";
            }
            os << endl;
        }
        return os;
    }
    //перегрузка >>
    friend istream& operator>>(istream& is, Matrix& other)
    {
        cout << "Enter " << other.columns * other.rows << " elements " << endl;
        for (int i = 0; i < other.rows; ++i)
        {
            for (int j = 0; j < other.columns; ++j)
            {
                is >> other.matrix[i][j];
            }
        }
        return is;
    }
    //перегрузка равенства
    bool operator==(const Matrix& other)
    {
        if (rows != other.matrix || columns != other.matrix)
        {
            throw invalid_argument("Error ==");
        }
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (matrix[i][j] != other.matrix[i][j])
                {
                    throw invalid_argument("Error");
                }
            }
        }
        return true;
    }
    //перегрузка неравенства
    bool operator!=(const Matrix& other)
    {
        return !(*this == other);
        /*if (rows != other.rows || columns != other.columns)
        {
            return true;
        }
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (matrix[i][j] != other.matrix[i][j])
                {
                    return true;
                }
            }
        }
        throw invalid_argument("Error !=");    */     
    }
    //перегрузка сложения матриц
    Matrix operator+(const Matrix& other)
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw invalid_argument("Error + matrices");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }
    //перегрузка вычитания матриц
    Matrix operator-(const Matrix& other)
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw invalid_argument("Error - matrices");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }
    //умножение матрицы на скаляр
    Matrix operator*(int scalar)
    {
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                result.matrix[i][j] = matrix[i][j] * scalar;
            }
        }
        return result;
    }
    //умножение матриц
    Matrix operator*(const Matrix& other)
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw invalid_argument("Error * matrices");
        }
        Matrix result(rows, other.columns);
        for (int i = 0; i < rows; ++i)
        {
           for (int j = 0; j < other.columns; ++j)
           {
                T sum = 0;
                for (int k = 0; k < columns; ++k)
                {
                    sum += matrix[i][k] * other.matrix[k][j];
                }
                result.matrix[i][j] = sum;
           }
        }
        return result;
    }
    //перегрузка присваивания
    Matrix operator=(const Matrix& other)
    {
        if (rows != other.matrix || columns != other.columns)
        {
            throw invalid_argument("Error = matrices");
        }
        this->rows = other.rows;
        this->columns = other.columns;
        this->matrix = other.matrix;
    }
    //перегрузка ! для нахождения обратной матрицы
    Matrix<double> operator!() 
    {
        if (this->rows != this->columns) {
            throw invalid_argument("Error !");
        }
        int n = this->rows;
        vector<vector<double>> extmatrix(n, vector<double>(n * 2, 0.0));
        for (int i = 0; i < n; ++i) {
            extmatrix[i][i + n] = 1.0;
            for (int j = 0; j < n; ++j) {
                extmatrix[i][j] = this->matrix[i][j];
            }
        }
        
        for (int i = 0; i < n; ++i) {
            if (extmatrix[i][i] == 0) {
                throw invalid_argument("Error !");
            }
            double p = extmatrix[i][i];
            for (int j = 0; j < 2 * n; ++j) {
                extmatrix[i][j] /= p;
            }
            for (int k = 0; k < n; ++k) {
                if (k != i) {
                    double f = extmatrix[k][i];
                    for (int j = 0; j < 2 * n; ++j) {
                        extmatrix[k][j] -= extmatrix[i][j] * f;
                    }
                }
            }
        }
        
        vector<vector<double>> inverse(n, vector<double>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                inverse[i][j] = extmatrix[i][j + n];
            }
        }
        return inverse;    
    }
    //нулевая матрица
    static Matrix zeromatrix(int rows, int columns)
    {
        return Matrix(vector<vector<T>>(rows, vector<T>(columns)));
    }
    //единичная матрица
    static Matrix onematrix(int rows)
    {
        vector<vector<T>> result = vector<vector<T>>(rows, vector<T>(rows, 0));
        for (int i = 0; i < rows; ++i)
        {
            result[i][i] = 1;
        }
        return result;
    }
};

int main()
{
    Matrix<int> fileMatrix("inputFile.txt"); // done
    Matrix<int> intMatrix(3, 3); // done
    //cin >> intMatrix;
    fileMatrix.printMatrixToFile("outputFile.txt"); // done
    Matrix<int> sumMatrix = fileMatrix + intMatrix; // done
    //cout << sumMatrix;
    Matrix<int> multMatrix = fileMatrix * intMatrix; // done
    //cout << multMatrix;
    Matrix<int> ravMatrix = fileMatrix; // done
    //cout << ravMatrix << endl;
    //cout << fileMatrix + intMatrix << endl;
    //cout << fileMatrix - intMatrix << endl;
    //cout << fileMatrix * 5 << endl;
    //cout << !fileMatrix << endl;
    //cout << Matrix<int>::zeromatrix(3,3) << endl;
    //cout << Matrix<int>::onematrix(3) << endl;
}