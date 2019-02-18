cmake_minimum_required(VERSION 3.5)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

set(SOURCE_FILES main.cpp)

add_executable(GeneticAlgorithm main.cpp city.cpp city.hpp tour.cpp tour.hpp population.cpp population.hpp templates.hpp)

INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.4.0/include )
LINK_DIRECTORIES(  /usr/local/Cellar/allegro/5.2.4.0/lib )

file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.4.0/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

TARGET_LINK_LIBRARIES(GeneticAlgorithm  ${LIBRARIES})