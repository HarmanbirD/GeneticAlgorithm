//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#pragma once

#include <list>
#include "tour.hpp"

class population {
    public:
        population();
        population(std::list<tour> list_of_tours);

    private:
        std::list<tour> list_of_tours;

};
