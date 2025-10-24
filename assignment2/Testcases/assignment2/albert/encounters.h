# pragma once

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


int encounters(int gridLength, int num_animals, int num_iterations, double p, unsigned int seed);