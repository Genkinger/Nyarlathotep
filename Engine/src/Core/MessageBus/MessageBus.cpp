//
// Created by genkinger on 8/29/19.
//

#include <Nyarlathotep/Core/MessageBus/MessageBus.hpp>


namespace ny{

    void MessageBus::addReceiver(const Receiver &receiver) {
        mReceivers.push_back(receiver);
    }

    void MessageBus::sendMessageDeferred(const Message *message){
        mMessageQueue.push(message);
    }

    void MessageBus::sendMessageImmediate(const Message *message) {
        for(auto &receiver : mReceivers){
            receiver(message);
        }
    }

    void MessageBus::notify() {
        while(!mMessageQueue.empty()){
            for(auto &receiver : mReceivers){
                receiver(mMessageQueue.front());
            }
            mMessageQueue.pop();
        }
    }
}