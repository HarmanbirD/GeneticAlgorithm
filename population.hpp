//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#pragma once

#include <iostream>
#include <array>
#include <list>
#include "tour.hpp"

constexpr int    SHUFFLE{64};
constexpr int    ITERATION{1000};
constexpr int    PARENT_POOL_SIZE{5};
constexpr int    NUMBER_OF_PARENTS{3};
constexpr int    NUMBER_OF_ELITES{1};
constexpr double MUTATION_RATE{0.15};

class population {
    public:
        population();
        explicit population(std::list<tour> list_of_tours);

        auto select_parents()                           -> std::list<tour>;
        auto evaluation()                               -> void;
        auto crossover()                                -> void;
        auto random_int(const int & x, const int & y)   -> int;
        auto crossover_parents(std::list<tour> list_of_tour_to_cross)     -> tour;
        friend auto operator<< (std::ostream & os, const population & p)  -> std::ostream &;

private:
        std::list<tour> list_of_tours;
        double          base_distance;

};
