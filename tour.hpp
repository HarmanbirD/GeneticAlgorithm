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

constexpr double SCALAR{1000.45};
constexpr double epsilon{0.00000001};
constexpr int    MUTATION_RATE{15};

class tour {
    private:
        std::list<city> list_of_cities;
        int             number_of_cities;
        double          fitness_rating;
        double          distance_travelled;

    public:
        tour();
        explicit tour(std::list<city> list_of_cities);

        auto add_city(const city & c)               -> void;
        auto shuffle_cities()                       -> void;
        auto calculate_tour_distance()              -> void;
        auto determine_fitness()                    -> void;
        auto calculate_numb_of_cities()             -> void;
        auto swap_city()                            -> void;
        auto get_numb_of_cities() const             -> int;
        auto contains_city(const city & m) const    -> bool;
        auto operator< (const tour & m) const       -> bool;
        auto operator== (const tour & m) const      -> bool;
        auto get_fitness() const                    -> double;
        auto get_distance_travelled() const         -> double;
        auto operator= (tour m)                     -> tour &;
        auto get_cities_in_vector()                 -> std::vector<city>;
        auto random_int(const int & x, const int & y) const                         -> int;
        auto get_distance_between_cities(const city & one, const city & two) const  -> double;
        friend auto is_equal(const tour & one, const tour & two)                    -> bool;
        friend auto swap(tour & first, tour & second)                               -> void;
        friend auto operator<< (std::ostream & os, const tour & t)                  -> std::ostream &;

};
