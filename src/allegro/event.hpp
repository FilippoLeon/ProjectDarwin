//
//  Copyright 2017 Filippo Leonardi
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//          http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//          limitations under the License.
//
//
// Created by filippo on 10/10/17.
//
#pragma once

#include <allegro5/allegro5.h>

#include <boost/log/trivial.hpp>

#include "allegro/allegro.hpp"

namespace Allegro {

enum class EventType {
    Timer = ALLEGRO_EVENT_TIMER,
    DisplayClose = ALLEGRO_EVENT_DISPLAY_CLOSE,
};

class EventQueue;

class Event {
    using al_ev_t = decltype(ALLEGRO_EVENT::type);
    Event(const ALLEGRO_EVENT & ev) {
        switch(ev.type) {
            case (al_ev_t) EventType::Timer:
                type = EventType::Timer;
                break;
            case (al_ev_t) EventType::DisplayClose:
                type = EventType::DisplayClose;
                break;
        }
    }

    friend EventQueue;
public:
    EventType get_type() {
        return type;
    }
private:
    EventType type;
};

class EventQueue {
public:
    EventQueue() {
        event_queue = al_create_event_queue();
        if( !event_queue ) {
            BOOST_LOG_TRIVIAL(error) << "Failed to create event queue!";
            throw FailedObjectCreation();
        }

    }

    template <class Object>
    inline void register_source(const Object & obj) {
        al_register_event_source(event_queue, obj.event_source());
    }

    ~EventQueue() {
        if(event_queue) {
            al_destroy_event_queue(event_queue);
        }
    }

    inline bool empty() {
        return al_is_event_queue_empty(event_queue);
    }

    inline Event wait() {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        return Event(ev);
    }

private:
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
};

}