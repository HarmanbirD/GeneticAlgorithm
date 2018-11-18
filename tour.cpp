//
// Created by Harmanbir Dhillon on 2018-11-12.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "tour.hpp"

std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count() );

template <class T > void listShuffle(std::list<T> &L )
{
    std::vector<T> V( L.begin(), L.end() );
    shuffle(V.begin(), V.end(), gen);
    L.assign( V.begin(), V.end() );
}


tour::tour()
{}

tour::tour(std::list<city> tour_list)
: tour_list{std::move(tour_list)}
{
    random_shuffle_list();
    evaluate_fitness();
}

void
tour::random_shuffle_list()
{
    std::vector<city> to_shuffle(tour_list.begin(), tour_list.end());
    std::random_shuffle(to_shuffle.begin(), to_shuffle.end());
    std::copy(to_shuffle.begin(), to_shuffle.end(), tour_list.begin());
}

void
tour::evaluate_fitness()
{
    distance_travelled = 0;
    std::list<city>::iterator iterator;
    std::list<city>::iterator iterator_next;
    for (iterator = tour_list.begin(); iterator != tour_list.end();)
    {
        int x  = iterator->get_x();
        int y  = iterator->get_y();

        if (++iterator == tour_list.end())
        {
            break;
        }
        int x2 = iterator->get_x();
        int y2 = iterator->get_y();

        int distance_one = x + y;
        int distance_two = x2 + y2;

        int temoem = abs(distance_two - distance_one);
        distance_travelled += temoem;
    }
}

void
tour::add_city(const city & c)
{
    tour_list.push_back(c);
}

double
tour::get_fitness() const
{
    return fitness_rating;
}

void
tour::print_tour()
{
    for (city &x : tour_list)
    {
        x.print_city();
    }
    std::cout << distance_travelled << "\n" << std::endl;
}
