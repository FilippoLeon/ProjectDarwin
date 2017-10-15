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
#include <iostream>

#include "allegro/display.hpp"
#include "allegro/bitmap.hpp"
#include "allegro/event.hpp"
#include "allegro/timer.hpp"
#include "allegro/font.hpp"

#include "main/darwin.hpp"
#include "entities/organism.hpp"

int main() {

    Allegro::Allegro allegro(Allegro::Component::All);

    Allegro::Display display(1200, 1200);
    Allegro::Font font("OpenSans-Regular.ttf", 14);

    Allegro::EventQueue event_queue;

    Allegro::Timer timer(1./60.);

//    Allegro::Bitmap image("image.png");

    timer.start();

    event_queue.register_source(display);
    event_queue.register_source(timer);

//    image.draw(10, 10, 0);


    Allegro::Bitmap image2(200, 200);
    {
        auto fut = allegro.set_target(image2, display);
        display.clear(Allegro::Color(244,244,1));
    }

    Darwin::Main::Controller<> main;

    Darwin::Entities::Dispatcher<Darwin::Entities::Organism>::register_observer_factory(
            [] (Darwin::Entities::Organism* o) {
                return std::move(std::make_unique<Darwin::Entities::OrganismBitmap>(o));
            }
    );

    Darwin::Entities::Organism organism;
    main.populate();

    display.toggle_fps(true);

    bool redraw = false;
    bool running = true;
    while( running ) {
        auto event = event_queue.wait();

        switch( event.get_type() ) {
            case Allegro::EventType::Timer:
                // Change objects state
//                organism.tic();
                main.tic();

                redraw = true;
                break;
            case Allegro::EventType::DisplayClose:
                running = false;
                break;
        }

        if(redraw && event_queue.empty()) {
            redraw = false;

            display.clear();

            main.draw();
//            auto [x, y] = organism.get_position();
//            image.draw(x ,y ,0);
//            image2.draw(x + 20, y+ 20, 0);;
//            image2.draw(x + 40, y+ 20, 0);;
//            image2.draw(x + 20, y+ 40, 0);

            display.flip();
        }
    }

//    display.flip();
//    display.rest(10);

    return 0;
}