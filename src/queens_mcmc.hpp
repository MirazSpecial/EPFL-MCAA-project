#pragma once

#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

#include "permutations.hpp"
#include "utils.hpp"

bool step(Permutation& permutation, double beta);
Permutation find_solution(uint32_t n);



/*
 * Performs a step in Markov Chain Monte Carlo Metropolis-Hastings algorithm
 * and returns true if we moved to a different state, or false if we stayed in this one
 */
bool step(Permutation& permutation, double beta) {
    uint32_t n = permutation.get_n();

    auto indexes = get_random_pair(n);

    uint32_t collision_before = permutation.get_collision_number();
    uint32_t collision_after = permutation.get_collision_number_after_swap(
        indexes.first, indexes.second);

    double aij = (collision_after < collision_before) ? 1 : exp(beta * ((double)collision_before - collision_after));
    
    if (aij >= get_random_double()) {
        /* Accept this swap */
        permutation.swap(indexes.first, indexes.second);
        return true;
    }
    else {
        /* Drop the swap */
        return false;
    }
}

Permutation find_solution(uint32_t n) {
    Permutation permutation(n);
    uint32_t iteration = 0;
    const uint32_t reporting_step = 10000;

    /* Experimentally we found out, that a greedy solution works for
       our loss function, so we can start with beta infinity */
    double beta = 1 << 10; /* Experimentally we found out*/

    while (true) {
        if (permutation.get_collision_number() == 0) {
            std::cout << "Proper permutation found in " << iteration << " iterations." << std::endl;
            return permutation;
        }
        if (iteration % reporting_step == 0) {
            std::cout << "Iteration: " << iteration << " collisions: "
                      << permutation.get_collision_number() << std::endl;
        }

        step(permutation, beta);
        iteration++;
    }

}