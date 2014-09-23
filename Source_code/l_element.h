#ifndef L_ELEMENT_H
#define L_ELEMENT_H

#include <glm/glm.hpp>
#include <iostream>

using namespace std;
using glm::ivec2;

/**
 * @brief The L_Element class represent all the possible element composing a proposition of The L-system
 *
 */
class L_Element
{
public:
    enum Enum{
        S,
        P,
        M,
        O,
        C,
        s
    };

    Enum element;

    //Constructor
    L_Element(Enum element);
    L_Element();

    friend ostream& operator<<(ostream &os, const L_Element &elem);

    bool operator== (const L_Element& cc) const;

    ivec2 action(double &angle,double delta_angle, int length,ivec2 previous_point);

};

#endif // L_ELEMENT_H
