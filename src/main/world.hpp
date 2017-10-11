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

#include <vector>
#include <limits>
#include <cmath>

#include "main/grid.hpp"

namespace Darwin::Main {

class coord_t;

class World {
public:
    World(int width, int height)
            : width(width), height(height), size(width*height) {

        food_map.resize(size);
    }

    int to_index(coord_t position) {
        int xf = std::floor(position.x);
        int yf = std::floor(position.y);
        return width * yf + xf;
    }

    int try_drain_food(coord_t position, int amount, bool simulate) {
        int index = to_index(position);
        int available = std::min(food_map[index], max_food_drain_speed);
        int drainable = std::min(available, amount);
        if( !simulate ) {
            food_map[index] -= to_index(position);
        }
        return drainable;
    }

    void bring_inside(coord_t & position) {
        if(position.x < 0) position.x = 0;
        if(position.x >= width) position.x = width - std::numeric_limits<float>::epsilon();
        if(position.y < 0) position.y = 0;
        if(position.y >= height) position.y = height - std::numeric_limits<float>::epsilon();
    }

    int width, height, size;

    int max_food_drain_speed = 5;
private:
    std::vector<int> food_map;
};

	
} // END NAMESPACE Darwin::World
