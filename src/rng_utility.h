#ifndef RNG_UTILITY_H
#define RNG_UTILITY_H

#include <vector>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "tile.h"
#include <tuple>
#include <algorithm>

using std::pair;
using namespace std;
using glm::ivec2;

const int MAP_SIZE = 700;

/**
 * @brief rng_utility contains several useful utility function, that can be use in various classes.
 */

void Interpolate( ivec2 a, ivec2 b, vector<ivec2>& result );
ivec2 find_next_point(ivec2 start,double angle, int length);
bool is_into_the_map(ivec2 p);
void mark_road(Tile map[MAP_SIZE][MAP_SIZE],ivec2 start,ivec2 end,int size);
void mark_base_square(Tile map[MAP_SIZE][MAP_SIZE], ivec2 start, ivec2 end,int size);
double find_angle(ivec2 start, ivec2 end);
double distance(ivec2 start,ivec2 end);
double distance_and_height(ivec2 start,ivec2 end,Tile map[MAP_SIZE][MAP_SIZE]);
void readPng(Tile map[MAP_SIZE][MAP_SIZE], const char* densityFile, const char* heightFile);
pair<ivec2, double> get_average_pop(Tile map[MAP_SIZE][MAP_SIZE], ivec2 left_top, int width, int height);
vector<pair<glm::ivec2, double> > get_subdivided_map(Tile map[MAP_SIZE][MAP_SIZE], int square_size);
bool comp_function(pair<glm::ivec2, double> a,pair<glm::ivec2, double> b);
void writeToPng(Tile map[MAP_SIZE][MAP_SIZE], const char* outputName);

#endif // RNG_UTILITY_H
