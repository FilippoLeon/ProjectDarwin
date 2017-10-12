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
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include <boost/log/trivial.hpp>

#include <fmt/format.h>

#include "tools/flagify.hpp"

#include "allegro/expiring_future.hpp"

namespace Allegro {

//class Display;

class FailedObjectCreation : public std::exception {};
class FailedAllegroInit : public std::exception {};
class FailedDisplayInit : public std::exception {};
class FileNotFound : public std::exception {
public:
    FileNotFound(std::string filename = "") {}
};

enum class Component {
    None =  0,
    Image = 1 << 0,
    Font =  1 << 1,
    All =   ~0,
}; FLAGIFY(Component);

class Allegro {
public:
    Allegro(Component component = Component::None){
        init(component);
    }

    ~Allegro() {
        if( image_init ){
            al_shutdown_image_addon();
        }
    }

    inline void init(Component component) {
        if( !al_init()) {
            BOOST_LOG_TRIVIAL(error) << "Failed to initialize Allegro!";
            throw FailedAllegroInit();
        }

        if( *(component & Component::Image) ) {
            if (!al_init_image_addon()) {
                BOOST_LOG_TRIVIAL(error) << "Failed to initialize the Image addon!";
                throw FailedAllegroInit();
            } else {
                BOOST_LOG_TRIVIAL(info) << "Loaded Image addon!";
                image_init = true;
            }
        }
        if( *(component & Component::Font) ) {
            if (!al_init_font_addon()) {
                BOOST_LOG_TRIVIAL(error) << "Failed to initialize the Font addon!";
                throw FailedAllegroInit();
            } else {
                BOOST_LOG_TRIVIAL(info) << "Loaded Font addon!";
                font_init = true;
            }
        }
    }

    template <class Image, class Display>
    [[nodiscard]]
    static inline decltype(auto) set_target(const Image & img, const Display & reset) {
        return ExpiringFuture(
                [&img] () { al_set_target_bitmap(img.get()); },
                [&reset] () { al_set_target_bitmap(reset.get_backbuffer()); }
        );
    }

    template <class Image>
    [[nodiscard]]
    static inline decltype(auto) set_target(const Image & img, const Image & reset) {
        return ExpiringFuture(
            [&img] () { al_set_target_bitmap(img.get()); },
            [&reset] () { al_set_target_bitmap(reset.get()); }
        );
    }

    template <class Image>
    [[nodiscard]]
    static inline decltype(auto) set_target(const Image & img);

    static ALLEGRO_PATH * Resources() {
        return al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    };

    static std::string Resources(std::string filename, char sep = ALLEGRO_NATIVE_PATH_SEP) {
        auto path = Allegro::Resources();
        al_set_path_filename(path, filename.c_str());
        return al_path_cstr(path, sep);
    }
private:
    bool image_init = false;
    bool font_init = false;

};

}

#include "allegro/display.hpp"