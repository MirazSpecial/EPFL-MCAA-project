#include <iostream>
#include <time.h>
#include <cmath>
#include <random>

#include "permutations.hpp"
#include "utils.hpp"
#include "queens_mcmc.hpp"

void print(std::vector<double> const &a) {
   std::cout << "The vector elements are : ";

   for(int i=0; i < a.size(); i++) {
      std::cout << a.at(i) << ' ';
   }
   std::cout << "\n" << std::endl;
}

int main() {
   // Turned off for debugging 
   // srand(time(0));

   double n = 19;
   double init_beta = pow(4000, -1);
   double r = pow(0.99, -1);
   std::vector<double> betas = fill_with_geometric(10, 0.01, 0.8);
   print(betas);
   int m = 800;
   int max_iter = 1000;
   double z_beta_infinity = 0;
   for (size_t i = 0; i < 5; ++i) {
      std::cout << "." << std::endl;
      z_beta_infinity += estimate_z_beta_infinity(n, betas, m, max_iter, false);
   }
   z_beta_infinity /= 5;
   std::cout << "For n equal to " << n << " we number of proper queen placements is around " << z_beta_infinity << std::endl;
   //Permutation permutation = sample_from_pi_b(n, init_beta, UINT32_MAX, true);
   //permutation.print_permutation();
}
