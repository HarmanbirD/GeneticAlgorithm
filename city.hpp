//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

constexpr int MAP_BOUNDARY_HIGH = 1000;
constexpr int MAP_BOUNDARY_LOW  = 0;


class city {

    private:
        std::string name;
        int         x;
        int         y;

    public:
        city();
        city(std::string name, int x, int y);
        ~city();

        auto get_x() const                      -> int;
        auto get_y() const                      -> int;
        auto get_name() const                   -> std::string;
        auto print_city() const                 -> void;
        auto operator== (const city & m) const  -> bool;

};
