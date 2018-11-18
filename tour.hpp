//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#pragma once
#include "city.hpp"
#include <list>
#include <vector>
#include <chrono>
#include <random>

class tour {
    private:
        std::list<city> tour_list;
        double fitness_rating;
        int distance_travelled;

public:
    tour();
    explicit tour(std::list<city> tour_list);
    void add_city(const city & c);
    void random_shuffle_list();
    double get_fitness() const;
    void evaluate_fitness();
    void print_tour();
};
