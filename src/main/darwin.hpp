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

#include <array>
#include <random>

#include "main/world.hpp"

#include "entities/organism.hpp"

namespace Darwin::Main {

template <class Device = std::random_device, class Engine = std::default_random_engine>
class Controller {
public:
    Controller()
    : device(), engine(device())
    , uniform_int(0, 1)
    , uniform_real(0, 1)
    , world(100, 100) {
        instance = this;
    }

    void populate() {
        population.resize(20);
    }

    template <typename T = int>
    static T uniform() {
        if constexpr( std::is_same<T, int>::value )
        {
            return instance->uniform_int(instance->engine);
        } else if constexpr ( std::is_same<T, float>::value ) {
            return instance->uniform_real(instance->engine);
        } else {
            return T();
        }
    }

    bool random_event(float probability) {
        return uniform<float>() > probability;
    }

    void tic() {
        world.tic();
        for (auto &organism: population) {
            organism->tic();
        }
        ++long_tic_count;
        if(long_tic_count > long_tic_length) {
            long_tic_count = 0;
            long_tic();
        }
    }

    void long_tic() {
//        world.tic();
        for (auto &organism: population) {
            organism->long_tic();
        }
    }

    void draw() {
        world.draw();
        for (auto &organism: population) {
            organism->draw();
        }
    }

    void die(Entities::Organism* organism) {
        population.erase(
                std::find_if(population.begin(), population.end(),
                                      [organism] (decltype(*population.begin()) ptr) { return ptr.get() == organism; }));
    }

    void add(std::unique_ptr<Entities::Organism> && organism, const coord_t & position) {
        population.emplace_back(std::move(organism));
        organism->set_position(position);
    }

    static Controller<Device, Engine> * instance ;
private:

    Device          device;
    Engine          engine;
public:
    World           world;
private:
    std::uniform_int_distribution<int>     uniform_int;
    std::uniform_real_distribution<float>  uniform_real;

    std::vector<std::unique_ptr<Entities::Organism>>  population;

    static const int long_tic_length = 10;
    int long_tic_count = 0;
};

template <class Device, class Engine>
Controller<Device, Engine> * Controller<Device, Engine>::instance = nullptr;
	
}