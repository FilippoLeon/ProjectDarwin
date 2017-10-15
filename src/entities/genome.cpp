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
#include <optional>

#include "main/darwin.hpp"
#include "main/grid.hpp"

#include "entities/organism.hpp"

namespace Darwin::Entities {

Genome::Genome() {

}

Genome Genome::mix(const Genome & other) const {

}

void Genome::process_food(Organism & organism) {
	if(organism.food < organism.max_food) {
        int delta = std::min(organism.max_food_store_rate, organism.max_food - organism.food);

        delta = Main::Controller<>::instance->world.try_drain_food(organism.get_position(), delta, true);

        Main::Controller<>::instance->world.try_drain_food(organism.get_position(), delta, false);
    }

    if(organism.food <= organism.min_food) {
        organism.change_health();
    } else if(organism.food >= organism.max_food_to_reproduce) {
        organism.reproduce();
    }
}

void Genome::process_position(Organism & organism) {
	organism.change_position( (Main::coord_t::random() * 2 - 1) / 1.f );

	organism.drain_food(5);
}

void Genome::process_stats(Organism & organism) {

}

}