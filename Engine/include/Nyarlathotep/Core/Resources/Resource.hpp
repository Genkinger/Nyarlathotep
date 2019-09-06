//
// Created by genkinger on 9/4/19.
//

#ifndef NYARLATHOTEP_RESOURCE_HPP
#define NYARLATHOTEP_RESOURCE_HPP

#include <Nyarlathotep/Core/Core.hpp>

namespace ny::resources {
    class Resource {
    protected:
        bool mWatch;
        bool mStagedForReload;
    protected:
        Resource(bool watch);

    public:
        bool IsWatched() const;

        bool IsStaged() const;

        void SetWatched(bool watched);

        virtual bool HasChanged() const;

        virtual void Reload();

        void Stage();

        void Unstage();

        virtual ~Resource();
    };
}

#endif //NYARLATHOTEP_RESOURCE_HPP
