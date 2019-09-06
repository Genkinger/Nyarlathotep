//
// Created by genkinger on 9/4/19.
//

#include "Nyarlathotep/Core/IO/File.hpp"


namespace ny::io {


    File::File(const ny::String &path) : mPath(path), mData(new byte[0]), mSize(0), mLastModified(0) {
        if (Exists(path)) {
            Load();
        }
    }

    File::~File() {
        delete[] mData;
    }

    u64 File::Size() const {
        return mSize;
    }

    struct stat File::Stat() const {
        struct stat buffer = {};
        stat(mPath, &buffer);
        return buffer;
    }

    void File::UpdateStat(struct stat buffer) {
        mSize = buffer.st_size;
        mLastModified = buffer.st_mtim.tv_sec;
    }

    StateChange File::GetChange() const {
        auto stat = Stat();
        if (stat.st_mtim.tv_sec != mLastModified) {
            return StateChange::MODIFIED;
        }
        return StateChange::NONE;
    }

    u64 File::LastModified() const {
        return mLastModified;
    }

    void File::Load() {
        std::lock_guard g(mFileMutex);
        if (!Exists(mPath))
            throw std::runtime_error("Unable to open File for reading!");

        auto stat = Stat();
        UpdateStat(stat);

        delete[] mData;
        mData = new byte[mSize];

        auto file = fopen(mPath, "rb");
        if (!file) throw std::runtime_error("Unable to open File for reading!");
        auto readbytes = fread(mData, 1, mSize, file);
        fclose(file);

        if (readbytes != mSize) throw std::runtime_error("Unexpected number of bytes!");
    }

    String File::ToString() const {
        return String(Get(), Size());
    }

    const byte *File::Get() const {
        return mData;
    }

    void File::Put(const byte *data, u64 size) {
        std::lock_guard g(mFileMutex);
        delete[] mData;
        mData = new byte[size];
        std::copy(data, data + size, mData);
        mSize = size;
    }

    void File::Append(const byte *data, u64 size) {
        std::lock_guard g(mFileMutex);
        byte *buffer = new byte[mSize + size];
        std::copy(mData, mData + mSize, buffer);
        std::copy(data, data + size, buffer + mSize);
        delete[] mData;
        mData = buffer;
        mSize += size;
    }

    void File::Clear() {
        std::lock_guard g(mFileMutex);
        delete[] mData;
        mData = new byte[0];
        mSize = 0;
    }

    void File::Write() {
        std::lock_guard g(mFileMutex);
        Write(mPath, mData, mSize);
    }

    bool File::Exists(const String &path) {
        struct stat buf = {};
        return stat(path, &buf) == 0;
    }

    u64 File::Size(const String &path) {
        struct stat buf = {};
        stat(path, &buf);
        return buf.st_size;
    }

    u64 File::LastModified(const String &path) {
        struct stat buf = {};
        stat(path, &buf);
        return buf.st_mtim.tv_sec;
    }

    void File::Write(const String &path, const byte *data, u64 size) {
        auto file = fopen(path, "wb");
        if (!file) throw std::runtime_error("Unable to open file for writing!");
        auto writtenbytes = fwrite(data, 1, size, file);
        fclose(file);
        if (writtenbytes != size) throw std::runtime_error("Unexpected number of bytes!");
    }
}