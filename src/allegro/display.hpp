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

class Color {
public:
    Color(unsigned char r, unsigned char g, unsigned char b) {
        color = al_map_rgb(r, g, b);
    }

    inline operator ALLEGRO_COLOR() const {
        return color;
    }
private:
    ALLEGRO_COLOR color;
};

class Display {
public:
    Display (int width, int height) {
        init();
        create_display(width, height);
    }


    ~Display() {
        if (display) {
            al_destroy_display(display);
        }
    }

    inline void flip(void) {
        al_flip_display();
    }

    inline void rest(float time) {
        al_rest(10.0);
    }

    inline ALLEGRO_EVENT_SOURCE* event_source(void) const {
        return al_get_display_event_source(display);
    }

    inline void clear(Color color = Color(0,0,0)) {
        al_clear_to_color(color);
    }

    inline ALLEGRO_BITMAP* get_backbuffer() const {
        return al_get_backbuffer(display);
    }

protected:
    inline void init() {

    }

    inline void create_display(int width, int height) {
        display = al_create_display(width, height);
        if ( !display ) {
            BOOST_LOG_TRIVIAL(error) << "Failed to create display!";
            throw FailedDisplayInit();
        }

        al_clear_to_color(al_map_rgb(0,0,0));
    }


private:
    ALLEGRO_DISPLAY * display = nullptr;
};

}