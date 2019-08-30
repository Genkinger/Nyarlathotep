//
// Created by genkinger on 8/29/19.
//

#ifndef NYARLATHOTEP_BUSNODE_HPP
#define NYARLATHOTEP_BUSNODE_HPP

#include <Nyarlathotep/Core/Core.hpp>
#include "MessageBus.hpp"
#include "Message.hpp"

namespace ny {

    class BusNode{
        MessageBus *mBus;
    protected:
        explicit BusNode(MessageBus *bus) : mBus(bus){
            mBus->addReceiver([=](const Message* message){
                onNotify(message);
            });
        }
        virtual void onNotify(const Message *message);
    };
}

#endif //NYARLATHOTEP_BUSNODE_HPP
