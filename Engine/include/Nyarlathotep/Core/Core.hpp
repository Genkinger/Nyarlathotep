//
// Created by genkinger on 8/27/19.
//

#ifndef NYARLATHOTEP_CORE_HPP
#define NYARLATHOTEP_CORE_HPP

using i64 = long long int;
using i32 = int;
using i16 = short;
using i8 = char;

using u64 = unsigned long long int;
using u32 = unsigned int;
using u16 = unsigned short;
using u8 = unsigned char;

using byte = i8;

using f32 = float;
using f64 = double;

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <ostream>
#include <fstream>
#include <memory>
#include <iostream>

#include <Nyarlathotep/Core/String/String.hpp>

#define BIT(x) 1 << x


#include <climits>
template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

#endif //NYARLATHOTEP_CORE_HPP
