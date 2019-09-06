//
// Created by genkinger on 8/29/19.
//

#ifndef NYARLATHOTEP_SAMPLEMESSAGE_HPP
#define NYARLATHOTEP_SAMPLEMESSAGE_HPP

#include <Nyarlathotep/Core/String/NStringDepr.hpp>
#include "Message.hpp"

namespace ny{
    class SampleMessage : public Message{
        NString mString;
    public:
        SampleMessage(const NString &string) : Message(MessageType::WindowClose, MessageCategory::Window), mString(string){}
        NString& GetString(){return mString;}
    };
}
#endif //NYARLATHOTEP_SAMPLEMESSAGE_HPP
