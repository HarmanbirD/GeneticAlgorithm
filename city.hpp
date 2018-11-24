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
        city(const city & other);
        ~city();

        auto get_x() const                      -> int;
        auto get_y() const                      -> int;
        auto get_name() const                   -> std::string;
        auto operator== (const city & m) const  -> bool;
        auto operator= (city m)                 -> city &;
        static auto swap(city & first, city & second)  -> void;
        friend auto operator<< (std::ostream & os, const city & c) -> std::ostream &;


};
