#include "l_element.h"
#include <glm/glm.hpp>
#include "rng_utility.h"

using glm::ivec2;

L_Element::L_Element(Enum element):element(element){}

L_Element::L_Element()
{
    element = S;
}

ostream& operator<<(ostream &os, const L_Element &elem){
    switch (elem.element) {
    case L_Element::S:
        os << "S";
        break;
    case L_Element::O:
        os << "[";
        break;
    case L_Element::C:
        os << "]";
        break;
    case L_Element::P:
        os << "+";
        break;
    case L_Element::M:
        os << "-";
        break;
    case L_Element::s:
        os << "s";
        break;
    default:
        break;
    }

    return os;
}

bool L_Element::operator==(const L_Element &cc) const
{
    return cc.element == element;
}

ivec2 L_Element::action(double &angle,double delta_angle, int length, ivec2 previous_point){
    switch (element) {
    case S:
        return find_next_point(previous_point,angle,length);
        break;
    case s:
        return find_next_point(previous_point,angle,length);
        break;
    case P:
        angle += delta_angle;
        break;
    case M:
        angle -= delta_angle;
        break;
    default:
        break;
    }

    return previous_point;
}
