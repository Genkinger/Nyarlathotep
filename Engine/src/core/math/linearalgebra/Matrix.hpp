//
// Created by genkinger on 8/26/19.
//

#ifndef NYARLATHOTEP_MATRIX_HPP
#define NYARLATHOTEP_MATRIX_HPP

#endif //NYARLATHOTEP_MATRIX_HPP

#include <ostream>

namespace Ny::Math::LinearAlgebra {

    template<int ROWS, int COLS, typename T>
    class Matrix {
        T m[ROWS][COLS] = {};
    public:

        Matrix() {
            if constexpr (ROWS == COLS) {
                for (int i = 0; i < ROWS; i++) {
                    m[i][i] = 1;
                }
            }
        }

        Matrix(T scale) {
            if constexpr (ROWS == COLS) {
                for (int i = 0; i < ROWS; i++) {
                    m[i][i] = scale;
                }
            }
        }

        T *operator[](int idx) {
            return m[idx];
        }

        const T *operator[](int idx) const {
            return m[idx];
        }

        Matrix<COLS, ROWS, T> transpose() const {
            Matrix<COLS, ROWS, T> result;
            for (int i = 0; i < COLS; i++) {
                for (int j = 0; j < ROWS; j++) {
                    result[i][j] = m[j][i];
                }
            }
            return result;
        }

        template<int R_COLS>
        Matrix<ROWS, R_COLS, T> operator*(const Matrix<COLS, R_COLS, T> &other) const {
            Matrix<ROWS, R_COLS, T> result;
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < R_COLS; j++) {
                    for (int k = 0; k < COLS; k++) {
                        result[i][j] += m[i][k] * other[k][j];
                    }
                }
            }
            return result;
        }

        Vector <ROWS, T> operator*(const Vector <COLS, T> &other) const {
            Vector<ROWS, T> result;
            for (int i = 0; i < ROWS; i++) {
                for (int j = 0; j < COLS; j++) {
                    result[i] += m[i][j] * other[j];
                }
            }
            return result;
        }

        Vector <ROWS, T> getColumn(i32 i) const {
            Vector<ROWS, T> result;
            for (int j = 0; j < ROWS; j++) {
                result[j] = m[j][i];
            }
            return result;
        }

        Vector <COLS, T> getRow(i32 i) const {
            Vector<COLS, T> result;
            for (int j = 0; j < COLS; j++) {
                result[j] = m[i][j];
            }
            return result;
        }

        Matrix<ROWS, COLS, T> setRow(i32 i, const Vector <COLS, T> &row) const {
            auto result = *this;
            for (int j = 0; j < COLS; j++) {
                result[i][j] = row[j];
            }
            return result;
        }


        Matrix<ROWS, COLS, T> setColumn(i32 i, const Vector <ROWS, T> &column) const {
            auto result = *this;
            for (int j = 0; j < ROWS; j++) {
                result[j][i] = column[j];
            }
            return result;
        }

        Matrix<ROWS, COLS, T> swapRows(i32 i, i32 j) const {
            auto result = *this;
            auto row_i = getRow(i);
            auto row_j = getRow(j);
            result.setRow(i, row_j);
            result.setRow(j, row_i);
            return result;
        }

        Matrix<ROWS, COLS, T> swapColumns(i32 i, i32 j) const {
            auto result = *this;
            auto column_i = getColumn(i);
            auto column_j = getColumn(j);
            result.setRow(i, column_j);
            result.setRow(j, column_i);
            return result;
        }

        Matrix<ROWS, COLS, T> addToRow(i32 i, const Vector <COLS, T> &vector) {
            auto result = *this;
            for (int j = 0; j < COLS; j++) {
                result[i][j] += vector[j];
            }
            return result;
        }

        Matrix<ROWS, COLS, T> addToColumn(i32 i, const Vector <ROWS, T> &vector) {
            auto result = *this;
            for (int j = 0; j < ROWS; j++) {
                result[j][i] += vector[j];
            }
            return result;
        }

        Matrix<ROWS, COLS + 1, T> appendColumn(const Vector <ROWS, T> &vector) {
            Matrix<ROWS, COLS + 1, T> result;
            for (int j = 0; j < COLS; j++) {
                result = result.setColumn(j, getColumn(j));
            }
            result = result.setColumn(COLS, vector);
            return result;
        }

        Matrix<ROWS + 1, COLS, T> appendRow(const Vector <COLS, T> &vector) {
            Matrix<ROWS + 1, COLS, T> result;
            for (int j = 0; j < ROWS; j++) {
                result = result.setRow(j, getRow(j));
            }
            result = result.setRow(ROWS, vector);
            return result;
        }

        template<int R_COLS>
        Matrix<ROWS, COLS + R_COLS, T> appendMatrix(const Matrix<ROWS, R_COLS, T> &other) {
            Matrix<ROWS, COLS + R_COLS, T> result;
            for (int i = 0; i < COLS; i++) {
                result = result.setColumn(i, getColumn(i));
            }
            for (int i = 0; i < R_COLS; i++) {
                result = result.setColumn(COLS + i, other.getColumn(i));
            }
            return result;
        }

        //TODO: this needs verification and tests
        Matrix<ROWS, COLS, T> rref() {
            auto result = *this;
            for (int i = 0; i < ROWS; i++) {
                i32 maxEl = abs(result[i][i]);
                i32 maxRow = i;
                for (int k = i + 1; k < ROWS; k++) {
                    if (abs(result[k][i]) > maxEl) {
                        maxEl = abs(result[k][i]);
                        maxRow = k;
                    }
                }
                result = result.swapRows(i, maxRow);
                for (int k = i + 1; k < ROWS; k++) {
                    T c = -result[k][i] / result[i][i];
                    for (int j = i; j < COLS; j++) {
                        if (i == j)
                            result[k][j] = 0;
                        else
                            result[k][j] += c * result[i][j];
                    }
                }
            }
            return result;
        }

        Matrix<ROWS,COLS,T> inverse(){
            if constexpr (ROWS == COLS){
                //TODO: implement
                return *this;
            }else{
                //TODO: throw error here (or calculate pseudoinverse)
                return *this;
            }
        }

        static Matrix<4, 4, T> translation(const Vector<3, T> &translation) {
            Matrix<4, 4, T> result;
            result[0][3] = translation[0];
            result[1][3] = translation[1];
            result[2][3] = translation[2];
            return result;
        }

        static Matrix<4, 4, T> rotation(const Vector<3, T> &axis, const T rad) {
            Matrix<4, 4, T> result;
            //TODO: implement
            return result;
        }

        static Matrix<4, 4, T> scale(const Vector<3, T> &scale) {
            Matrix<4, 4, T> result;
            result[0][0] = scale[0];
            result[1][1] = scale[1];
            result[2][2] = scale[2];
            return result;
        }

        static Matrix<4, 4, T> scale(const T &scale) {
            return Matrix<4, 4, T>(scale);
        }

    };

    template<int ROWS, int COLS, typename T>
    std::ostream &operator<<(std::ostream &os, const Matrix<ROWS, COLS, T> &obj) {
        for (int i = 0; i < ROWS; i++) {
            os << "| ";
            for (int j = 0; j < COLS; j++) {
                if (obj[i][j] < 0) {
                    os << obj[i][j] << " ";
                } else {
                    os << " " << obj[i][j] << " ";
                }
            }
            os << " |\n";
        }

        return os;
    }

    using Matrix33f = Matrix<3, 3, float>;
    using Matrix44f = Matrix<4, 4, float>;
    using Matrix22f = Matrix<2, 2, float>;


}