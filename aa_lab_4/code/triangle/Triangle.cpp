#include "Triangle.h"

std::ostream& operator<<(std::ostream &os, const Triangle &tr) {
    return os << "(" << *(tr[0]) << "_" << *(tr[1]) << "_" << *(tr[2]) << ")";
}

void Triangle::print_debug_info() {
    std::cout << *this << std::endl;
    for (size_t i = 0; i < 3; ++i) {
        std::cout << "use_count " << *points[i] << " = " << points[i].use_count() << std::endl;
    }
}

Triangle::Triangle(Point3 &&p1, Point3 &&p2, Point3 &&p3) {
    if (p1 == p2 || p2 == p3 || p1 == p3) {
        time_t curTime = time(NULL);
        throw SamePointsTriangleException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    if (p3.isBelongsToLine(p1, p2)) {
        time_t curTime = time(NULL);
        throw DegenerateTriangleException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    points[0] = std::make_shared<Point3>(p1);
    points[1] = std::make_shared<Point3>(p2);
    points[2] = std::make_shared<Point3>(p3);
}

Triangle::Triangle(psPoint3 &p1, psPoint3 &p2, psPoint3 &p3) {
    if (*p1 == *p2 || *p2 == *p3 || *p1 == *p3) {
        time_t curTime = time(NULL);
        throw SamePointsTriangleException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    if (p3->isBelongsToLine(*p1, *p2)) {
        time_t curTime = time(NULL);
        throw DegenerateTriangleException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

Triangle::Triangle(Triangle &&tr) noexcept {
    for (size_t i = 0; i < 3; ++i) {
        points[i] = tr[i];
    }
}

Triangle::Triangle(const Triangle &tr) {
    for (size_t i = 0; i < 3; ++i) {
        points[i] = tr[i];
    }
}

psPoint3 Triangle::operator[](size_t ind) const {
    if (ind >= 3) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return points[ind];
}

// Point3 &Triangle::operator[](size_t ind) {
//     if (ind >= 3) {
//         time_t curTime = time(NULL);
//         throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
//     }
//     return points[ind];
// }

Triangle& Triangle::operator=(const Triangle &tr) noexcept {
    for (size_t i = 0; i < 3; ++i)
        points[i] = tr[i];
    return *this;
}

Triangle& Triangle::operator=(Triangle &&tr) noexcept {
    for (size_t i = 0; i < 3; ++i)
        points[i] = tr[i];
    return *this;
}

bool Triangle::operator==(const Triangle &tr) const noexcept {
    bool point_same;
    for (size_t i = 0; i < 3; ++i) {
        point_same = false;
        for (size_t j = 0; !point_same && j < 3; ++j) {
            if (*(points[i]) == *(tr[j]))
                point_same = true;
        }
        if (!point_same)
            return false;
    }
    return true;
}

bool Triangle::operator!=(const Triangle &tr) const noexcept {
    return !(*this == tr);
}

/* R(t) = orig + t * Dir, 
T(u, v) = (1 - u - v)V0 + uV1 + vV2 // точка на треугольнике, u, v - барицентрические координаты
*/
bool Triangle::intersection(const Ray &ray, double &t) const noexcept {
    const Point3 v0 = *points[0], v1 = *points[1], v2 = *points[2];
    
    // находим векторы V0V1 и V0V2
    Vector3 e1 = v1 - v0, e2 = v2 - v0;
    Vector3 de2 = (ray.getDirection()).vectorProduct(e2);   // (D x e2), D - ray.direction

    double det = de2.scalarProduct(e1); // (D x e2) * e1
    if (fabs(det) < EPS) {   // если определитель -> 0, то луч лежит в плоскости треугольника
        // std::cout << "\nfabs(det) < EPS\n";
        return false;
    }
    double invDet = 1 / det;

    Vector3 T = ray.getOrigin() - v0;   // расстояние от v0 до начала луча
    double u = de2.scalarProduct(T) * invDet;   // барицентрическая координата
    // Чтобы точка лежала внутри треугольника, обе ее барицентрические координаты должны лежать в пределах [0, 1]
    if (u < 0 || u > 1) {
        // std::cout << "\nu < 0 || u > 1: u = " << u << "\n";
        return false; 
    }  

    Vector3 te1 = T.vectorProduct(e1); // (T x e1)
    double v = te1.scalarProduct(ray.getDirection()) * invDet;  // барицентрическая координата
    if (v < 0 || u + v > 1) {
        // std::cout << "\nv < 0 || u + v > 1\n";
        return false; 
    }  

    t = te1.scalarProduct(e2) * invDet;

    return t > 0;
}

/* Возвращает нормаль так что скалярное произведение norm * ray < 0 */
Vector3 Triangle::getNormal(const Ray &ray) const noexcept {
    Vector3 e1 = *(points[1]) - *(points[0]);
    Vector3 e2 = *(points[2]) - *(points[0]);
    Vector3 normal = e1.vectorProduct(e2);
    normal.normalize();

    if (normal.scalarProduct(ray.getDirection()) > 0) {
        normal = normal * (-1);
    }

    return normal;
}