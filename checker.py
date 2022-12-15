from itertools import permutations
from collections import defaultdict
from math import exp

def count_collisions(permutation):
    result = 0
    for i, e1 in enumerate(permutation):
        for j, e2 in enumerate(permutation):
            if i != j and abs(i - j) == abs(e1 - e2):
                result += 1
    return result // 2 # We counted each collision twice

def find_collisions_distribution(n):
    distribution = defaultdict(lambda: 0)

    for permutation in permutations(range(n)):
        collisions = count_collisions(permutation)
        distribution[collisions] += 1
    return dict(distribution)

def calculate_real_z_beta(n, beta):
    coll_dist = find_collisions_distribution(n)

    z_beta = 0
    for collision_number in coll_dist:
        z_beta += coll_dist[collision_number] * exp(-beta * collision_number)
    return z_beta
    