//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#include "city.hpp"
#include "templates.hpp"

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

city::city(std::string name)
: name{std::move(name)}, x{random_int(MAP_BOUNDARY_LOW, MAP_BOUNDARY_HIGH)}, y{random_int(MAP_BOUNDARY_LOW, MAP_BOUNDARY_HIGH)}
{}

city::city(const city & other)
: name{other.name}, x{other.x}, y{other.y}
{}

int
city::get_x() const
{
    return x;
}

int
city::get_y() const
{
    return y;
}

std::string
city::get_name() const
{
    return name;
}

bool
city::operator==(const city & m) const
{
    return this->name == m.get_name() && this->x == m.get_x() && this->y == m.get_y();
}

city &
city::operator=(city m) {
    swap(*this, m);
    return *this;
}

void
city::swap(city & first, city & second)
{
    std::swap(first.name, second.name);
    std::swap(first.x, second.x);
    std::swap(first.y, second.y);
}

std::ostream &
operator<<(std::ostream & os, const city &c)
{
    std::ostringstream temp;
    temp << c.name << " [" << std::setw(4) << c.x << ", " << std::setw(4) << c.y << "]";
    std::string temp_string = temp.str();
    os  << std::right <<  std::setw(55) << temp_string << std::endl;
    return os;
}

auto city::operator!=(const city &m) const -> bool {
    return !operator==(m);
}

int
city::random_int(const int & x, const int & y)
{
    // return random int
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(x,y);
    return uni(rng);
}

city::~city() = default;
