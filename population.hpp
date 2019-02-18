//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#pragma once

#include <iostream>
#include <array>
#include <list>
#include <iomanip>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "tour.hpp"

constexpr int    SHUFFLE{64};
constexpr int    PARENT_POOL_SIZE{8};
constexpr double IMPROVEMENT_FACTOR{0.45};

class population {
    public:
        population();
        explicit population(std::list<tour> list_of_tours);

        auto select_parents()                                                               -> std::list<tour>;
        auto evaluation()                                                                   -> void;
        auto crossover()                                                                    -> void;
        auto sort_tours()                                                                   -> void;
        auto mutation()                                                                     -> void;
        auto run_crossover()                                                                -> void;
        auto add_tour(const tour & t)                                                       -> void;
        auto get_coords(tour to_draw)                                                       -> void;
        auto crossover_parents(std::list<tour> list_of_tour_to_cross)                       -> tour;
        friend auto operator<< (std::ostream & os, const population & p)                    -> std::ostream &;
        auto contains_tour(const std::list<tour> & list_tour, const tour & other) const     -> bool;
        auto draw_map(const float & x1, const float & y1, const float & x2, const float & y2, const ALLEGRO_COLOR & color, const float & thickness) -> void;


        static const int    NUMBER_OF_PARENTS;
        static const int    NUMBER_OF_ELITES;
        static const int    ITERATION;

    private:
        std::list<tour> list_of_tours;
        double          base_distance;

};
