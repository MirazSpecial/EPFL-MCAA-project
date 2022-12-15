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

    size_t n = 100;

    Permutation permutation = find_solution(n);
    permutation.print_permutation();
}