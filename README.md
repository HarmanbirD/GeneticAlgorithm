# Genetic Algorithm
 
 An Object Oriented implementation of a Genetic algorithm to solve the travelling salesman problem. 
 Includes a GUI that visualizes the best route everytime a new one is found,
 
 ## Getting Started
 
 You will be prompted to enter values for the following:
 
 ```
 Enter the number of cities you would like to visit: (recommend 32)
 ```
 This is the number of cities that the "salesman" needs to visit, higher number will take more time but produce
more interesting plots.

 ```
 Enter the number of candidate tours in the population: (recommend 32)
 ```
 This is the number of different routes the salesman can take per generation.  I'm not sure the optimal value for this
relative to the number of cities, but it seems to work well if this equals number of cities.

 ```
 Enter the mutation rate(If you want a 15% mutation rate, enter 15): (recommend 5)
 ```
 Every generation, every city in every route (except the elite) has a % chance of being randomly swapped with another
random city's spot in that route.  Lower mutation rate is favourable at lower iterations, but at higher iterations,
mutation rate needs to be high enough for the algorithm to be able to try completely new routes.  It's safe to keep
this around 5-15.

 ```
 Enter number of parents: (recommend 8)
 ```
 The number of parent routes that are randomly selected, from which the offsprings parents will be chosen.  

 ```
 Enter number of elites: (recommend 1)
 ```
 This is the number of best routes that are saved from mutation every generation.  
 
 ```
 Enter the number of iterations: (recommend 1000)
 ```
This is the number of generations that will be simulated.  There seems to be a logarithmic relationship of increasing
improvement and increasing iterations.  Of course, the more iterations, the better the output will be.
