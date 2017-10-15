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
#include "allegro/display.hpp"

#include <allegro5/allegro.h>

#include "allegro/font.hpp"

namespace Allegro {

Display * Display::current = nullptr;
Display * Display::main = nullptr;

void Display::set_current() const {
    al_set_target_bitmap(current->get_backbuffer());
}

void Display::flip(void) {

    std::chrono::nanoseconds ns = timer.elapsed();
    float fps = 1000. / std::chrono::duration_cast<std::chrono::milliseconds>(ns).count();
    std::cout << fmt::format("-- {} ns // {:2.4} FPS--",
                             ns.count(),
                             fps);

    Font::main->draw(90_pct, 20, fmt::format("{:2.4}", fps));

    al_flip_display();

    timer.reset();
}


}