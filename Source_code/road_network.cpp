#include "road_network.h"


/**
 * @brief Road_Network::Road_Network: Add the starting node to the set nodes.
 * @param start
 * @param distance_to_close_node
 */
Road_Network::Road_Network(Node start, int distance_to_close_node):distance_to_close_node(distance_to_close_node){
    nodes.push_back(start);
}

/**
 * @brief Road_Network::mark_road_network
 * @param map
 */
void Road_Network::mark_road_network(Tile map[MAP_SIZE][MAP_SIZE]){

    for (unsigned int i = 0; i < edges.size(); ++i) {
        Edge e = edges[i];
        mark_road(map,e.start,e.end,e.size);
    }

}

/**
 * @brief Road_Network::is_there_close_node: Checks if a node is near the one given in argument
 * if one is found in the network, return this node. Else return the node given in argument
 * @param pos
 * @param dist_max
 * @param road_size
 * @return
 */
Node Road_Network::is_there_close_node(Node pos, int dist_max,int road_size){
    int index = -1;
    int min_length = dist_max;

    //Find the closest Node to pos
    //Go through all the node in the network
    for (unsigned int i = 0; i < nodes.size(); ++i) {
        //If the distance between the pos and the node at index i is less than the
        //minimal distance
        if(distance(pos.p, nodes[i].p) < min_length){
            //Store the index of the current node.
            index = i;
            //Modify the minimal distance in case we find a closer one.
            min_length = distance(pos.p, nodes[i].p);
        }
    }

    //If a node has been found
    if(index != -1){
        //Change the node road size if the pos node has a higher one.
        if(road_size > nodes[index].road_size){
            nodes[index].road_size = road_size;
        }

        //Return the node found
        return nodes[index];
    }

    //Else, return the pos initial
    return pos;
}

/**
 * @brief Road_Network::find_closest_node
 * @param pos
 * @param road_size
 * @return
 */
glm::ivec2 Road_Network::find_closest_node(glm::ivec2 pos, int road_size,Tile map[MAP_SIZE][MAP_SIZE]){
    //Set the min distance to the largest value that can separate 2 nodes.
    double min_dist = MAP_SIZE;
    ivec2 result;

    //Look over all the node of the network
    for (unsigned int i = 0; i < nodes.size(); ++i) {
        if(distance_and_height(pos, nodes[i].p,map) < min_dist && nodes[i].road_size >= road_size){
            min_dist = distance_and_height(pos, nodes[i].p,map);
            result = nodes[i].p;
        }
    }

    return result;
}

/**
 * @brief Road_Network::add_edge_to_network
 * @param start
 * @param end
 * @param size
 * @return
 */
glm::ivec2 Road_Network::add_edge_to_network(glm::ivec2 start, glm::ivec2 end, int size){
    //Initialization of the edge.
    Edge e;
    e.start = start;
    e.size = size;

    //Initialization of the end node of the edge previously initialized.
    Node en;
    en.p = end;
    en.road_size = size;

    //Find a node already existing to replace the ending node of the edge.
    //The node needs to be at a distance less or equal to the size of the road plus a constant
    Node corrected_end = is_there_close_node(en, distance_to_close_node+size,size);

    //If there is no existing node close enough to the end of the edge
    if(end == corrected_end.p){
        //Set the end of the edge to the one initialy specified
        e.end = end;

        //Create a new node representing the end of the edge
        Node n;
        n.p = end;
        n.road_size = size;

        //Add the new node since no one exists
        nodes.push_back(n);

    }else{
        //Change the end node of the edge if a close node has been found.
        e.end = corrected_end.p;
    }

    //Put the edge to the network
    edges.push_back(e);
    //Return the node corresponding to the end of the edge.
    return corrected_end.p;
}
