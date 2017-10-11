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
#include "main/world.hpp"

#include "main/darwin.hpp"

namespace Darwin::Main {

coord_t coord_t::operator+(float rhs) const {
    return coord_t(x + rhs, y + rhs);
}

coord_t coord_t::operator-(float rhs) const {
    return coord_t(x - rhs, y - rhs);
}

coord_t coord_t::operator*(float rhs) const {
    return coord_t(x * rhs, y * rhs);
}

coord_t coord_t::operator/(float rhs) const {
    return coord_t(x / rhs, y / rhs);
}

coord_t & coord_t::operator+=(const coord_t &rhs) {
    x += rhs.x;
    y += rhs.y;
}

coord_t coord_t::random(void) {
    float x = Controller<>::instance->uniform<float>();
    float y = Controller<>::instance->uniform<float>();

    return coord_t(x, y);
}

}