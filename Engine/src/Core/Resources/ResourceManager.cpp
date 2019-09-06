//
// Created by genkinger on 9/3/19.
//

#include "Nyarlathotep/Core/Resources/ResourceManager.hpp"

namespace ny::resources {
    ResourceManager::ResourceManager(i32 watchInterval) : mWatchInterval(watchInterval) {
        StartWatchThread();
    }

    void ResourceManager::StartWatchThread() {
        if (mWatchInterval < 0) throw std::runtime_error("Invalid watchInterval");
        if (mWatchInterval == 0) return;
        mWatchThreadRunning = true;
        mWatchThread = std::thread([&]() {
                                       std::cout << "Starting watch thread..." << std::endl;
                                       while (mWatchThreadRunning) {
                                           if (mMapMutex.try_lock()) {
                                               for (auto[key, value] : mResources) {
                                                   if (value->IsWatched()) {
                                                       if (!value->IsStaged()) {
                                                           if (value->HasChanged()) {
                                                               std::cout << "Resource " << key << " has changed! Staging for Reload..."
                                                                         << std::endl;
                                                               value->Stage();
                                                           }
                                                       } else {
                                                           std::cout << "Reloading Resource " << key << "..." << std::endl;
                                                           value->Reload();
                                                           std::cout << "Unstaging ..." << std::endl;
                                                           value->Unstage();
                                                       }
                                                   }
                                               }
                                               mMapMutex.unlock();
                                           }
                                           std::this_thread::sleep_for(std::chrono::milliseconds(mWatchInterval));
                                       }
                                   }
        );
    }

    void ResourceManager::StopWatchThread() {
        if (!mWatchThreadRunning) return;
        mWatchThreadRunning = false;
        if (mWatchThread.joinable()) {
            mWatchThread.join();
        }
    }

    ResourceManager::~ResourceManager() {
        StopWatchThread();
    }

}