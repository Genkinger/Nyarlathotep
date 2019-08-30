//
// Created by genkinger on 8/30/19.
//

#include "Nyarlathotep/Core/IO/VirtualFilesystem.hpp"

namespace ny::io {


    void VirtualFilesystem::Mount(const ny::NString &virtualPath, const ny::NString &physicalPath) {
        if (!physicalPath.ends("/")) {
            mMountPoints[virtualPath].push_back(physicalPath + "/");
        } else {
            mMountPoints[virtualPath].push_back(physicalPath);
        }
    }

    void VirtualFilesystem::Umount(const ny::NString &virtualPath) {
        mMountPoints[virtualPath].clear();
    }

    bool VirtualFilesystem::Resolve(const ny::NString &path, NString &resolvedPath) {
        for (auto[key, value] : mMountPoints) {
            if (path.begins(key)) {
                auto rest = path.substring(key.length());
                for (auto &physicalPart : value) {
                    NString fullPath = physicalPart + rest;
                    if (Filesystem::FileExists(fullPath)) {
                        resolvedPath = fullPath;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    NString VirtualFilesystem::ReadTextFile(const ny::NString &virtualPath) {
        NString resolvedPath;
        if (Resolve(virtualPath, resolvedPath)) {
            return Filesystem::ReadTextFile(resolvedPath);
        }
        return "";
    }

    std::shared_ptr<byte> VirtualFilesystem::ReadFile(const ny::NString &virtualPath) {
        NString resolvedPath;
        if (Resolve(virtualPath, resolvedPath)) {
            return Filesystem::ReadFile(resolvedPath);
        }
        return nullptr;
    }

}
