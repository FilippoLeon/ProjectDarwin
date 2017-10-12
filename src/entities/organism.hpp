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

#include "main/grid.hpp"

#include "entities/dispatcher.hpp"
#include "entities/genome.hpp"

#include "allegro/bitmap.hpp"
#include "allegro/display.hpp"

namespace Darwin::Entities {

class Organism : public Dispatcher<Organism> {
public:
    Organism();
    Organism(Organism &&) = default;
    Organism(const Organism &) = delete;
	Organism(Genome & genome);
    virtual ~Organism() = default;

	void tic(void);
    void draw(void);

    Main::coord_t get_position();

    void change_position(const Main::coord_t & delta);
    int drain_food(int amount);

    int size = 1;

    int food = 100;
    int min_food = 10;
    int max_food = 100;
    int max_food_store_rate = 5;

    int health = 100;
    int health_max = 100;
private:
	Genome genome;

    Main::coord_t position;

};

class OrganismBitmap : public Observer<Organism> {
public:
	OrganismBitmap(Organism* organism)
            : organism(organism), bitmap(10, 10) {
        {
            Allegro::ExpiringFuture fut = Allegro::Allegro::set_target(bitmap);
            Allegro::Display::main->clear(Allegro::Color(188,188,0));
        }
	}

    virtual void update() {

    }

	virtual void draw() {
        auto [x,y] = organism->get_position();
        bitmap.draw(x, y ,0);
	}
private:
    Allegro::Bitmap bitmap;

	Organism * organism;
};

}