//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#include "population.hpp"

struct tour_comparator
{
    bool operator() (const tour & one, const tour & two)
    {
        return !(one < two);
    }
};

population::population() = default;

population::population(std::list<tour> list_of_tours)
: list_of_tours{std::move(list_of_tours)}
{
    select_parents();
    print_population();
}

void
population::select_parents()
{
    list_of_tours.sort(tour_comparator());
}

void
population::print_population() const
{
    for (const tour & x : list_of_tours)
    {
        x.print_tour();
    }
}

void
population::evaluation()
{
    for (tour & x : list_of_tours)
    {
        x.determine_fitness();
    }
}

void
population::crossover()
{
    std::list<tour> crosses;

    for (auto i = list_of_tours.begin(); i != list_of_tours.end();)
    {
        std::list<tour> temp_tour;
        for (int j = 0; j < PARENT_POOL_SIZE; ++j)
        {
            if (++i != list_of_tours.end())
            {
                temp_tour.push_back(*i);
            } else
            {
                break;
            }
        }
        crossover_parents(temp_tour);
    }
}

tour
population::crossover_parents(std::list<tour> & list_of_tour_to_cross)
{
    // list of cities that are populated from parent tours
    tour mixed_tour;

    // array of random indices to populate the mixed_tour
    std::array<int, NUMBER_OF_PARENTS> random_numbers {};

    int count = 0;

    // upper bound of the random numbers, its the number of cities in the tours
    int size_of_tours = list_of_tour_to_cross.front().get_numb_of_cities();

    for (int i = 0; i < NUMBER_OF_PARENTS; ++i)
    {
        random_numbers[i] = random_int(0, size_of_tours);
    }

    for (tour & x : list_of_tour_to_cross)
    {
        std::vector<city> temp = x.get_cities_in_vector();
        for (int i = random_numbers[count++]; i != random_numbers[count] && count < random_numbers.size(); ++i)
        {
            int index_of_next_city = i;

            while (mixed_tour.contains_city(temp[index_of_next_city]))
            {
                ++index_of_next_city;
            }
            mixed_tour.add_city(temp[index_of_next_city]);
        }
    }


    return tour();
}

int
population::random_int(const int & x, const int & y)
{
    // return random int
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(x,y);
    return uni(rng);
}