//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#pragma once

#include <list>
#include "tour.hpp"

constexpr int    SHUFFLE{64};
constexpr int    ITERATION{1000};
constexpr int    PARENT_POOL_SIZE{5};
constexpr int    NUMBER_OF_PARENTS{};
constexpr int    NUMBER_OF_ELITES{1};
constexpr double MUTATION_RATE{0.15};

class population {
    public:
        population();
        explicit population(std::list<tour> list_of_tours);

        auto select_parents() -> void;
        auto evaluation() -> void;
        auto print_population() const -> void;
        auto crossover() -> void;
        auto random_int(const int & x, const int & y) -> int;
        auto crossover_parents(std::list<tour> & list_of_tour_to_cross) -> tour;

    private:
        std::list<tour> list_of_tours;
        double          base_distance;

};
