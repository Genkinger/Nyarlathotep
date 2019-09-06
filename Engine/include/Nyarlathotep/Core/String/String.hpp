//
// Created by genkinger on 8/27/19.
//

#ifndef NYARLATHOTEP_STRING_HPP
#define NYARLATHOTEP_STRING_HPP

#include <Nyarlathotep/Core/Core.hpp>

namespace ny {

    class String {
    private:
        std::string mString;
    public:
        String() = default;

        String(const char *string);
        String(const char *string, u64 length);

        String(char c, u64 count);

        String(const std::string &string);

        String(const String &string);

    public:
        String substr(u64 start, u64 end) const;

        std::vector<String> split(const String &delimiter) const;

        std::vector<String> lines() const;


        String replace(const String &find, const String &replace) const;

        bool contains(const String &string) const;

        std::optional<u64> find(const String &string) const;

        std::vector<u64> findAll(const String &string) const;

        bool beginsWith(const String &string) const;

        bool endsWith(const String &string) const;

        String ltrim(char c) const;

        String rtrim(char c) const;

        String trim(char c) const;

        String ltrim() const;

        String rtrim() const;

        String trim() const;

        u64 count(const String &string) const;

    public:
        i64 length() const;

        const char *raw() const;

    public:
        String &operator+=(const String &rightHand);

        String &operator+=(char rightHand);

        String &operator*=(u64 count);

        String operator+(const String &rightHand) const;

        String operator+(char rightHand) const;

        String operator*(u64 count) const;

        bool operator<(const String &other) const;

        bool operator>(const String &other) const;

        bool operator==(const String &other) const;

        bool operator<=(const String &other) const;

        bool operator>=(const String &other) const;

        char operator[](u64 index) const;

        char &operator[](u64 index);

        friend std::ostream &operator<<(std::ostream &os, const String &obj);

        operator std::string() const {
            return mString;
        }

        operator std::string&() {
            return mString;
        }

        operator const char *() const {
            return raw();
        }
    };

    std::ostream &operator<<(std::ostream &os, const String &obj);
}


#endif //NYARLATHOTEP_STRING_HPP
