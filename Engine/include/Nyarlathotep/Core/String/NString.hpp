//
// Created by genkinger on 8/27/19.
//

#ifndef NYARLATHOTEP_NSTRING_HPP
#define NYARLATHOTEP_NSTRING_HPP

#include <Nyarlathotep/Core/Core.hpp>

namespace ny {
    class NString {
    private:
        i32 mLength = 0;
        char *mBuffer = nullptr;
    private:
        i32 resize(i32 length);

    public:
        NString() = default;
        NString(const char *string);
        NString(char c);
        NString(const char *string, i32 length);
        NString(const NString &string);
        ~NString();

    public:
        NString substring(i32 start, i32 length = -1) const;
        std::vector<NString> split(char delimiter) const;
        std::vector<NString> lines() const;

        std::vector<NString> split(const NString &delimiter) const;
        std::vector<NString> splitRaw(const NString &delimiter) const;



        NString replace(char find, char replace) const;
        NString replace(const NString &find, const NString &replace) const;

        bool contains(char c) const;
        bool contains(const NString &string) const;
        i32 find(char c) const;
        i32 find(const NString &string) const;
        std::vector<i32> findAll(char c) const;
        std::vector<i32> findAll(const NString &string) const;
        bool begins(const NString &string) const;
        bool ends(const NString &string) const;
        NString ltrim(char c = ' ') const;
        NString rtrim(char c = ' ') const;
        NString trim(char c = ' ') const;
        i32 count(char c) const;
        i32 count(const NString &string) const;

    public:
        i32 length() const;
        std::shared_ptr<char> raw() const;

    public:
        NString operator+=(const NString &rightHand);
        NString operator+=(char rightHand);
        NString &operator=(const NString &other);
        char &operator[](i32 index);
        NString operator*=(i32 count);

        NString operator+(const NString &rightHand) const;
        NString operator+(char rightHand) const;
        NString operator*(i32 count) const;
        bool operator<(const NString &other) const;
        bool operator>(const NString &other) const;
        bool operator==(const NString &other) const;
        bool operator<=(const NString &other) const;
        bool operator>=(const NString &other) const;
        char operator[](i32 index) const;

    };

    std::ostream &operator<<(std::ostream &os, const NString &obj);
}


#endif //NYARLATHOTEP_NSTRING_HPP
