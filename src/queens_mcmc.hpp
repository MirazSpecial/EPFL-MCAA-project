#pragma once

#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

#include "permutations.hpp"
#include "utils.hpp"

bool step(Permutation& permutation, double beta);


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

/*
 * Performes sampling from given distribution using Metropolis algorithm.
 * Does up to 'max_iterations' steps in Markov chain, and returns chain after those steps.
 * 
 * The default beta value is a result of observation, that greedy algorithms for finding
 * solution of n-queens problem with loss function defined in our way, is actually correct.
 * So we can set beta to infinity and the solution is still always found.
 */
Permutation sample_from_pi_b(uint32_t n, 
                             double beta = (1<<10), 
                             uint32_t max_iterations = UINT32_MAX,
                             bool return_minimum = true) {
    Permutation permutation(n);

    for (uint32_t iteration = 0; iteration < max_iterations; ++iteration) {
        if (return_minimum && permutation.get_collision_number() == 0) {
            return permutation;
        }
        step(permutation, beta);
    }

    return permutation;
}

/*
 * Function samples m times (samples by performing Metropolis algorithm, with 
 * 'max_iterations' iterations) from underlying distribution, and using those 
 * samples estimates the ration between 'z_beta_big' and 'z_beta_small' 
 */
double estimate_z_beta_ratio(uint32_t n,
                             double beta_big,
                             double beta_small,
                             uint32_t m,
                             uint32_t max_iterations) {

    double result = 0;
    for (uint32_t i = 0; i < m; ++i) {
        Permutation sample = sample_from_pi_b(n, beta_small, max_iterations, false);
        double value = exp(-(beta_big - beta_small) * sample.get_collision_number());
        result += value / m;
    }
    return result;
}

/*
 * Function to estimate number of proper permutations (queen placements).
 */
double estimate_z_beta_infinity(uint32_t n,
                                const std::vector<double>& betas,
                                uint32_t m,
                                uint32_t max_iterations,
                                bool verbose = false) {
    
    double big_z_beta_ratio = 1;
    for (size_t i = 0; i < betas.size() - 1; ++i) {
        double ratio = estimate_z_beta_ratio(n, betas[i + 1], betas[i], m, max_iterations);
        big_z_beta_ratio *= ratio;
        
        if (verbose) {
            std::cout << "Ratio between beta " << betas[i + 1] << " and beta " << betas[i] << " is: " 
                      << ratio << std::endl;
        }
    }

    double z_beta0 = factorial(n);
    return big_z_beta_ratio * z_beta0;
}
