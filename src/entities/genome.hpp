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

#include <optional>
#include <vector>

#include "main/grid.hpp"

namespace Darwin::Entities {

class Organism;

class Gene {

};

class Genome {
public:
	Genome();

    Genome mix(const Genome & other) const;

    void process_food(Organism & organism);

	void process_position(Organism & organism);

    void process_stats(Organism & organism);

private:
	struct ActiveGene {
		std::optional<Gene> stats;
        std::optional<Gene> movement;
        std::optional<Gene> feeding;
	} active_genes;

	std::vector<Gene> inactive_genes;
};

}