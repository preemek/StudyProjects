//
// Created by Filip Olszowski on 02.01.2020.
//

#include "helpers.hpp"

int probability_generator()
{
    std::mt19937 mt_rand(time(0));;

    int random_number = mt_rand()%101;

    return random_number;
};