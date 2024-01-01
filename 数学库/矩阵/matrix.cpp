#include "matrix.h"
#include <iomanip>

namespace lyy_matrix
{
    double ** _new_darray(int row , int column)
    {
        double ** array = new double *[row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new double[column];
        }
        // inital to 0
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                array[i][j] = 0;
            }
        }
        return array;
    }


    // class Matrix
    ////////////////////////////////////
    // private function
    void Matrix::_array_copy(const double * array)
    {
        int k = 0;
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
            {
                _array[i][j] = array[k];
                k++;
            }
        }
    }

    
    void Matrix::_delete_darray()
    {
        for (int i = 0; i < _row; i++)
        {
            delete [] _array[i];
        }
        delete [] _array;
    }



    //////////////////////////////////////////////////
    // initial
    Matrix::Matrix(int row , int column)
    { 
        _row = row;   
        _column = column;   
        _array = _new_darray(_row , _column);
    }
    
    Matrix::Matrix(int row , int column , const double * array)
    {
        _row = row;
        _column = column;
        _array = _new_darray(_row , _column);
        _array_copy(array);
    }

    // destory
    Matrix::~Matrix()
    { _delete_darray(); }
    
    // public function
    double Matrix::get_value(int row , int column)
    { return _array[row][column]; }

    int Matrix::get_row()   
    { return _row; }

    int Matrix::get_column()
    { return _column; }

    void Matrix::load_from_array(const double * array)   
    { _array_copy(array); }

    void Matrix::reset_size(int row , int column)
    {
        _delete_darray();
        _row = row;
        _column = column;
        _array = _new_darray(_row , _column);
    }

    //////////////////////////////
    // overload
    Matrix Matrix::operator+(const Matrix & matrix) const
    {
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
            {
                _array[i][j] = _array[i][j] + matrix._array[i][j];
            } 
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix & matrix) const
    {
        // 这里应该有个错误检查，检查两个矩阵是否能相乘，不能则要抛出错误
        // ????????
        ///////////////////////////////////////////
        Matrix new_matrix = Matrix(this->_row , matrix._column); // 前行 后列

        for (int i = 0; i < this->_row; i++)    // 前行乘后列对应生成结果的i行j列
        {
            for (int j = 0; j < matrix._column; j++)
            {
                double sum = 0;
                for (int k = 0; k < _column; k++)
                {
                    sum = sum + _array[i][k] * matrix._array[k][j];
                }
                new_matrix._array[i][j] = sum;   
            }
        }
        return new_matrix;
    }

    Matrix Matrix::operator*(double n) const
    {
        Matrix new_matrix = Matrix(_row , _column);
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
            {
                new_matrix._array[i][j] = _array[i][j]*n;
            }
        }
        return new_matrix;
    }

    inline Matrix operator*(double n , const Matrix & matrix) // 反过来的数乘
    {
        return matrix * n;
    }

    double * Matrix::operator>>(double * &tar_array) const
    {
        double * res = new double[_row*_column];
        int k = 0;
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
            {
                res[k] = _array[i][j];
                k++;
            }   
        }
        tar_array = res;
        return res;
    }

    double * Matrix::operator>>(double tar_array[]) const
    {
        int k = 0;
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
            {
                tar_array[k] = _array[i][j];
                k++;
            }   
        }
        return tar_array;
    }

    // cout overload
    std::ostream & operator<<(std::ostream & os , const Matrix & matrix)
    {

        os << std::fixed << std::setprecision(2);
        for (int i = 0; i < matrix._row; i++)
        {
            os << '|';
            for (int j = 0; j < matrix._column; j++)
            {
                os << matrix._array[i][j] << ",\t";  
            }
            os << '|' << std::endl;
        }
        return os;
    }
    
}