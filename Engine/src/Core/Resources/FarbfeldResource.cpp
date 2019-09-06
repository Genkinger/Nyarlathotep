//
// Created by genkinger on 9/4/19.
//

#include <Nyarlathotep/Core/Resources/FarbfeldResource.hpp>
#include "string.h"

namespace ny::resources {
    FarbfeldResource::FarbfeldResource(const ny::String &physicalPath, bool autoReload) : FileResource(physicalPath,
                                                                                                        autoReload) {
        mFile.Load();
        const byte *data = mFile.Get();
        mHeader = *reinterpret_cast<const FarbfeldHeader*>(data);
        mHeader.width = swap_endian<u32>(mHeader.width);
        mHeader.height = swap_endian<u32>(mHeader.height);

        mSize = mFile.Size() - sizeof(FarbfeldHeader);
        if (strncmp("farbfeld", mHeader.magic, 8)) throw std::runtime_error("Invalid Farbfeld File!");
    }

    i32 FarbfeldResource::GetWidth() {
        return mHeader.width;
    }

    i32 FarbfeldResource::GetHeight() {
        return mHeader.height;
    }

    u64 FarbfeldResource::GetDataSize() {
        return mSize;
    }

    const byte *FarbfeldResource::GetData() { return mFile.Get() + sizeof(FarbfeldHeader); }

    void FarbfeldResource::Reload() {
        FileResource::Reload();
        const byte *data = mFile.Get();
        mHeader = *reinterpret_cast<const FarbfeldHeader*>(data);
        mSize = mFile.Size() - sizeof(FarbfeldHeader);
        mHeader.width = swap_endian<u32>(mHeader.width);
        mHeader.height = swap_endian<u32>(mHeader.height);
        if (!strncmp("farbfeld", mHeader.magic, 8)) throw std::runtime_error("Invalid Farbfeld File!");
    }

}