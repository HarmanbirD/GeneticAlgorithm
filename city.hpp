//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#pragma once

#include <string>
#include <stdexcept>

constexpr int MAP_BOUNDARY_HIGH = 1000;
constexpr int MAP_BOUNDARY_LOW  = 0;


class city {
    private:
        std::string name;
        int x;
        int y;

    public:
        city();
        city(std::string name, int x, int y);
        int get_x() const;
        int get_y() const;
        void print_city();
        ~city();
};
