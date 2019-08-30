//
// Created by genkinger on 8/29/19.
//

#ifndef NYARLATHOTEP_MESSAGE_HPP
#define NYARLATHOTEP_MESSAGE_HPP

#include <Nyarlathotep/Core/Core.hpp>

namespace ny{


    enum class MessageType{
        WindowResize, WindowClose,
        KeyDown, KeyUp, Key,
        MouseButtonDown, MouseButtonUp, MouseScroll, Other
    };

    enum class MessageCategory{
        Keyboard = BIT(0),
        Mouse = BIT(1),
        Window = BIT(2)
    };

    class Message{
    protected:
        Message(MessageType type, MessageCategory category) : mType(type), mCategory(category){}
        MessageType mType;
        MessageCategory mCategory;
    public:
        MessageType GetType() const {
            return mType;
        }

        MessageCategory GetCategory() const{
            return mCategory;
        }
    };
}

#endif //NYARLATHOTEP_MESSAGE_HPP
