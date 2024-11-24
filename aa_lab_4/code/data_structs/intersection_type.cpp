#include "intersection_type.h"


std::ostream& operator<<(std::ostream &os, const intersection_t &interset) {
    os << "Intersection: Point" << interset.point << " dist= " << interset.distance << ", n= " << interset.normal << std::endl;
    return os;
}
