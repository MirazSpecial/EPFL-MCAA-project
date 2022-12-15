#pragma once

#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdlib>

class Permutation {
    size_t n;
    uint32_t collision_number;
    std::vector<uint32_t> data;

public:

    Permutation(size_t n): n(n), collision_number(n * (n - 1) / 2) {
        for (uint32_t i = 0; i <= n; ++i) {
            data.push_back(i);
        }
    }

    const void print_permutation() {
        std::cout << "[";
        for (size_t i = 0; i < n; ++i) {
            std::cout << data[i];
            if (i < n - 1)
                std::cout << " ";
        }
        std::cout << "]" << std::endl;
    }

    const uint32_t get_collision_number() {
        return collision_number;
    }

    const size_t get_n() {
        return n;
    }

    /*
     * Checks and returns what would be the number of collisions after
     * swaping values with given indexes. Doesn't really perform the swap.
     * 
     * Complexity: O(n) - because of using 'collisions_if_set_field'
     *
     */
    uint32_t get_collision_number_after_swap(size_t ind1, size_t ind2) const {
        uint32_t old_collisions = collisions_if_set_field(ind1, data[ind1]) + 
                                  collisions_if_set_field(ind2, data[ind2]);
        uint32_t new_collisions = collisions_if_set_field(ind1, data[ind2]) +
                                  collisions_if_set_field(ind2, data[ind1]);
        if (abs(ind1 - ind2) == abs(data[ind1] - data[ind2]))
            new_collisions += 2;

        return collision_number - old_collisions + new_collisions;
    }

    /*
     * Swap values in permutation and update number of collisions
     * 
     * complexity: O(n) - because of using 'get_collision_number_after_swap'
     */
    void swap(size_t ind1, size_t ind2) {
        uint32_t new_collision_number = get_collision_number_after_swap(ind1, ind2);
        std::swap(data[ind1], data[ind2]);
        collision_number = new_collision_number;
    }

    /*
     * Recalculate current numberof collisions. 
     *
     * Complexity: O(n^2)
     */
    uint32_t recalculate_collisions() const {
        uint32_t collisions = 0;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                if (abs(i - j) == abs(data[i] - data[j]))
                    collisions++;
            }
        }
        return collisions;
    }

private:

    /*
     * Return number of collisions of index 'ind' if its value was 'value'
     *
     * Complexity: O(n)
     */
    uint32_t collisions_if_set_field(size_t ind, uint32_t value) const {
        uint32_t collisions = 0;
        for (size_t i = 0; i < n; ++i) {
            if (i != ind && abs(ind - i) == abs(value - data[i]))
                collisions++;
        }
        return collisions; 
    }

};
