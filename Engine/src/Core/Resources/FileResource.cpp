//
// Created by genkinger on 9/4/19.
//

#include <Nyarlathotep/Core/Resources/FileResource.hpp>

namespace ny::resources {

    FileResource::FileResource(const String &physicalPath, bool autoReload) : Resource(autoReload),
                                                                               mFile(physicalPath) {}

    io::File *FileResource::Get() {
        return &mFile;
    }

    void FileResource::Reload() {
        mFile.Load();
    }

    bool FileResource::HasChanged() const {
        return mFile.GetChange() == io::StateChange::MODIFIED;
    }
}