#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

#include "permutations.hpp"
#include "utils.hpp"
#include "queens_mcmc.hpp"

void example_1() {
    double beta = 0.01;
    double beta_increment = 0.01;
    uint32_t beta_step = 100;
    uint32_t n;

    n = 100;
    Permutation permutation_100 = sample_from_pi_b(
        n, beta, beta_increment, beta_step).first;

    n = 1000;
    Permutation permutation_1000 = sample_from_pi_b(
        n, beta, beta_increment, beta_step).first;
}

void example_2(uint32_t n) {
    /*
     * We found this beta to be optimal beta infinity
     */
    double max_beta = calculate_max_beta(n); 
    /*
     * We decided to go with this beta as the smallest non-zero value
     */
    double min_beta = 0.005;
    /*
     * As we sample from distribution changing beta is not really important
     */
    double beta_increment = 0;
    uint32_t beta_step = -1;
    /*
     * Number of betas
     */
    uint32_t T = 10;
    /*
     * Apart from first beta value (which is zero), all
     * other are taken from geometric sequence
     */
    std::vector<double> betas = fill_with_geometric(T, min_beta, max_beta);

    uint32_t m = 500;
    uint32_t max_iter = 1000;

    auto z_betas = estimate_z_betas(n, betas, m, max_iter);
    for (size_t i = 0; i < betas.size(); ++i) {
        std::cout << "Beta: " << betas[i] << " z_beta: " << z_betas[i] << std::endl; 
    }
    std::cout << "z_beta_infinty (final estimation): " << z_betas.back() << std::endl;

}


int main() {
    // Turned off for debugging 
    // srand(time(0));

    // example_1(); /* For N-queens problem solution */

    // example_2(12); /* For estimating number of solutions for n=12 */

}
