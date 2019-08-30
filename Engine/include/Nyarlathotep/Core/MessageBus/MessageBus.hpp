//
// Created by genkinger on 8/29/19.
//

#ifndef NYARLATHOTEP_MESSAGEBUS_HPP
#define NYARLATHOTEP_MESSAGEBUS_HPP

#include <Nyarlathotep/Core/Core.hpp>

#include "Message.hpp"

namespace ny{

    class MessageBus{
        using Receiver = std::function<void(const Message*)>;
        std::vector<Receiver> mReceivers;
        std::queue<const Message*> mMessageQueue;
    public:
        void addReceiver(const Receiver &receiver);
        void sendMessageDeferred(const Message *message);
        void sendMessageImmediate(const Message *message);
        void notify();
    };
}

#endif //NYARLATHOTEP_MESSAGEBUS_HPP
