#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

#include "permutations.hpp"
#include "utils.hpp"

/*
 * Performs a step in Markov Chain Monte Carlo Metropolis-Hastings algorithm
 * and returns true if we moved to a different state, or false if we stayed in this one
 */
double step(Permutation& permutation, double beta) {
    uint32_t n = permutation.get_n();

    auto indexes = get_random_pair(n);

    uint32_t collision_before = permutation.get_collision_number();
    uint32_t collision_after = permutation.get_collision_number_after_swap(
        indexes.first, indexes.second);

    double aij = (collision_after < collision_before) ? 1 : exp(beta * ((double)collision_before - collision_after));
    
    // std::cout << "coll before " << collision_before << " coll after: " << collision_after 
    //           << " aij: " << aij << " beta: " << beta << std::endl;

    if (aij >= get_random_double()) {
        /* Accept this swap */
        permutation.swap(indexes.first, indexes.second);
        // return true;
        return aij;
    }
    else {
        /* Drop the swap */
        // return false;
        return 0.;
    }
}

int main() {
    // Turned off for debugging 
    // srand(time(0));

    size_t n = 5000;
    // double beta = 0.1;
    double beta = 1<<10;
    double beta_increment = 0;
    // double beta_increment = 0.1;
    uint32_t beta_step = 100;
    double aij;
    Permutation permutation = Permutation(n);

    for (uint32_t i = 1; i < 10000000; ++i) {
        if (i % 1000 == 0)
            std::cout << "Iteration: " << i 
                      << " collisions: " << permutation.get_collision_number() 
                      << " beta: " << beta 
                      << " aij: " << aij << std::endl;

        if (permutation.get_collision_number() == 0) {
            std::cout << "Iteration: " << i << " collisions: " << permutation.get_collision_number()
                  << " permutation: ";
            permutation.print_permutation();
            std::cout << std::endl;
            break;
        }
        aij = step(permutation, beta);

        if (i % beta_step == 0) {
            beta += beta_increment;
        }
    }

}