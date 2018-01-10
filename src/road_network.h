    #ifndef ROAD_NETWORK_H
#define ROAD_NETWORK_H

#include <vector>
#include "rng_utility.h"
#include "glm/glm.hpp"
#include <iostream>

using glm::ivec2;
using namespace std;

/**
 * @brief The Edge struct represent an edge of the rode network.
 */
struct Edge {
    ivec2 start;
    ivec2 end;
    int size;
};

/**
 * @brief The Node struct represent a struct the road_size parameter corespond to the size of the largest edge passing by this node.
 */
struct Node {
    ivec2 p;
    int road_size;
};

class Road_Network
{
public:

    Road_Network(Node start, int distance_to_close_node);

    vector<Node> nodes;
    vector<Edge> edges;
    int distance_to_close_node = 10;

    void mark_road_network(Tile map[MAP_SIZE][MAP_SIZE]);
    Node is_there_close_node(Node pos, int dist_max, int road_size);
    ivec2 find_closest_node(ivec2 pos, int road_size, Tile map[MAP_SIZE][MAP_SIZE]);
    ivec2 add_edge_to_network(ivec2 start,ivec2 end,int size);
};

#endif // ROAD_NETWORK_H
