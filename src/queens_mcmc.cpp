#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

#include "permutations.hpp"
#include "utils.hpp"
#include "queens_mcmc.hpp"


int main() {
    // Turned off for debugging 
    // srand(time(0));

    size_t n = 20;
    std::vector<double> betas = fill_with_geometric(10, 0.002, 0.1);
    int m = 400;
    int max_iter = 1000;

    double z_beta_infinity = estimate_z_beta_infinity(n, betas, m, max_iter, true);
    std::cout << "For n equal to " << n << " we number of proper queen placements is around " << z_beta_infinity << std::endl;
}
