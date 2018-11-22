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
    crossover();
}

std::list<tour>
population::select_parents()
{
    std::list<tour> list_of_tours_to_cross;

    for (int i = 0; i < NUMBER_OF_PARENTS; ++i)
    {
        std::array<int, PARENT_POOL_SIZE> random_indeces {};

        for (int j = 0; j < static_cast<int>(random_indeces.size()); ++j)
        {
            random_indeces[j] = random_int(1, static_cast<int>(list_of_tours.size() - 1));
        }

        std::sort(random_indeces.begin(), random_indeces.end());

        auto tour_iterator = list_of_tours.begin();

        std::list<tour> parent_pool_tours;

        int count = 0;

        for (int j = 0; j < PARENT_POOL_SIZE; ++j)
        {
            while (count != random_indeces[j])
            {
                while (++tour_iterator == list_of_tours.end())
                {
                    break;
                }
                ++count;
            }
            parent_pool_tours.push_back(*tour_iterator);
        }

        parent_pool_tours.sort(tour_comparator());
        list_of_tours_to_cross.push_back(parent_pool_tours.front());
    }

    return list_of_tours_to_cross;
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
    std::cout << "Before Crossing Over" << std::endl;
    list_of_tours.sort(tour_comparator());
    for ( tour & x : list_of_tours)
    {
        std::cout << x;
    }

    std::list<tour> crosses;
    crosses.push_back(list_of_tours.front());

    // runs to repopulate all tour except the ELITE tour
    for (int k = 0; k < (int) list_of_tours.size() - 1; ++k)
    {
        crosses.push_back(crossover_parents(select_parents()));
    }

    list_of_tours = crosses;

    std::cout << "After Crossing Over" << std::endl;
    evaluation();
    list_of_tours.sort(tour_comparator());
    for (tour & x : list_of_tours)
    {
        std::cout << x;
    }
}

tour
population::crossover_parents(std::list<tour> list_of_tour_to_cross)
{
    list_of_tour_to_cross.sort(tour_comparator());
    // list of cities that are populated from parent tours
    tour mixed_tour;

    // array of random indices to populate the mixed_tour
    std::array<int, NUMBER_OF_PARENTS + 1> random_numbers {};

    int count = 0;

    // upper bound of the random numbers, its the number of cities in the tours
    int size_of_tours = list_of_tour_to_cross.front().get_numb_of_cities();

    // first index is always 0
    random_numbers[0] = 0;
    // random numbers to fill random indeces used to populate tours
    for (int i = 1; i < NUMBER_OF_PARENTS; ++i)
    {
        random_numbers[i] = random_int(0, size_of_tours);
    }
    // last index is always the max index
    random_numbers[NUMBER_OF_PARENTS] = size_of_tours - 1;

    // sort numbers so the indices are in ascending order
    std::sort(random_numbers.begin(), random_numbers.end());

    for (tour & x : list_of_tour_to_cross)
    {
        std::vector<city> temp = x.get_cities_in_vector();
        for (int i = count ? random_numbers[count] + 1 : random_numbers[count];
            i != random_numbers[count + 1] + 1 && i < size_of_tours; ++i)
        {
            int index_of_next_city = i;
            while (mixed_tour.contains_city(temp[index_of_next_city]))
            {
                if (++index_of_next_city == (int) temp.size())
                {
                    index_of_next_city = 0;
                }
            }
            mixed_tour.add_city(temp[index_of_next_city]);
        }
        ++count;
    }

    return mixed_tour;
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

std::ostream &
operator<<(std::ostream &os, const population & p)
{
    for (const tour & x : p.list_of_tours)
    {
        std::cout << x;
    }
    return os;
}
