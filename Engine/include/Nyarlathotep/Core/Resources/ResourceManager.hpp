//
// Created by genkinger on 9/3/19.
//

#ifndef NYARLATHOTEP_RESOURCEMANAGER_HPP
#define NYARLATHOTEP_RESOURCEMANAGER_HPP


#include <Nyarlathotep/Core/IO/File.hpp>
#include <thread>
#include <mutex>
#include "Resource.hpp"

namespace ny::resources {

    class ResourceManager {
        i32 mWatchInterval;
        bool mWatchThreadRunning;
        std::thread mWatchThread;
        std::map<String, std::shared_ptr<Resource>> mResources;
        std::mutex mMapMutex;

    public:
        ResourceManager(i32 watchInterval = 0);

        ~ResourceManager();

        void StartWatchThread();
        void StopWatchThread();

        template<typename T>
        std::shared_ptr<T> Get(const String &path, bool watch = false) {
            static_assert(std::is_base_of<Resource, T>::value, "Not a valid Resource");
            mMapMutex.lock();
            if (mResources.find(path) == mResources.end()) {
                mResources.emplace(path, std::make_shared<T>(path, watch));
            }
            auto ptr = mResources[path];
            mMapMutex.unlock();
            return std::static_pointer_cast<T>(ptr);

        }

    };


}


#endif //NYARLATHOTEP_RESOURCEMANAGER_HPP
