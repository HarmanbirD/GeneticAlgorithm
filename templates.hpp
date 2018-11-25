//
// Created by Harmanbir Dhillon on 2018-11-24.
//

#pragma once

#include <iostream>

class templates {
public:
    template<typename T>
    static
    const T get_const(std::istream & in, const std::string & prompt)
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
    static
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
};
