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

#include <allegro5/allegro5.h>

#include <boost/log/trivial.hpp>

#include <fmt/format.h>

#include "allegro/allegro.hpp"

namespace Allegro {

class Font {
public:

private:
    ALLEGRO_FONT *font = nullptr;
};

}