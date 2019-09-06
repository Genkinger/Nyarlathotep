//
// Created by genkinger on 9/4/19.
//

#ifndef NYARLATHOTEP_FILERESOURCE_HPP
#define NYARLATHOTEP_FILERESOURCE_HPP

#include <Nyarlathotep/Core/Core.hpp>
#include <Nyarlathotep/Core/IO/File.hpp>

#include "Resource.hpp"

namespace ny::resources {

    class FileResource : public Resource {
    protected:
        io::File mFile;
    public:
        FileResource(const String &physicalPath, bool autoReload);

        void Reload() override;

        bool HasChanged() const override;

        io::File *Get();
    };
}

#endif //NYARLATHOTEP_FILERESOURCE_HPP
