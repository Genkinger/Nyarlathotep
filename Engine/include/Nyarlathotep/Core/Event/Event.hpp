//
// Created by genkinger on 8/29/19.
//

#ifndef NYARLATHOTEP_EVENT_HPP
#define NYARLATHOTEP_EVENT_HPP

namespace ny {

    enum class EventType {
        WindowResize, WindowClose,
        KeyDown, KeyUp, Key,
        MouseButtonDown, MouseButtonUp, MouseScroll, Sample
    };

    class Event {
    protected:
        EventType mType;
        explicit Event(EventType type): mType(type){};

    public:
        EventType GetType() {
            return mType;
        }
    };

    class SampleEvent : public Event {
    public:
        SampleEvent() : Event(EventType::Sample) {
        }
    };

    class KeyEvent: public Event {
    public:
        KeyEvent() : Event(EventType::Key) {
        }
    };
}


#endif //NYARLATHOTEP_EVENT_HPP
