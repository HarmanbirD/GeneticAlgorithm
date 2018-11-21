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
}

void
population::select_parents()
{
    list_of_tours.sort(tour_comparator());
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

    // array of random indices to populate the mixed_tour
    std::array<int, PARENT_POOL_SIZE> random_numbers {};


    // runs to repopulate all tour except the ELITE tour
    for (int k = 0; k < (int) list_of_tours.size() - 1; ++k)
    {
        // list that contains all parent tours to cross
        std::list<tour> list_of_tours_to_cross;
        // runs number of parents times
        for (int j = 0; j < NUMBER_OF_PARENTS; ++j)
        {
            // runs number of parent pool size time
            for (int i = 0; i < PARENT_POOL_SIZE; ++i)
            {
                random_numbers[i] = random_int(1, (int) list_of_tours.size() - 1);
            }

            // sorts random numbers so they are all in ascending order
            std::sort(random_numbers.begin(), random_numbers.end());

            auto i = list_of_tours.begin();

            // list that contains randomly selected PARENT_POOL_SIZE tours
            std::list<tour> temp_tour;

            for (int t = 0; t < PARENT_POOL_SIZE; ++t)
            {
                int count = 0;
                while (count != random_numbers[t])
                {
                    if (++i == list_of_tours.end())
                    {
                        break;
                    }
                    ++count;
                }
                temp_tour.push_back(*i);
            }

            temp_tour.sort(tour_comparator());
            list_of_tours_to_cross.push_back(temp_tour.front());
        }
        crosses.push_back(crossover_parents(list_of_tours_to_cross));
    }
    auto it = list_of_tours.begin();
    std::copy(crosses.begin(), crosses.end(), ++it);
}

tour
population::crossover_parents(std::list<tour> & list_of_tour_to_cross)
{
    list_of_tour_to_cross.sort(tour_comparator());
    // list of cities that are populated from parent tours
    tour mixed_tour;

    // array of random indices to populate the mixed_tour
    std::array<int, NUMBER_OF_PARENTS + 1> random_numbers {};

    int count = 0;

    // upper bound of the random numbers, its the number of cities in the tours
    int size_of_tours = list_of_tour_to_cross.front().get_numb_of_cities();

    random_numbers[0] = 0;
    for (int i = 1; i < NUMBER_OF_PARENTS; ++i)
    {
        random_numbers[i] = random_int(0, size_of_tours);
        std::cout << "random number [" << i << "] = " << random_numbers[i] << std::endl;
    }
    random_numbers[NUMBER_OF_PARENTS] = size_of_tours;

    std::sort(random_numbers.begin(), random_numbers.end());

    for (tour & x : list_of_tour_to_cross)
    {
        std::cout << x;
        std::vector<city> temp = x.get_cities_in_vector();
        for (int i = random_numbers[count]; i != random_numbers[count + 1] && !count + 1 < (int) random_numbers.size(); ++i)
        {
            if (i == (int) temp.size())
            {
                i = 0;
            }
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
