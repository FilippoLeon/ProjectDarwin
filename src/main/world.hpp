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

#include "allegro/bitmap.hpp"

namespace Darwin::Main {

class coord_t;

class World {
public:
    static const int tileSizeX = 8, tileSizeY = 8, mapNLevels = 255;
    static const int tileSizeXw = tileSizeX + 1, tileSizeYw = tileSizeY + 1;
public:
    World(int width, int height)
            : width(width), height(height), size(width*height), map(tileSizeX, tileSizeY * mapNLevels) {

        food_map.resize(size, max_food);

        for(int z = 0; z < mapNLevels; ++z) {
            Allegro::Color color{z, 255 - z, 0};

            Allegro::Bitmap tile(tileSizeX, tileSizeY);
            {
                auto fut = Allegro::Allegro::set_target(tile, map);
                Allegro::Display::main->clear(color);
            }

            {
                auto fut = Allegro::Allegro::set_target(map);
                al_draw_bitmap_region(tile.get(), 0, 0, 10, 10, 0, z * tileSizeY, 0);
            }
        }
    } Allegro::Bitmap map;

    void tic() {

    }

    void draw() {
        al_hold_bitmap_drawing(true);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
//                map.draw(i * 5, j * 5, 0);
//                int z = (i + j) % 255;
                int z = std::max(0.f, std::floor((float) food_map[to_index(i, j)] / max_food * 254));
                al_draw_bitmap_region(map.get(), 0, z * tileSizeY, tileSizeX, tileSizeY, i * (tileSizeX+1), j * (tileSizeY+1), 0);
            }
        }
        al_hold_bitmap_drawing(false);
//        map.draw(0,0,0);
    }

    inline size_t to_index(size_t i, size_t j) {
        return i * height + j;
    }

    int to_index(coord_t position) {
        int xf = std::floor(position.x);
        int yf = std::floor(position.y);
        return height * xf + yf;
    }

    int try_drain_food(coord_t position, int amount, bool simulate) {
        int index = to_index(position);
        int available = std::min(food_map[index], max_food_drain_speed);
        int drainable = std::min(available, amount);
        if( !simulate ) {
            food_map[index] -= drainable;
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

    int max_food = 100;
    int max_food_drain_speed = 5;
private:
    std::vector<int> food_map;
};

	
} // END NAMESPACE Darwin::World
