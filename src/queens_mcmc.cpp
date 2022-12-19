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

   double n = 1000;
   double init_beta = pow(4000, -1);
   //double r = pow(0.99, -1);
   //std::vector<double> betas = fill_with_geometric(3*n, 1e-10, 7091.48951306079*exp(-0.58893998427322*n));
   //std::vector<double> betas = fill_with_geometric(10, 0.0001, 0.01);
   //print(betas);
   //int m = 500;
   //int max_iter = 10000;
   //double z_beta_infinity = estimate_z_beta_infinity(n, betas, m, max_iter, false);
   //std::cout << "For n equal to " << n << " we number of proper queen placements is around " << z_beta_infinity << std::endl;
   Permutation permutation = sample_from_pi_b(n, init_beta, UINT32_MAX, true);
   permutation.print_permutation();

   /**
    * 4  2
      5 	10
      6 	4
      7 	0
      8 	92
      9 	352
      10 724
      11 2,680
      12 14,200
      13 73,712
      14 365,596
      15 2,279,184
      16 14,772,512
      17 95,815,104
      18 666,090,624
      19 4,968,057,848
      20 39,029,188,884
      21 314,666,222,712
      22 2,691,008,701,644
      23 24,233,937,684,440
      24 227,514,171,973,736
      25 2,207,893,435,808,352
      26 22,317,699,616,364,044
      27 234,907,967,154,122,528 
   */
}
