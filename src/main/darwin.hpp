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

        population.resize(100);
    }

    template <typename T = int>
    static T uniform() {
        if constexpr( std::is_same<T, int>::value )
        {
            return instance->uniform_int(instance->engine);
        } else if ( std::is_same<T, float>::value ) {
            return instance->uniform_real(instance->engine);
        } else {
            return T();
        }
    }

    void tic() {
        for (auto &organism: population) {
            organism.tic();
        }
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

    std::vector<Entities::Organism>  population;
};

template <class Device, class Engine>
Controller<Device, Engine> * Controller<Device, Engine>::instance = nullptr;
	
}