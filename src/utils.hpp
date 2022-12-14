#pragma once

#include <cassert>
#include <random>

/*
 * Returns pair of two different integer values from 0 to n-1 
 */
std::pair<size_t, size_t> get_random_pair(size_t n) {
    assert(n > 1);

    size_t ind1 = rand() % n, ind2 = rand() % n;
    while(ind1 == ind2) {
        ind2 = rand() % n;
    }
    return std::make_pair(ind1, ind2);
}

double get_random_double() {
    return (double)rand() / (double)RAND_MAX;
}

uint32_t factorial(uint32_t n) {
    uint32_t result = 1;
    while(--n) {
        result *= (n + 1);
    }
    return result;
}

/*
 * Return a vector with num+1 elements, where:
 * vector[0] == 0
 * vector[1] == min_el
 * vector.bacK() == max_el
 * for i > 1, i < vector.size()
 *   vector[i] / vector[i - 1] = const
 * So elements (apart from 0) form geometric sequence 
 */
std::vector<double> fill_with_geometric(uint32_t num, double min_el, double max_el) {
    double r = pow(max_el / min_el, (double)1 / (double)(num - 1));

    std::vector<double> result = {0};
    for (uint32_t i = 0; i < num; ++i) {
        result.push_back(min_el);
        min_el *= r;
    }
    return result;
}

/*
 * Calculates beta max (for second task)
 * depending on n. This is estimated to be the optimal
 * beta max during preprocessing
 */
double calculate_max_beta(uint32_t n) {
    uint32_t n_thresholds[] = {13, 15, 17, 19};
    double betas[] = {5, 1.6, 0.8, 0.5, 0.1};
    for (uint32_t i = 0; i < 4; ++i) {
        if (n < n_thresholds[i]) 
            return betas[i];
    }
    return betas[4];
}