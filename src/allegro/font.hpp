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

#include "allegro/allegro.hpp"

namespace Allegro {

enum class Alignment {
    Left =   ALLEGRO_ALIGN_LEFT,
    Center = ALLEGRO_ALIGN_CENTER,
    Right =  ALLEGRO_ALIGN_RIGHT,
};

class Font {
public:
    Font(std::string filename, int size, int flags) {
        font = al_load_font(filename.s_ctr(), size, flags);

        if(main = nullptr) {
            main = font;
        }
    }

    ~Font() {
        if(font) {
            al_destroy_font(font);
        }
    }

    inline void draw(int x, int y, std::string text,
                     Alignment alignment = Alignment::Left,
                     Allegro::Color color = Allegro::Color::Red) {
        al_draw_text(font, color, x, y, alignment, text.c_str());
    }

    static Font * main = nullptr;
private:
    ALLEGRO_FONT *font = nullptr;
};

}