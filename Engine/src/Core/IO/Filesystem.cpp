#include <memory>

//
// Created by genkinger on 8/30/19.
//

#include "Nyarlathotep/Core/IO/Filesystem.hpp"

namespace ny::io {

    bool Filesystem::FileExists(const ny::NString &path) {
        struct stat buf = {};
        return stat(path.raw().get(), &buf) == 0;
    }

    i64 Filesystem::FileSize(const ny::NString &path) {
        struct stat buf = {};
        stat(path.raw().get(), &buf);
        return buf.st_size;
    }

    timespec Filesystem::LastModified(const ny::NString &path) {
        struct stat buf = {};
        stat(path.raw().get(), &buf);
        return buf.st_mtim;
    }


    std::shared_ptr<byte> Filesystem::ReadFile(const ny::NString &path, const ny::NString &mode) {
        auto filesize = FileSize(path);
        auto file = fopen(path.raw().get(), mode.raw().get());
        if (!file) {
            std::cout << "Failed to open file!" << std::endl; //TODO: Remove this
            return nullptr;
        }
        auto buffer = new byte[filesize];

        auto readbytes = fread(buffer, 1, filesize, file);

        if (readbytes != filesize) {
            std::cout << "Only read " << readbytes << " bytes of expected " << filesize << "bytes!"
                      << std::endl; //TODO: Remove this
        }

        fclose(file);
        return std::shared_ptr<byte>(buffer);

    }

    NString Filesystem::ReadTextFile(const ny::NString &path) {
        return NString(ReadFile(path, "r").get(), FileSize(path));
    }

    bool Filesystem::WriteFile(const ny::NString &path, const byte *data, i64 length) {
        auto file = fopen(path.raw().get(), "wb");
        if (!file) {
            std::cout << "Failed to open file" << std::endl; //TODO: Remove this
            return false;
        }
        auto writtenbytes = fwrite(data, 1, length, file);
        if (writtenbytes != length) {
            std::cout << "Only wrote " << writtenbytes << " bytes of expected " << length << "bytes!"
                      << std::endl; //TODO: Remove this
        }
        fclose(file);
        return true;

    }

    bool Filesystem::WriteTextFile(const ny::NString &path, const ny::NString &text) {
        return WriteFile(path, text.raw().get(), text.length());
    }

}