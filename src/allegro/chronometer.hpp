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

#include <chrono>

using namespace std::chrono_literals;

class Chronometer {
public:
    Chronometer() {
        start();
    }

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        elapsed_counter += (std::chrono::high_resolution_clock::now() - start_time);
        start_time = std::chrono::high_resolution_clock::now();
    }

    void reset(void) {
        start_time = std::chrono::high_resolution_clock::now();
        elapsed_counter = std::chrono::nanoseconds::zero();
    }

    std::chrono::nanoseconds elapsed(void) {
        stop();
        return elapsed_counter;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock>    start_time;
    std::chrono::nanoseconds                                       elapsed_counter = 0ns;
};
