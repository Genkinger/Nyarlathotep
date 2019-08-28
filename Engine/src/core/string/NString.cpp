//
// Created by genkinger on 8/27/19.
//

#include "NString.hpp"

#include <cstring>
#include <iostream>

namespace Ny {

    NString::~NString() {
        delete[] mBuffer;
    }

    NString::NString(const char *string) {
        mLength = strlen(string);
        mBuffer = new char[mLength];
        strncpy(mBuffer, string, mLength);
    }

    NString::NString(const NString &string) {
        mLength = string.mLength;
        mBuffer = new char[mLength];
        strncpy(mBuffer, string.mBuffer, mLength);
    }

    i32 NString::resize(i32 length) {
        char *buffer = new char[length];
        memset(buffer, 0, length);
        if (length >= mLength) {
            strncpy(buffer, mBuffer, mLength);
        } else {
            strncpy(buffer, mBuffer, length);
        }
        delete[] mBuffer;
        mBuffer = buffer;
        int oldSize = mLength;
        mLength = length;
        return oldSize;
    }

    NString NString::substring(const i32 start, const i32 length) const {
        char sub[length + 1];
        for (int i = start; i < start + length + 1; i++) {
            sub[i - start] = mBuffer[i];
        }
        sub[length + 1] = '\0';
        return NString(sub);
    }

    std::vector<NString> NString::split(const char delimiter) const {
        NString current;
        std::vector<i32> indices;
        for (int i = 0; i < length(); i++) {
            if (mBuffer[i] == delimiter) {
                indices.push_back(i);
            }
        }

        std::vector<NString> result;
        if (!indices.empty()) {
            i32 lastIndex = 0;
            for (int index : indices) {
                if (index - lastIndex >= 1) {
                    result.push_back(substring(lastIndex, index - lastIndex - 1));
                }
                lastIndex = index + 1;
            }
            result.push_back(substring(indices[indices.size() - 1] + 1, length() - indices[indices.size() - 1]));
        } else {
            result.push_back(*this);
        }
        return result;
    }

    bool NString::contains(const char c) const {
        for (int i = 0; i < length(); i++) {
            if (c == mBuffer[i]) return true;
        }
        return false;
    }

    i32 NString::count(const char c) const {
        i32 count = 0;
        for (int i = 0; i < length(); i++) {
            if (c == mBuffer[i]) count++;
        }
        return count;
    }

    NString NString::replace(const char find, const char replace) const {
        NString result = *this;
        for (int i = 0; i < result.length(); i++) {
            if (result.mBuffer[i] == find) {
                result.mBuffer[i] = replace;
            }
        }
        return result;
    }

    bool NString::begins(const NString &string) const {
        return !strncmp(mBuffer,string.mBuffer,string.length());
    }

    bool NString::contains(const NString &string) const {
        //TODO: implement this
        return false;
    }

    i32 NString::length() const {
        return mLength;
    }

    const char *NString::raw() const {
        return mBuffer;
    }

    NString NString::operator+(const NString &rightHand) {
        return NString(*this) += rightHand;
    }

    NString NString::operator+(const char rightHand) {
        return NString(*this) += rightHand;
    }

    NString NString::operator*(const i32 count) {
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

    NString NString::operator+=(const char rightHand) {
        resize(mLength+1);
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

    char& NString::operator[](const i32 index) {
        return mBuffer[index];
    }

    std::ostream &operator<<(std::ostream &os, const NString &obj) {
        return os.write(obj.raw(), obj.length());
    }


}