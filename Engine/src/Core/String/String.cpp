//
// Created by genkinger on 8/27/19.
//

#include <Nyarlathotep/Core/String/String.hpp>

namespace ny {

    String::String(const char *string) {
        mString = string;
    }

    String::String(const ny::String &string) {
        mString = string.mString;
    }

    String::String(const std::string &string) {
        mString = string;
    }

    String::String(const char *string, u64 length) {
        mString = std::string(string, length);
    }

    String String::substr(u64 start, u64 end) const {
        return String(mString.substr(start, end - start));
    }

    i64 String::length() const {
        return mString.length();
    }

    const char *String::raw() const {
        return mString.c_str();
    }

    std::vector<String> String::split(const ny::String &delimiter) const {
        std::vector<String> result;
        std::vector<u64> indices = findAll(delimiter);

        if (indices.empty()) return result;

        result.push_back(substr(0, indices[0]));
        for (u64 i = 1; i < indices.size() - 1; i++) {
            i32 j = indices[i - 1] + delimiter.length();
            result.push_back(substr(j, indices[i]));
        }
        result.push_back(substr(indices[indices.size() - 1] + delimiter.length(), length()));

        result.erase(std::remove_if(std::begin(result), std::end(result),
                                    [](const String &s) { return s.length() <= 0; }), result.end()
        );

        return result;
    }

    std::vector<String> String::lines() const {
        return split("\n");
    }

    bool String::contains(const ny::String &string) const {
        return find(string).has_value();
    }

    u64 String::count(const ny::String &string) const {
        return findAll(string).size();
    }


    String String::rtrim(char c) const {
        u64 index = 0;
        for (u64 i = 0; i < length(); i++) {
            if (mString[length() - i - 1] != c) {
                index = i;
                break;
            }
        }
        return substr(0, length() - index);
    }

    String String::ltrim(char c) const {
        u64 index = 0;
        for (u64 i = 0; i < length(); i++) {
            if (mString[i] != c) {
                index = i;
                break;
            }
        }
        return substr(index, length());
    }

    String String::trim(char c) const {
        return ltrim(c).rtrim(c);
    }


    String String::rtrim() const {
        u64 index = 0;
        for (u64 i = 0; i < length(); i++) {
            if (!std::isspace(mString[length() - i - 1])) {
                index = i;
                break;
            }
        }
        return substr(0, length() - index);
    }

    String String::ltrim() const {
        u64 index = 0;
        for (u64 i = 0; i < length(); i++) {
            if (!std::isspace(mString[i])) {
                index = i;
                break;
            }
        }
        return substr(index, length());
    }

    String String::trim() const {
        return ltrim().rtrim();
    }

    std::optional<u64> String::find(const ny::String &string) const {
        if (string.length() > length()) return {};
        for (u64 i = 0; i < length() - string.length() + 1; i++) {
            if (!mString.compare(i, string.length(), string.mString)) return i;
        }
        return {};
    }

    std::vector<u64> String::findAll(const ny::String &string) const {
        std::vector<u64> result;
        if (string.length() > length()) return result;
        for (u64 i = 0; i < length() - string.length() + 1; i++) {
            if (!mString.compare(i, string.length(), string.mString)) result.push_back(i);
        }
        return result;
    }

    String String::replace(const ny::String &find, const ny::String &replace) const {
        //TODO: Implement
        return String();
    }


    bool String::beginsWith(const ny::String &string) const {
        if (string.length() > length()) return false;
        return !mString.compare(0, string.length(), string.mString);
    }

    bool String::endsWith(const ny::String &string) const {
        if (string.length() > length()) return false;
        return !mString.compare(length() - string.length(), string.length(), string.mString);
    }

    bool String::operator<(const ny::String &other) const {
        return mString < other.mString;
    }

    bool String::operator>(const ny::String &other) const {
        return mString > other.mString;
    }

    bool String::operator<=(const ny::String &other) const {
        return mString <= other.mString;
    }

    bool String::operator>=(const ny::String &other) const {
        return mString >= other.mString;
    }

    bool String::operator==(const ny::String &other) const {
        return mString == other.mString;
    }

    String String::operator+(const ny::String &other) const {
        return String(mString + other.mString);
    }

    String String::operator+(char other) const {
        return String(mString + other);
    }

    String &String::operator+=(const ny::String &other) {
        mString += other.mString;
        return *this;
    }

    String &String::operator+=(char other) {
        mString += other;
        return *this;
    }

    String &String::operator*=(u64 count) {
        std::string result;
        for (u64 i = 0; i < count; i++) {
            result += mString;
        }
        mString = result;
        return *this;
    }

    String String::operator*(u64 count) const {
        return String(*this) *= count;
    }

    char String::operator[](u64 index) const {
        return mString[index];
    }

    char &String::operator[](u64 index) {
        return mString[index];
    }

    std::ostream &operator<<(std::ostream &os, const String &obj) {
        return os << obj.mString;
    }

}