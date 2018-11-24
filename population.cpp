//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#include "population.hpp"

const int population::NUMBER_OF_PARENTS = get_const<int>(std::cin, "Enter number of parents");
const int population::NUMBER_OF_ELITES  = get_const<int>(std::cin, "Enter number of elites");

template<typename T>
const T population::get_const(std::istream & in, const std::string & prompt)
{
    T x;
    std::cout << prompt;
    if (!(in >> x))
    {
        throw "Invalid input";
    }
    return x;
}

template<typename T>
void bubble_sort(T * arr, int x)
{
    bool exchanges;
    do {
        exchanges = false;  // assume no exchanges
        for (int i=0; i<x-1; i++)
        {
            if (arr[i] > arr[i+1])
            {
                T temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                exchanges = true;  // after exchange, must look again
            }
        }
    } while (exchanges);
}

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
    sort_tours();
    run_crossover();
}

std::list<tour>
population::select_parents()
{
    std::list<tour> list_of_tours_to_cross;

    for (int i = 0; i < NUMBER_OF_PARENTS; ++i)
    {
        std::array<int, PARENT_POOL_SIZE> random_indices {};

        for (int j = 0; j < PARENT_POOL_SIZE; ++j)
        {
            random_indices[j] = random_int(NUMBER_OF_ELITES, static_cast<int>(list_of_tours.size() - 1));
//            std::cout << "random indices: " << random_indices[j] << std::endl;
        }

        std::sort(random_indices.begin(), random_indices.end());

        auto tour_iterator = list_of_tours.begin();

        std::list<tour> parent_pool_tours;

        int count = NUMBER_OF_ELITES;

        for (int j = 0; j < count; ++j)
        {
            ++tour_iterator;
        }

        for (const int & j : random_indices)
        {
            while (count != j)
            {
                if (++tour_iterator == list_of_tours.end())
                {
                    break;
                }
                ++count;
            }
            parent_pool_tours.push_back(*tour_iterator);
        }
        parent_pool_tours.sort(tour_comparator());
//        std::cout<<"list of parent pool tours" << std::endl;
//
//        for (tour & x : parent_pool_tours)
//        {
//            std::cout << x;
//        }
        if (contains_tour(list_of_tours_to_cross, parent_pool_tours.front()))
        {
            --i;
        }
        else
        {
            list_of_tours_to_cross.push_back(parent_pool_tours.front());
        }
    }
//
//    std::cout<<"list of tour to cross" << std::endl;
//
//    for (tour & x : list_of_tours_to_cross)
//    {
//        std::cout << x;
//    }

    return list_of_tours_to_cross;
}

void
population::sort_tours()
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

    auto iterator_for_elite_tour = list_of_tours.begin();
    for (int i = 0; i < NUMBER_OF_ELITES; ++i)
    {
        crosses.push_back(*iterator_for_elite_tour);
        ++iterator_for_elite_tour;
    }

    // runs to repopulate all tour except the ELITE tour(s)
    for (int k = 0; k < static_cast<int>(list_of_tours.size() - NUMBER_OF_ELITES); ++k)
    {
        crosses.push_back(crossover_parents(select_parents()));
    }

    list_of_tours = crosses;
//    evaluation();
//    std::cout << "\n\n\n\n" << std::endl;
//    for (tour & x : list_of_tours)
//    {
//        double a = x.get_distance_travelled();
//        std::cout << a << std::endl;
//    }
    mutation();
    evaluation();
    sort_tours();
    std::cout << "\n\n\n\n" << std::endl;
    for (tour & x : list_of_tours)
    {
        double a = x.get_distance_travelled();
        std::cout << a << std::endl;
    }
}

tour
population::crossover_parents(std::list<tour> list_of_tour_to_cross)
{
    // list of cities that are populated from parent tours
    tour mixed_tour;

    // array of random indices to populate the mixed_tour
    int * random_numbers = new int[NUMBER_OF_PARENTS + 1];

    // counts the current index in random_numbers
    int count = 0;

    // upper bound of the random numbers, its the number of cities in the tours
    int numb_of_cities = list_of_tour_to_cross.front().get_numb_of_cities();

    // first index is always 0
    random_numbers[0] = 0;
    // random numbers to fill random indices used to populate tours
    for (int i = 1; i < NUMBER_OF_PARENTS; ++i)
    {
        random_numbers[i] = random_int(0, numb_of_cities - 1);
//        std::cout << "random number [" << i << "]: " << random_numbers[i] << std::endl;
    }
    // last index is always the max index
    random_numbers[NUMBER_OF_PARENTS] = numb_of_cities - 1;
//
//    std::cout << "1" << std::endl;
//    for (int i = 0; i < NUMBER_OF_PARENTS + 1; ++i)
//    {
//        std::cout << random_numbers[i];
//    }
//    std::cout << std::endl;

    // sort numbers so the indices are in ascending order
    bubble_sort<int>(random_numbers, NUMBER_OF_PARENTS);
//    std::cout << "sort" << std::endl;
//    for (int i = 0; i < NUMBER_OF_PARENTS + 1; ++i)
//    {
//        std::cout << random_numbers[i];
//    }
//    std::cout << std::endl;
//
//    std::cout << "test :(" << (count ? random_numbers[count] + 1 : random_numbers[count]);

    // iterates through every tour in the parent tours
    for (tour & x : list_of_tour_to_cross)
    {
//        std::cout << count << std::endl;
//        std::cout << "curr tour\n " << x << std::endl;

        // vector containing all cities in the current parent tour
        std::vector<city> temp = x.get_cities_in_vector();

        // if count is 0 then i = 0 else it will equal the random index + 1
        // because the previous tour added all cities up to and including this index
        // so now you want to start from that index + 1
        // breaks out of for loop when i adds all cities up to and including the random index
        // or i > cities in a tour, which means u have added all 32 cities to the new tour
        for (int i = count ? random_numbers[count] + 1 : random_numbers[count];
             i != random_numbers[count + 1] + 1 && i < numb_of_cities; ++i)
        {
//            std::cout << "i " << i << std::endl;
            int index_of_next_city = i;
//            std::cout << index_of_next_city << std::endl;
            // finds the next index of city that is not in tour
            while (mixed_tour.contains_city(temp[index_of_next_city]))
            {
                if (++index_of_next_city == static_cast<int>(temp.size()))
                {
                    index_of_next_city = 0;
                }
            }
//            std::cout << "Added city: " << temp[index_of_next_city] << std::endl;
            mixed_tour.add_city(temp[index_of_next_city]);
        }
        ++count;
    }
//
//    std::cout << "MIXED TOUR" << std::endl;
//    mixed_tour.determine_fitness();
//    std::cout << mixed_tour;

    delete[] random_numbers;

    return mixed_tour;
}

void
population::run_crossover()
{
    std::cout << "Before crossover" << std::endl;
    for (tour & x : list_of_tours)
    {
        std::cout << x.get_distance_travelled() << "\n";
    }
//    std::cout << list_of_tours.front();
    for (int i = 0; i < ITERATION; ++i)
    {
        crossover();
    }
    std::cout << "After crossover" << "\n\n\n\n\n\n\n" << std::endl;
    for (tour & x : list_of_tours)
    {
        std::cout << x.get_distance_travelled() << "\n";
    }
//    std::cout << list_of_tours.front();

}

int
population::random_int(const int & x, const int & y) const
{
    // return random int
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(x,y);
    return uni(rng);
}

void
population::shuffle_population()
{
    std::vector<tour> temp(list_of_tours.begin(), list_of_tours.end());
    std::random_shuffle(temp.begin(), temp.end());
    std::copy(temp.begin(), temp.end(), list_of_tours.begin());
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

bool
population::contains_tour(const std::list<tour> & list_tour, const tour & other) const
{
    for (const tour & x : list_tour)
    {
        if (x == other)
        {
            return true;
        }
    }
    return false;
}

void population::mutation()
{
    int count = 0;

    for (tour & x : list_of_tours)
    {
        if (count < NUMBER_OF_ELITES)
        {
            ++count;
        }
        else
        {
            x.swap_cities();
        }
    }
}

