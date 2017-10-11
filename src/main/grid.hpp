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
#include <tuple>

namespace Darwin::Main {
	
class coord_t {
public:
    coord_t() = default;

    coord_t(float x, float y)
            : x(x), y(y) {
    }

    coord_t operator+(float rhs) const;
    coord_t operator-(float rhs) const;
    coord_t operator*(float rhs) const;
    coord_t operator/(float rhs) const;

    coord_t & operator+=(const coord_t & rhs);

    template <std::size_t i>
    decltype(auto) get(void) const {
        if constexpr(i == 0) {
            return x;
        } else if constexpr (i == 1) {
            return y;
        }
    }

    static coord_t random(void);

    float x = 0, y = 0;
};

}

namespace std {

template<>
struct tuple_size<Darwin::Main::coord_t> : std::integral_constant<std::size_t, 2> {};

template<std::size_t i>
struct tuple_element<i, Darwin::Main::coord_t> {
    using type = decltype(std::declval<Darwin::Main::coord_t>().get<i>());
};

}