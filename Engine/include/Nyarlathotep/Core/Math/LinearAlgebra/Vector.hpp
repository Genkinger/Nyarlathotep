//
// Created by genkinger on 8/26/19.
//

#ifndef NYARLATHOTEP_VECTOR_HPP
#define NYARLATHOTEP_VECTOR_HPP

#include <cmath>

namespace ny::math::lin {

    template<int N, typename T>
    class Vector {
        T m[N] = {0};
    public:

        template<typename... Tail>
        Vector(typename std::enable_if<sizeof...(Tail) + 1 == N, T>::type head, Tail... tail)
                : m{head, T(tail)...} {}

        Vector() = default;

        T norm() const {
            float result = 0;
            for (T i : m) {
                result += i * i;
            }
            return sqrtf(result);
        }

        Vector<N,T> normalized() const{
            return *this/norm();
        };

        T &operator[](int idx) {
            return m[idx];
        }

        T operator[](int idx) const {
            return m[idx];
        }

        Vector<N, T> operator+(const Vector<N, T> &other) {
            Vector<N, T> result;
            for (int i = 0; i < N; i++) {
                result[i] = m[i] + other[i];
            }
            return result;
        }

        Vector<N, T> operator+=(const Vector<N, T> &other) {
            for (int i = 0; i < N; i++) {
                m[i] += other[i];
            }
            return *this;
        }

        Vector<N, T> operator-(const Vector<N, T> &other) {
            Vector<N, T> result;
            for (int i = 0; i < N; i++) {
                result[i] = m[i] - other[i];
            }
            return result;
        }

        Vector<N, T> operator-=(const Vector<N, T> &other) {
            for (int i = 0; i < N; i++) {
                m[i] -= other[i];
            }
            return *this;
        }

        Vector<N, T> operator*=(const T &val) {
            for (int i = 0; i < N; i++) {
                m[i] *= val;
            }
            return *this;
        }

        Vector<N, T> operator*(const T &val) {
            Vector<N, T> result;
            for (int i = 0; i < N; i++) {
                result[i] = m[i] * val;
            }
            return result;
        }

        T operator*(const Vector<N,T> &other) {
            T result;
            for(int i = 0; i < N; i++){
                result += m[i] * other[i];
            }
            return result;
        } //TODO: Maybe make this static only

        Vector<N, T> operator/(const T &val) {
            Vector<N, T> result;
            for (int i = 0; i < N; i++) {
                result[i] = m[i] / val;
            }
            return result;
        }

        Vector<N, T> operator/=(const T &val) {
            for (int i = 0; i < N; i++) {
                 m[i] /= val;
            }
            return *this;
        }

        static Vector<3,T> cross(const Vector<3,T> &lhs, const Vector<3,T> &rhs){
            return Vector<3,T>(lhs[1]*rhs[2] - lhs[2]*rhs[1],lhs[2]*rhs[0]-lhs[0]*rhs[2],lhs[0]*rhs[1]-lhs[1]*rhs[0]);
        }

        static T dot(const Vector<N,T> &lhs, const Vector<N,T> &rhs){
            T result;
            for(int i = 0; i < N; i++){
                result += lhs[i] * rhs[i];
            }
            return result;
        }
    };

    template<int N, typename T>
    std::ostream &operator<<(std::ostream &os, const Vector<N, T> &obj) {
        os << "[ ";
        for (int i = 0; i < N; i++) {
            os << obj[i] << " ";
        }
        return os << "]";
    }

    using Vector4f = Vector<4,float>;
    using Vector3f = Vector<3,float>;
    using Vector2f = Vector<2,float>;
}

#endif //NYARLATHOTEP_VECTOR_HPP
