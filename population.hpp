//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#pragma once

#include <iostream>
#include <array>
#include <list>
#include "tour.hpp"

constexpr int    SHUFFLE{64};
constexpr int    ITERATION{1500};
constexpr int    PARENT_POOL_SIZE{5};
constexpr double IMPROVEMENT_FACTOR{0.4};

class population {
    public:
        population();
        explicit population(std::list<tour> list_of_tours);

        auto select_parents()                           -> std::list<tour>;
        auto evaluation()                               -> void;
        auto crossover()                                -> void;
        auto sort_tours()                               -> void;
        auto shuffle_population()                       -> void;
        auto mutation()                                 -> void;
        auto run_crossover()                            -> void;
        auto contains_tour(const std::list<tour> & list_tour, const tour & other) const    -> bool;
        auto crossover_parents(std::list<tour> list_of_tour_to_cross)     -> tour;
        friend auto operator<< (std::ostream & os, const population & p)  -> std::ostream &;
        template<typename T> static const T get_const(std::istream & in  = std::cin, const std::string & prompt = " ");

        static const int    NUMBER_OF_PARENTS;
        static const int    NUMBER_OF_ELITES;

    private:
            std::list<tour> list_of_tours;
            double          base_distance;

};
