//
// Created by genkinger on 8/27/19.
//

#ifndef NYARLATHOTEP_NSTRING_HPP
#define NYARLATHOTEP_NSTRING_HPP

#include <vector>
#include <ostream>
#include "../common.hpp"

namespace Ny {
    class NString {
    private:
        i32 mLength = 0;
        char *mBuffer = nullptr;
    private:
        i32 resize(i32 length);

    public:
        NString() = default;

        NString(const char *string);

        NString(const NString &string);

        ~NString();

    public:
        NString substring(const i32 start, const i32 end) const;

        std::vector<NString> split(const char delimiter) const;

        NString replace(const char find, const char replace) const;

        bool contains(const char c) const;

        bool contains(const NString &string) const;

        bool begins(const NString &string) const;

        i32 count(const char c) const;

    public:
        i32 length() const;

        const char *raw() const;

    public:
        NString operator+=(const NString &rightHand);

        NString operator+=(const char rightHand);

        NString operator+(const NString &rightHand);

        NString operator+(const char rightHand);

        NString operator*(const i32 count);

        NString operator*=(const i32 count);

        char& operator[](const i32 index);

    };

    std::ostream &operator<<(std::ostream &os, const NString &obj);
}


#endif //NYARLATHOTEP_NSTRING_HPP
