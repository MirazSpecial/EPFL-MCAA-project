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