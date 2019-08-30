//
// Created by genkinger on 8/28/19.
//

#ifndef NYARLATHOTEP_RAY_HPP
#define NYARLATHOTEP_RAY_HPP

#include "Vector.hpp"

namespace ny::math::lin {

    template<int N, typename T>
    class Ray {
        Vector<N, T> mRayDirection = {0};
        Vector<N, T> mRayOrigin = {0};
    };
}

#endif //NYARLATHOTEP_RAY_HPP
