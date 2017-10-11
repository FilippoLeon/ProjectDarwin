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

#include "entities/organism.hpp"

#include "main/darwin.hpp"

namespace Darwin::Entities {

Organism::Organism() {

}

Organism::Organism(Genome & genome) {
    genome.process_stats(*this);
}

void Organism::tic(void) {
    genome.process_position(*this);
    genome.process_food(*this);


    call([] (observer_p o) { o->update(); });
//		process_movement();
//		process_food();
}

Main::coord_t Organism::get_position() {
    return position;
}

void Organism::change_position(const Main::coord_t & delta) {
    position += delta;
    Main::Controller<>::instance->world.bring_inside(position);
}

int Organism::drain_food(int amount) {
    int delta = std::min(amount, food);
    food -= delta;
    return delta;
}


}