//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#include <iostream>
#include "city.hpp"

city::city()
: name{"Vancouver"}, x{0}, y{0}
{}

city::city(std::string name, int x, int y)
: name{std::move(name)}, x{x}, y{y}
{
    if (x < MAP_BOUNDARY_LOW || x > MAP_BOUNDARY_HIGH)
    {
        throw std::invalid_argument("X coordinate must be greater than 0 and less than 1000");
    }
    if (y < MAP_BOUNDARY_LOW || y > MAP_BOUNDARY_HIGH)
    {
        throw std::invalid_argument("Y coordinate must be greater than 0 and less than 1000");
    }
}

int
city::get_x() const {
    return x;
}

int
city::get_y() const {
    return y;
}

void
city::print_city()
{
    std::cout << name << "[" << x << ", " << y << "]" << std::endl;
}

city::~city() = default;