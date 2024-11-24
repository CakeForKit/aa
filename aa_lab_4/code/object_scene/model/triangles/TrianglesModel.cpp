#include "TrianglesModel.h"

std::ostream& TrianglesModel::print(std::ostream &os) const noexcept {
    os << "TrianglesModel: \n\tVertices: [ ";
    for (psPoint3 v: vertices) {
        os << *v << " ";
    }
    os << "]\n\tTriangles: [ \n";
    for (psTriangle tr : triangles) {
        os << "\t" << *tr << " \n";
    }
    os << "]\n\tCenter: " << center << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream &os, const TrianglesModel &model) {
    return model.print(os);
}

TrianglesModel::TrianglesModel() 
: vertices(container_vertices()), triangles(container_triangles()), center(Point3()) {}

std::pair<container_vertices::iterator, bool> TrianglesModel::addVertex(psPoint3 pv) noexcept {

    for (container_vertices::iterator it = vertices.begin(); it != vertices.end(); ++it) {
        if (*(*it) == *pv) {
            return std::pair<container_vertices::iterator, bool>(it, false);
        }
    }
    vertices.push_back(pv);
    return std::pair<container_vertices::iterator, bool>(--vertices.end(), true);
}

void TrianglesModel::addFace(std::vector<psPoint3> &lst) {
    if (lst.size() != 3) {
        time_t curTime = time(NULL);
        throw SizeFaceTrianglesModelException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    psPoint3 points[3];
    size_t i = 0;
    bool triangle_alredy_exist = true;
    for (psPoint3 elem : lst) {
        // Если равная этой, вершина уже была упомянута, то создадим Triangle на основе ссылки на уже упомянутую вершину
        // А если их этого массива вершины повторяются, то это ошибка будет выявлена при создании Triangle
        std::pair<container_vertices::iterator, bool> rv = addVertex(elem);
        /* Если хоть одна точка из triangle новая в списке, то triangle уникальный, 
        если все точки уже существуют в списке то стоит проверить 
        наличие такого треугольника чтобы не было повторов */
        triangle_alredy_exist = triangle_alredy_exist && !rv.second; 
        points[i] = *(rv.first);
        ++i;
    }

    psTriangle tr = std::make_shared<Triangle>(points[0], points[1], points[2]);
    if (triangle_alredy_exist) {
        for (psTriangle elem : triangles) {
            if (*elem == *tr)
                return;
        }
    }
    triangles.push_back(tr);
}

void TrianglesModel::addFace(std::initializer_list<psPoint3> &lst) {
    if (lst.size() != 3) {
        time_t curTime = time(NULL);
        throw SizeFaceTrianglesModelException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    psPoint3 points[3];
    size_t i = 0;
    bool triangle_alredy_exist = true;
    for (psPoint3 elem : lst) {
        std::cout << "TrianglesModel::addFace elem - " << *elem << "\n";
        // Если равная этой, вершина уже была упомянута, то создадим Triangle на основе ссылки на уже упомянутую вершину
        // А если их этого массива вершины повторяются, то это ошибка будет выявлена при создании Triangle
        std::pair<container_vertices::iterator, bool> rv = addVertex(elem);
        /* Если хоть одна точка из triangle новая в списке, то triangle уникальный, 
        если все точки уже существуют в списке то стоит проверить 
        наличие такого треугольника чтобы не было повторов */
        triangle_alredy_exist = triangle_alredy_exist && !rv.second; 
        points[i] = *(rv.first);
        ++i;
    }

    psTriangle tr = std::make_shared<Triangle>(points[0], points[1], points[2]);
    if (triangle_alredy_exist) {
        for (psTriangle elem : triangles) {
            if (*elem == *tr)
                return;
        }
    }
    triangles.push_back(tr);
}

void TrianglesModel::addFace(std::initializer_list<psPoint3> &&lst) {
    std::initializer_list<psPoint3> _lst(lst);
    this->addFace(_lst);
}

void TrianglesModel::setCenter(Point3 &c) noexcept {
    center = c;
}

void TrianglesModel::setCenter(Point3 &&c) noexcept {
    center = c;
}

container_vertices TrianglesModel::getVertices() const noexcept {
    return vertices;
}

container_triangles TrianglesModel::getTriangles() const noexcept {
    return triangles;
}

Point3 TrianglesModel::getCenter() const noexcept {
    return center;
}

bool TrianglesModel::intersection(const Ray &ray, intersection_t &intersect) const {
    double t_value, min_t_value = std::numeric_limits<double>::max();
    psTriangle trIntersect;

    for (psTriangle tr : triangles) {
        if (tr->intersection(ray, t_value) && t_value < min_t_value) {
            min_t_value = t_value;
            trIntersect = tr;
        }
    }
    if (fabs(std::numeric_limits<double>::max() - min_t_value) < EPS) {
        return false;
    }

    intersect.point = ray(min_t_value);
    intersect.distance = min_t_value;
    intersect.normal = trIntersect->getNormal(ray);

    return true;
}

void TrianglesModel::transform(const std::shared_ptr<TransformAction> action) {
    for (psPoint3 elem : vertices) {
        action->transform(elem);
    }
}

size_t TrianglesModel::getCountFaces() const noexcept {
    return triangles.size();
}