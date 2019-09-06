//
// Created by genkinger on 9/4/19.
//

#ifndef NYARLATHOTEP_FARBFELDRESOURCE_HPP
#define NYARLATHOTEP_FARBFELDRESOURCE_HPP

#include <Nyarlathotep/Core/Core.hpp>
#include "FileResource.hpp"


//TODO: This is brittle code... endianness specific

namespace ny::resources {
    class FarbfeldResource : public FileResource {

        struct FarbfeldHeader {
            char magic[8];
            u32 width;
            u32 height;
        };
        FarbfeldHeader mHeader;
        u64 mSize;
    public:
        FarbfeldResource(const String &physicalPath, bool autoReload);

        void Reload() override;

        i32 GetWidth();
        i32 GetHeight();
        const byte* GetData();
        u64 GetDataSize();


    };
}

#endif //NYARLATHOTEP_FARBFELDRESOURCE_HPP
