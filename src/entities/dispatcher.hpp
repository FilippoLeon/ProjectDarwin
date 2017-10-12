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
#include <memory>
#include <functional>

namespace Darwin::Entities {

template <class Subject>
class Observer {
public:
    virtual void update() {};
    virtual void draw() {};
};

template <class Subject>
class Dispatcher {
protected:
public:
	using observer_t = Observer<Subject>;
	using observer_p = std::unique_ptr<observer_t>;
	using factory_t = std::function<observer_p(Subject*)>;
public:
	Dispatcher() {
		for(auto factory: factories) {
			observers.emplace_back(factory(static_cast<Subject*>(this)));
		}
	}
    Dispatcher(Dispatcher &&) = default;

    virtual ~Dispatcher() = default;

	static void register_observer_factory(factory_t factory) {
		factories.push_back(factory);
	}

	template <class Functor>
	void call(Functor callback) {
		for(auto & observer: observers) {
			callback(observer);
		}
	}

protected:
	void attach(observer_p observer) {
		observers.push_back(observer);
	}

private:
	std::vector<observer_p> observers;

	static std::vector<factory_t> factories;
};

template <class Subject>
std::vector<typename Dispatcher<Subject>::factory_t> Dispatcher<Subject>::factories;

}