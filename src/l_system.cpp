#include "l_system.h"

L_system::L_system(ivec2 start_pos, double base_angle, int min_length, int max_length, int nb_iteration, int base_road_size):start_pos(start_pos),angle(base_angle),
    min_length(min_length),max_length(max_length),nb_iteration(nb_iteration),base_road_size(base_road_size)
{
    vector<L_Element> v;

    Proposition p1;
    p1.left_side = L_Element::S;
    v = {L_Element::S, L_Element::S};
    p1.right_side = v;
    p1.p = 0.25;
    props.push_back(p1);


    Proposition p2;
    p2.left_side = L_Element::S;
    v = {L_Element::S,L_Element::O,L_Element::P,L_Element::s,L_Element::C,L_Element::S};
    p2.right_side = v;
    p2.p = 0.25;
    props.push_back(p2);


    Proposition p3;
    p3.left_side = L_Element::S;
    v = {L_Element::S,L_Element::O,L_Element::M,L_Element::s,L_Element::C,L_Element::S};
    p3.right_side = v;
    p3.p = 0.25;
    props.push_back(p3);

    Proposition p32;
    p32.left_side = L_Element::S;
    v = {L_Element::S,L_Element::O,L_Element::P,L_Element::s,L_Element::C,L_Element::O,L_Element::M,L_Element::s,L_Element::C,L_Element::S};
    p32.right_side = v;
    p32.p = 0.25;
    props.push_back(p32);


    Proposition p4;
    p4.left_side = L_Element::O;
    v = {L_Element::O};
    p4.right_side = v;
    p4.p = 1;
    props.push_back(p4);


    Proposition p5;
    p5.left_side = L_Element::C;
    v = {L_Element::C};
    p5.right_side = v;
    p5.p = 1;
    props.push_back(p5);


    Proposition p6;
    p6.left_side = L_Element::P;
    v = {L_Element::P};
    p6.right_side = v;
    p6.p = 1;
    props.push_back(p6);


    Proposition p7;
    p7.left_side = L_Element::M;
    v = {L_Element::M};
    p7.right_side = v;
    p7.p = 1;
    props.push_back(p7);


    Proposition p8;
    p8.left_side = L_Element::s;
    v = {L_Element::s,L_Element::S};
    p8.right_side = v;
    p8.p = 1;
    props.push_back(p8);


    srand(time(NULL));

}

void L_system::generate_network(Tile map[MAP_SIZE][MAP_SIZE], Road_Network &network)
{
    vector<L_Element> chain = generate_chain();
    for (unsigned int i = 0; i < chain.size(); ++i) {
        cout << chain[i];
    }
    cout << endl;

    mark_chain_as_road(chain,start_pos,angle,map,base_road_size, network);
}

vector<L_Element> L_system::generate_chain()
{
    vector<L_Element> result;
    result.push_back(L_Element::S);

    vector<L_Element> temp_result;

    for (int i = 0; i < nb_iteration; ++i) {
        for (unsigned int j = 0; j < result.size(); ++j) {
            vector<L_Element> elements = get_props_from_rhs(result[j]).right_side;
            temp_result.insert(temp_result.end(),elements.begin(),elements.end());
        }

        result = temp_result;
        temp_result.clear();
    }

    return result;
}

void L_system::mark_chain_as_road(vector<L_Element> chain, glm::ivec2 start_position, double angle, Tile map[MAP_SIZE][MAP_SIZE], int road_size, Road_Network &network)
{
    ivec2 current_pos = start_position;
    double current_angle = angle;

    for (unsigned int i = 0; i < chain.size(); ++i) {
        switch (chain[i].element) {
        case L_Element::O:
            if(road_size > 0)
                mark_chain_as_road(get_sub_chain(chain,i),current_pos,current_angle,map,road_size-1,network);
            else
                mark_chain_as_road(get_sub_chain(chain,i),current_pos,current_angle,map,road_size,network);
            break;
        default:
            double length = rand() % (max_length-min_length) + min_length;
            ivec2 next_pos = chain[i].action(current_angle,delta_angle,length,current_pos);

            current_pos = network.add_edge_to_network(current_pos,next_pos,road_size);

            //Correcting the angle when a point is replaced by an existing point close by.
            ivec2 old_next_pos = L_Element().action(current_angle,delta_angle,100,next_pos);
            angle = find_angle(current_pos,old_next_pos);
            break;
        }
    }
}

/**
 * @brief L_system::get_props_from_rhs: Return the proposition according to its probability.
 * High probability proposition should be choosen more often.
 * The proposition must have a left side equal to rhs.
 * @param rhs
 * @return
 */
Proposition L_system::get_props_from_rhs(L_Element rhs)
{
    vector<Proposition> result;
    for (unsigned int i = 0; i < props.size(); ++i) {
        if(rhs == props[i].left_side){
            result.push_back(props[i]);
        }
    }

    double r = (rand() % 1000 + 1) / 1000.0;
    double t = 0;

    for (unsigned int i = 0; i < result.size(); ++i) {
        t += result[i].p;

        if(r <= t){
            return result[i];
        }
    }

    cout << "Error no Proposition found " << rhs << " r,t " << r << ", " << t << endl;
    return result[0];
}

vector<L_Element> L_system::get_sub_chain(vector<L_Element> &chain, int start)
{
    int nb_bracket = 0;
    int end = start;
    for (unsigned int i = start; i < chain.size(); ++i) {
        if(chain[i] == L_Element::O){
            nb_bracket += 1;
        }else if(chain[i] == L_Element::C){
            nb_bracket -=1;
            if(nb_bracket == 0){
                end = i;
                break;
            }
        }
    }

    vector<L_Element> result(chain.begin()+start,chain.begin()+end);
    chain.erase(chain.begin()+start,chain.begin()+end);

    return result;
}

