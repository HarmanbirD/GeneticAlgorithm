//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#pragma once
#include "city.hpp"
#include <list>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>

constexpr double SCALAR = 10.45;

class tour {
    private:
        std::list<city> list_of_cities;
        double          fitness_rating;
        double          distance_travelled;

    public:
        tour();
        explicit tour(std::list<city> list_of_cities);

        auto add_city(const city & c)   -> void;
        auto shuffle_cities()           -> void;
        auto get_tour_distance()        -> void;
        auto get_fitness() const        -> double;
        auto determine_fitness()        -> void;
        auto print_tour() const         -> void;
        auto get_distance_between_cities(const city & one, const city & two) -> double;
};
