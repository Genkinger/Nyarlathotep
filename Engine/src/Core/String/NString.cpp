//
// Created by genkinger on 8/27/19.
//

#include <Nyarlathotep/Core/String/NString.hpp>

#include <cstring>

namespace ny {

    NString::~NString() {
        delete[] mBuffer;
    }

    NString::NString(const char *string) {
        mLength = strlen(string);
        mBuffer = new char[mLength];
        std::copy(string, string + mLength, mBuffer);
    }

    NString::NString(char c) {
        mLength = 1;
        mBuffer = new char[mLength];
        mBuffer[0] = c;
    }

    NString::NString(const char *string, i32 length) {
        mLength = length;
        mBuffer = new char[mLength];
        std::copy(string, string + length, mBuffer);
    }

    NString::NString(const NString &string) {
        mLength = string.mLength;
        mBuffer = new char[mLength];
        std::copy(string.mBuffer, string.mBuffer + string.mLength, mBuffer);
    }

    i32 NString::resize(i32 length) {
        char *buffer = new char[length];
        memset(buffer, 0, length);
        if (length >= mLength) {
            std::copy(mBuffer, mBuffer + mLength, buffer);
        } else {
            std::copy(mBuffer, mBuffer + length, buffer);
        }
        delete[] mBuffer;
        mBuffer = buffer;
        int oldSize = mLength;
        mLength = length;
        return oldSize;
    }

    NString NString::substring(i32 start, i32 length) const {
        if (length == -1) {
            length = this->length() - start;
        }
        char sub[length + 1];
        for (int i = start; i < start + length; i++) {
            sub[i - start] = mBuffer[i];
        }
        sub[length] = '\0';
        return NString(sub);
    }

    std::vector<NString> NString::split(char delimiter) const {
        return split(NString(delimiter));
    }

    std::vector<NString> NString::split(const NString &delimiter) const {
        std::vector<i32> indices = findAll(delimiter);
        std::vector<NString> result;
        std::vector<NString> tmp;
        for (int i = 0; i < indices.size(); i++) {
            NString s;
            if (i == 0) {
                tmp.push_back(substring(0, indices[i]));
            } else {
                i32 j = indices[i - 1] + delimiter.length();
                tmp.push_back(substring(j, indices[i] - j));
                if (i == indices.size() - 1) {
                    tmp.push_back(substring(indices[i] + delimiter.length()));
                }
            }
        }
        std::copy_if(std::begin(tmp), std::end(tmp), std::back_inserter(result),
                     [](NString &s) { return s.length() > 0; });
        return result;
    }


    bool NString::contains(char c) const {
        return find(c) != -1;
    }

    i32 NString::count(char c) const {
        return std::count(mBuffer, mBuffer + mLength, c);
    }

    i32 NString::count(const NString &string) const {
        return findAll(string).size();
    }

    NString NString::replace(char find, char replace) const {
        NString result = *this;
        for (int i = 0; i < result.length(); i++) {
            if (result.mBuffer[i] == find) {
                result.mBuffer[i] = replace;
            }
        }
        return result;
    }

    bool NString::begins(const NString &string) const {
        return !std::strncmp(mBuffer, string.mBuffer, string.length());
    }

    bool NString::ends(const NString &string) const {
        return !std::strncmp(mBuffer + mLength - string.mLength, string.mBuffer, string.length());
    }

    i32 NString::find(char c) const {
        for (int i = 0; i < length(); i++) {
            if (c == mBuffer[i]) return i;
        }
        return -1;
    }

    std::vector<i32> NString::findAll(char c) const {
        std::vector<i32> indices;
        for (int i = 0; i < length(); i++) {
            if (c == mBuffer[i]) indices.push_back(i);
        }
        return indices;
    }

    std::vector<i32> NString::findAll(const ny::NString &string) const {
        std::vector<i32> indices;
        i32 count = mLength - string.mLength + 1;

        for (int i = 0; i < count; i++) {
            if (!std::strncmp(mBuffer + i, string.mBuffer, string.mLength)) {
                indices.push_back(i);
            }
        }
        return indices;
    }

    i32 NString::find(const ny::NString &string) const {
        if (string.mLength > mLength) return false;
        i32 count = mLength - string.mLength + 1;

        for (int i = 0; i < count; i++) {
            if (!std::strncmp(mBuffer + i, string.mBuffer, string.mLength)) {
                return i;
            }
        }

        return -1;
    }

    bool NString::contains(const NString &string) const {
        return find(string) != -1;
    }

    NString NString::ltrim(char c) const {
        i32 newStartIndex = 0;
        for (i32 i = 0; i < mLength; i++) {
            if (mBuffer[i] != c) {
                newStartIndex = i;
                break;
            }
        }
        return substring(newStartIndex);
    }

    NString NString::rtrim(char c) const {
        i32 newEndIndex = 0;
        for (i32 i = 0; i < mLength; i++) {
            if (mBuffer[mLength - i - 1] != c) {
                newEndIndex = i;
                break;
            }
        }
        return substring(0, mLength - newEndIndex);
    }

    NString NString::trim(char c) const {
        return ltrim(c).rtrim(c);
    }


    i32 NString::length() const {
        return mLength;
    }

    std::shared_ptr<char> NString::raw() const {
        char *nullTerminated = new char[mLength + 1];
        std::copy(mBuffer, mBuffer + mLength, nullTerminated);
        nullTerminated[mLength] = '\0';
        return std::shared_ptr<char>(nullTerminated);
    }

    NString NString::operator+(const NString &rightHand) const {
        return NString(*this) += rightHand;
    }

    NString NString::operator+(char rightHand) const {
        return NString(*this) += rightHand;
    }

    NString NString::operator*(const i32 count) const {
        return NString(*this) *= count;
    }

    NString NString::operator+=(const NString &rightHand) {
        i32 newLength = mLength + rightHand.mLength;
        i32 oldLength = resize(newLength);
        for (int i = 0; i < rightHand.mLength; ++i) {
            mBuffer[oldLength + i] = rightHand.mBuffer[i];
        }
        return *this;
    }

    NString NString::operator+=(char rightHand) {
        resize(mLength + 1);
        mBuffer[mLength] = rightHand;
        return *this;
    }

    NString NString::operator*=(const i32 count) {
        if (count <= 0) {
            mLength = 0;
            delete[] mBuffer;
            mBuffer = new char[0];
            return *this;
        }

        i32 newLength = mLength * count;
        i32 oldLength = resize(newLength);
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < oldLength; j++) {
                mBuffer[i * oldLength + j] = mBuffer[j];
            }
        }
        return *this;
    }

    char &NString::operator[](i32 index) {
        return mBuffer[index];
    }

    char NString::operator[](i32 index) const {
        return mBuffer[index];
    }

    NString &NString::operator=(const ny::NString &other) {
        if (this != &other) {
            if (other.length() != mLength) {
                delete[] mBuffer;
                mBuffer = new char[other.mLength];
                mLength = other.mLength;
            }
            std::copy(other.mBuffer, other.mBuffer + other.mLength, mBuffer);
        }
        return *this;
    }

    bool NString::operator<(const NString &other) const {
        i32 minLength = mLength >= other.mLength ? other.mLength : mLength;
        return std::strncmp(mBuffer, other.mBuffer, minLength) < 0;
    }

    bool NString::operator>(const NString &other) const {
        i32 minLength = mLength >= other.mLength ? other.mLength : mLength;
        return std::strncmp(mBuffer, other.mBuffer, minLength) > 0;
    }

    bool NString::operator<=(const NString &other) const {
        i32 minLength = mLength >= other.mLength ? other.mLength : mLength;
        return std::strncmp(mBuffer, other.mBuffer, minLength) <= 0;
    }

    bool NString::operator>=(const NString &other) const {
        i32 minLength = mLength >= other.mLength ? other.mLength : mLength;
        return std::strncmp(mBuffer, other.mBuffer, minLength) >= 0;
    }

    bool NString::operator==(const NString &other) const {
        i32 minLength = mLength >= other.mLength ? other.mLength : mLength;
        return std::strncmp(mBuffer, other.mBuffer, minLength) == 0;
    }

    std::ostream &operator<<(std::ostream &os, const NString &obj) {
        return os.write(obj.raw().get(), obj.length());
    }

}