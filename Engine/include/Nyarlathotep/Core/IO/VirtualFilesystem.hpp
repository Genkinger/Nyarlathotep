//
// Created by genkinger on 8/30/19.
//

#ifndef NYARLATHOTEP_VIRTUALFILESYSTEM_HPP
#define NYARLATHOTEP_VIRTUALFILESYSTEM_HPP

#include <Nyarlathotep/Core/Core.hpp>
#include <Nyarlathotep/Core/IO/Filesystem.hpp>

namespace ny::io {
    class VirtualFilesystem {
        std::map<NString, std::vector<NString>> mMountPoints;

    public:
        void Mount(const NString &virtualPath, const NString &physicalPath);
        void Umount(const NString &virtualPath);

        bool Resolve(const NString &path, NString &resolvedPath);

        NString ReadTextFile(const NString& virtualPath);
        std::shared_ptr<byte> ReadFile(const NString& virtualPath);
        
    };
}


#endif //NYARLATHOTEP_VIRTUALFILESYSTEM_HPP
