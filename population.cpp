//
// Created by Harmanbir Dhillon on 2018-11-17.
//

#include "population.hpp"
#include "templates.hpp"

const int population::NUMBER_OF_PARENTS = templates::get_const<int>(std::cin, "Enter number of parents: ");
const int population::NUMBER_OF_ELITES  = templates::get_const<int>(std::cin, "Enter number of elites: ");
const int population::ITERATION         = templates::get_const<int>(std::cin, "Enter the number of iterations: ");

struct tour_comparator
{
    bool operator() (const tour & one, const tour & two)
    {
        return !(one < two);
    }
};

// default constructor
population::population() = default;

// constructor that takes a list of tours
population::population(std::list<tour> list_of_tours)
: list_of_tours{std::move(list_of_tours)}
{
    ALLEGRO_DISPLAY * display = NULL;

    if (!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro\n");
    }

    display = al_create_display(500, 500);

    if(!display) {
        fprintf(stderr, "failed to create display!\n");
    }

    sort_tours();
    base_distance = this->list_of_tours.front().get_distance_travelled();
    run_crossover();
}

// selects NUMBER_OF_PARENT tours
std::list<tour>
population::select_parents()
{
    // list of parent tours
    std::list<tour> list_of_tours_to_cross;

    // runs NUMBER_OF_PARENTS times
    for (int i = 0; i < NUMBER_OF_PARENTS; ++i)
    {
        // array that contains the random indices used to populate the parent pool
        std::array<int, PARENT_POOL_SIZE> random_indices {};
        for (int j = 0; j < PARENT_POOL_SIZE; ++j)
        {
            random_indices[j] = city::random_int(0, static_cast<int>(list_of_tours.size() - 1));
        }

        // sort the random indices
        std::sort(random_indices.begin(), random_indices.end());

        auto tour_iterator = list_of_tours.begin();

        // list containing the tours in the parent pool
        std::list<tour> parent_pool_tours;

        int count = 0;

        // runs for every index in the random_indices
        for (const int & j : random_indices)
        {
            // while count != the index from the random_indices,
            // count is increased until it == to the index from random_indices
            // that tour is then added to the parent pool
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
        // parent pool is sorted so the fittest tour is moved to the front of the list
        parent_pool_tours.sort(tour_comparator());

        // if the tour is already in the parent tours, another parent tour is chosen
        // decrementing i means that the for loop that runs NUMBER_OF_PARENT times
        // runs again to select another parent
        if (contains_tour(list_of_tours_to_cross, parent_pool_tours.front()))
        {
            --i;
        }
        else
        {
            list_of_tours_to_cross.push_back(parent_pool_tours.front());
        }
    }

    return list_of_tours_to_cross;
}

// sorts the list_of_tours list
void
population::sort_tours()
{
    list_of_tours.sort(tour_comparator());
}

// determines the fitness of all tours
void
population::evaluation()
{
    for (tour & x : list_of_tours)
    {
        x.determine_fitness();
    }
}

// replaces non-elite tours
void
population::crossover()
{
    // temp list of tours created by crossing over parent tours
    // also contains the ELITE tours
    std::list<tour> crosses;

    // adds ELITE tours to temp list of tours
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
    mutation();
    evaluation();
    sort_tours();
}

// crosses NUMBER_OF_PARENT tours
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
        random_numbers[i] = city::random_int(0, numb_of_cities - 1);
    }
    // last index is always the max index
    random_numbers[NUMBER_OF_PARENTS] = numb_of_cities - 1;

    // sort numbers so the indices are in ascending order
    templates::bubble_sort<int>(random_numbers, NUMBER_OF_PARENTS);

    // iterates through every tour in the parent tours
    for (tour & x : list_of_tour_to_cross)
    {
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
            int index_of_next_city = i;

            // finds the next index of city that is not in tour
            while (mixed_tour.contains_city(temp[index_of_next_city]))
            {
                if (++index_of_next_city == static_cast<int>(temp.size()))
                {
                    index_of_next_city = 0;
                }
            }
            mixed_tour.add_city(temp[index_of_next_city]);
        }
        ++count;
    }

    delete[] random_numbers;

    return mixed_tour;
}

// runs crossover ITERATION times
void
population::run_crossover()
{
    auto t_start = std::chrono::high_resolution_clock::now();
//    std::cout << "\nBest tour before crossover: \n" << std::endl;
//    std::cout << list_of_tours.front();

    int count = 0;
    double current_best_tour_distance = list_of_tours.front().get_distance_travelled();

//    while (list_of_tours.front().get_distance_travelled() / base_distance > IMPROVEMENT_FACTOR)
    while (count < ITERATION)
    {
        crossover();
        std::cout << std::flush;
        std::cout << std::right << std::setw(20) << "\rCurrent best tour distance: " << list_of_tours.front().get_distance_travelled();
        std::cout << std::right << std::setw(35) << " Current Iteration: " << ++count;
        std::cout << std::right << std::setw(35) << " Current Improvement: ";
        std::cout << std::fixed << std::setprecision(2) << (100 - list_of_tours.front().get_distance_travelled() / base_distance * 100) << "%";
        if (current_best_tour_distance > list_of_tours.front().get_distance_travelled())
        {
            al_clear_to_color(al_map_rgb(250, 250, 250));
            get_coords(list_of_tours.front());
            al_flip_display();
        }
        current_best_tour_distance = list_of_tours.front().get_distance_travelled();
    }


    std::cout << "\n\n\nBest tour after crossover: \n";
    std::cout << list_of_tours.front();
    std::cout << "\n\nImproved by: " << std::fixed << std::setprecision(2);
    std::cout << (100 - list_of_tours.front().get_distance_travelled() / base_distance * 100);
    std::cout << "% after " << count << " iterations." << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "\nPARENT POOL SIZE: " << PARENT_POOL_SIZE << std::endl;
    std::cout << "Time: " << std::chrono::duration<double, std::milli>(t_end-t_start).count() / 1000 << " seconds" << std::endl;

    al_rest(50.0);
}

// adds a tour to the population
void
population::add_tour(const tour & t)
{
    list_of_tours.push_back(t);
}

// overloaded output operator
std::ostream &
operator<<(std::ostream &os, const population & p)
{
    for (const tour & x : p.list_of_tours)
    {
        std::cout << x;
    }
    return os;
}

// returns true if the list of tours contains the given tour
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

// mutates all tours
void
population::mutation()
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
            x.mutate_tour();
        }
    }
}

void
population::get_coords(tour to_draw)
{
    auto cities_vector = to_draw.get_cities_in_vector();
    for (auto i = 0; i != cities_vector.size()-1;)
    {
        int x1 = cities_vector[i].get_x();
        int y1 = cities_vector[i].get_y();
        int x2 = cities_vector[++i].get_x();
        int y2 = cities_vector[i].get_y();
        draw_map(x1,y1,x2,y2,al_map_rgb(0,0,0),2);
    }

    al_draw_circle(cities_vector.back().get_x()/2,cities_vector.back().get_y()/2,2,al_map_rgb(0,0,0), 3);
}

void
population::draw_map(const float & x1, const float & y1, const float & x2, const float & y2, const ALLEGRO_COLOR & color, const float &thickness)
{
    al_draw_line(x1/2,y1/2,x2/2,y2/2,color,thickness);
    al_draw_circle(x1/2,y1/2,2,color,3);
}
