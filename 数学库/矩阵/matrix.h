#ifndef _lyy_matrix
#define _lyy_matrix
#include <iostream>

namespace lyy_matrix
{
    class Matrix
    {
    private:
        // private variable
        double ** _array;
        int _row;       // 行
        int _column;    // 列
        // private function
        void _array_copy(const double * array);    // 将一维数组拷贝到二维
        void _delete_darray();                     //  删除自身数组_array
    

    public:
        // initial
        Matrix(int row = 1 , int column = 1);
        Matrix(int row , int column , const double * array);   // 从一维数组创建矩阵

        // delete
        ~Matrix();

        // function
        double get_value(int row , int column);
        int    get_row();
        int    get_column();
        void   reset_size(int row , int column);       // 重置大小，清空数据
        void   load_from_array(const double * array);  // 使用double数组写入数据（其实可以调整大小后用等于赋值）

        // overload
        Matrix operator+(const Matrix & matrix) const;   // 矩阵加法
        Matrix operator*(const Matrix & matrix) const;         // 两个矩阵相乘
        Matrix operator*(double n) const;                // 矩阵数乘
        friend Matrix operator*(double n , const Matrix & matrix); // 反过来的数乘
        double * operator>>(double * &tar_array) const;        // 导出数据到一维数组（一行一行的）
        double * operator>>(double tar_array[]) const;
        // cout
        friend std::ostream & operator<<(std::ostream & os , const Matrix & matrix);
        
        
    };

}
#endif