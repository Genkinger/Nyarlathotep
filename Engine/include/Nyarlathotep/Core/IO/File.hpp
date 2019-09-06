//
// Created by genkinger on 9/4/19.
//

#ifndef NYARLATHOTEP_FILE_HPP
#define NYARLATHOTEP_FILE_HPP

#include <Nyarlathotep/Core/Core.hpp>
#include <sys/stat.h>
#include <mutex>

namespace ny::io {

    enum class StateChange {
        NONE,
        MODIFIED,
        REMOVED
    };

    class File {
        String mPath;
        byte *mData;
        u64 mSize;
        u64 mLastModified;
        std::mutex mFileMutex;
    public:
        File(const String &path);

        ~File();

        void Load();

        struct stat Stat() const;

        void UpdateStat(struct stat buffer);

        u64 Size() const;

        u64 LastModified() const;

        StateChange GetChange() const;

        const byte *Get() const;

        void Put(const byte *data, u64 size);

        void Append(const byte *data, u64 size);

        void Clear();

        void Write();

        String ToString() const;

    public:
        static void Write(const String &path, const byte *data, u64 size);

        static bool Exists(const String &path);

        static u64 Size(const String &path);

        static u64 LastModified(const String &path);
    };
}


#endif //NYARLATHOTEP_FILE_HPP
