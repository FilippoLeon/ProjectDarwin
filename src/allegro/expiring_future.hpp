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

namespace Allegro {

template <class T>
class ExpiringFuture {
public:
    template <class L>
    ExpiringFuture(const L& pre, const T& post) : post_(post) {
        pre();
    }

    ExpiringFuture(const ExpiringFuture<T>& other) = delete;

    ExpiringFuture(ExpiringFuture<T>&& other)
            : post_(std::move(other.post_)) {
    }

    ~ExpiringFuture() {
        post_();
    }

private:
    T post_;
};

template <class T, class L>
auto make_ExpiringFuture(const L& pre,
                          const T& post) {
    return ExpiringFuture<
            typename std::remove_reference<T>::type
    >(pre, post);
}

}