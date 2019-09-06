//
// Created by genkinger on 9/4/19.
//

#include <Nyarlathotep/Core/Resources/Resource.hpp>

namespace ny::resources {
    Resource::Resource(bool watch) : mWatch(watch) {}

    Resource::~Resource() {
        std::cout << "DESTROYED RESOURCE" << std::endl;
    }

    bool Resource::IsWatched() const { return mWatch; }

    void Resource::SetWatched(bool watch) { mWatch = watch; }

    bool Resource::HasChanged() const { return false; }

    void Resource::Stage() {
        mStagedForReload = true;
    }

    void Resource::Unstage() {
        mStagedForReload = false;
    }

    bool Resource::IsStaged() const {
        return mStagedForReload;
    }

    void Resource::Reload() {}
}

