#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <vector>
#include "l_element.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <glm/glm.hpp>
#include "rng_utility.h"
#include "road_network.h"

using namespace std;
using glm::ivec2;

/**
 * @brief The Proposition struct contain all the information about a proposition left hand side,
 * right hand side and a probability representing it's likeliness to be choosen.
 */
struct Proposition {
    L_Element left_side;
    vector<L_Element> right_side;
    double p;

    void print() {
        cout << left_side << " -> ";
        for (unsigned int i = 0; i < right_side.size(); ++i) {
            cout << right_side[i];
        }

        cout << endl;
    }
};

/**
 * @brief The L_system class contains all the information needed to generate a chain and then transform it to a road network.
 */
class L_system
{
public:
    L_system(ivec2 start_pos,double base_angle, int min_length, int max_length, int nb_iteration,int base_road_size);

    ivec2 start_pos;
    double angle;
    int min_length;
    int max_length;
    int nb_iteration;
    double delta_angle = 90;
    int base_road_size = 4;

    vector<Proposition> props;

    void generate_network(Tile map[MAP_SIZE][MAP_SIZE], Road_Network &network);

private:

    vector<L_Element> generate_chain();
    void mark_chain_as_road(vector<L_Element> chain,ivec2 start_position,double angle,Tile map[MAP_SIZE][MAP_SIZE],int road_size,Road_Network &network);
    Proposition get_props_from_rhs(L_Element rhs);
    vector<L_Element> get_sub_chain(vector<L_Element> &chain,int start);

};

#endif // L_SYSTEM_H
