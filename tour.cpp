//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#include "tour.hpp"

tour::tour()
: fitness_rating{0}, distance_travelled{0}
{}

tour::tour(std::list<city> list_of_cities)
: list_of_cities{std::move(list_of_cities)}, fitness_rating{0}, distance_travelled{0}
{
    shuffle_cities();
    determine_fitness();
}

void
tour::shuffle_cities()
{
    std::vector<city> to_shuffle(list_of_cities.begin(), list_of_cities.end());
    std::random_shuffle(to_shuffle.begin(), to_shuffle.end());
    std::copy(to_shuffle.begin(), to_shuffle.end(), list_of_cities.begin());
}

void
tour::determine_fitness()
{
    get_tour_distance();
    fitness_rating = 1.0 / distance_travelled * SCALAR;
}

double
tour::get_distance_between_cities(const city & one, const city & two)
{
    double first_city  = one.get_x() + one.get_y();
    double second_city = two.get_x() + two.get_y();
    return abs(second_city - first_city);
}

void
tour::add_city(const city & c)
{
    list_of_cities.push_back(c);
}

double
tour::get_fitness() const
{
    return fitness_rating;
}

void
tour::print_tour() const
{
    for (const city & x : list_of_cities)
    {
        x.print_city();
    }
    std::cout << fitness_rating << "\n" << distance_travelled << "\n" << std::endl;
}

void
tour::get_tour_distance()
{
    std::list<city>::iterator iterator;
    std::list<city>::iterator iterator_next;
    for (iterator = list_of_cities.begin(); iterator != list_of_cities.end();)
    {
        city temp = *iterator++;
        if (iterator == list_of_cities.end())
        {
            return;
        }
        city temp_two = *iterator;

        double erer = get_distance_between_cities(temp, temp_two);
        distance_travelled += erer;
    }
}
