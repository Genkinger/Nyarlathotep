//
// Created by genkinger on 8/30/19.
//

#ifndef NYARLATHOTEP_FILESYSTEM_HPP
#define NYARLATHOTEP_FILESYSTEM_HPP

#include <Nyarlathotep/Core/Core.hpp>
#include <sys/stat.h>

namespace ny::io {
    class Filesystem {
    public:
        static bool FileExists(const NString &path);
        static i64 FileSize(const NString &path);
        static timespec LastModified(const NString &path);

        static std::shared_ptr<byte> ReadFile(const NString &path, const NString &mode = "rb");
        static NString ReadTextFile(const NString &path);

        static bool WriteFile(const NString &path, const byte* data, i64 length);
        static bool WriteTextFile(const NString &path, const NString &text);
    };
}


#endif //NYARLATHOTEP_FILESYSTEM_HPP
