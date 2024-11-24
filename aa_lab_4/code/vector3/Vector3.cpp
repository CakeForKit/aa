#include "Vector3.h"

#include <iomanip>

std::ostream& operator<<(std::ostream &os, const Vector3 &v) {
    return os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
}

Vector3::Vector3() noexcept {
    for (size_t i = 0; i < 3; ++i) 
        coord[i] = 0;
}

Vector3::Vector3(double x, double y, double z, double w) noexcept{
    // if (w  0)
    //     w = 1;
    coord[0] = x / w;
    coord[1] = y / w;
    coord[2] = z / w;
}

Vector3::Vector3(Vector3 &&v) noexcept {
    for (size_t i = 0; i < 3; ++i) {
        coord[i] = v[i];
    }
}

Vector3::Vector3(const Vector3 &v) {
    for (size_t i = 0; i < 3; ++i) {
        coord[i] = v[i];
    }
}

double Vector3::x() const noexcept { return coord[0]; }
double Vector3::y() const noexcept { return coord[1]; }
double Vector3::z() const noexcept { return coord[2]; }

void Vector3::setX(double x) noexcept { coord[0] = x; }
void Vector3::setY(double y) noexcept { coord[1] = y; }
void Vector3::setZ(double z) noexcept { coord[2] = z; }

double Vector3::operator[](size_t ind) const { 
    if (ind >= 3) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return coord[ind];
}

double &Vector3::operator[](size_t ind) { 
    if (ind >= 3) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return coord[ind];
}

Vector3& Vector3::operator=(const Vector3 &v) noexcept {
    for (size_t i = 0; i < 3; ++i) 
        coord[i] = v[i];
    return *this;
}
Vector3& Vector3::operator=(Vector3 &&v) noexcept {
    for (size_t i = 0; i < 3; ++i)
        coord[i] = v[i];
    return *this;
}

bool Vector3::operator==(const Vector3 &v) const noexcept {
    for (size_t i = 0; i < 3; ++i) 
        if (fabs(coord[i] - v[i]) >= EPS)
            return false;
    return true;
}
bool Vector3::operator!=(const Vector3 &v) const noexcept {
    return !(*this == v);
}

Vector3 Vector3::operator-() const noexcept {
    return *this * (-1);
}

double Vector3::scalarProduct(const Vector3 &v) const noexcept {
    double res = 0;
    for (size_t i = 0; i < 3; ++i)
        res += coord[i] * v[i];
    return res;
}

Vector3 Vector3::vectorProduct(const Vector3 &v) const noexcept {
    Vector3 res;
    res[0] = this->y() * v.z() - this->z() * v.y();
    res[1] = this->z() * v.x() - this->x() * v.z();
    res[2] = this->x() * v.y() - this->y() * v.x();
    return res;
}

Vector3 Vector3::reflect(Vector3 &norm) const {
    if (!norm.isNormalized())
        norm.normalize();

    double scalProduct = this->scalarProduct(norm);
    if (scalProduct > 0) {
        scalProduct *= -1;
        norm = -norm;
    }
    // std::cout << "\n\nscalProduct = " << scalProduct << "\n"; 
    // std::cout << "norm = " << norm << "\n";
    
    Vector3 vreflect = *this - 2.0 * scalProduct * norm;
    vreflect.normalize();
    return vreflect;
}

Vector3 Vector3::refract(Vector3 &norm, double refrIndFrom, double refrIndexTo) const {
    if (this->scalarProduct(norm) > 0)
        norm = -norm;

    double ratioRefrIndex = refrIndFrom / refrIndexTo;
    double ratioRefrIndex2 = ratioRefrIndex * ratioRefrIndex;
    double cosaL = -this->scalarProduct(norm) / this->length() / norm.length();
    double cos2aT = 1 - ratioRefrIndex2 * (1 - cosaL * cosaL);
    if (cos2aT < 0)
        return Vector3(0, 0, 0);

    Vector3 vrefract = ratioRefrIndex * (this->normalized()) + norm * (ratioRefrIndex * cosaL - sqrt(cos2aT));
    vrefract.normalize();
    return vrefract;
}

double Vector3::length()  const noexcept{
    return static_cast<double>(sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]));
}

void Vector3::normalize() {
    double len = this->length();
    if (fabs(len) < EPS) {
        time_t curTime = time(NULL);
        throw NormalizeDivZeroException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }

    for (size_t i = 0; i < 3; ++i) 
        coord[i] /= len;
}

bool Vector3::isNormalized() const noexcept {
    return fabs(this->length() - 1) < EPS;
}

Vector3 Vector3::normalized() const {
    Vector3 vec(*this);
    vec.normalize();
    return vec;
}

bool Vector3::isNull() const noexcept {
    return fabs(this->length()) < EPS;
}

bool Vector3::isBelongsToLine(const Vector3 &p1, const Vector3 &p2) const noexcept {
    double kx, ky, kz;
    kx = (this->x() - p1.x()) / (p2.x() - p1.x());
    ky = (this->y() - p1.y()) / (p2.y() - p1.y());
    kz = (this->z() - p1.z()) / (p2.z() - p1.z());

    if (fabs(kx - ky) < EPS && fabs(ky - kz) < EPS)
        return true;
    return false;
}

Vector3 Vector3::operator+(double num) const noexcept {
    Vector3 v(*this);
    for (size_t i = 0; i < 3; ++i) {
        v[i] += num;
    }
    return v;
}

Vector3 operator+(const double num, const Vector3& vec) noexcept{
    return vec - num;
}

Vector3 Vector3::operator-(double num) const noexcept {
    Vector3 v(*this);
    for (size_t i = 0; i < 3; ++i) {
        v[i] -= num;
    }
    return v;
}

Vector3 operator-(const double num, const Vector3& vec) noexcept {
    return vec - num;
}

Vector3 Vector3::operator*(double num) const noexcept {
    Vector3 v(*this);
    for (size_t i = 0; i < 3; ++i) {
        v[i] *= num;
    }
    return v;
}

Vector3 operator*(const double num, const Vector3& vec) noexcept {
    return vec * num;
}

Vector3 Vector3::operator/(double num) const {
    if (fabs(num) < EPS) {
        time_t curTime = time(NULL);
        throw DivZeroException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    Vector3 v(*this);
    for (size_t i = 0; i < 3; ++i) {
        v[i] /= num;
    }
    return v;
}

Vector3 operator/(const double num, const Vector3& vec) {
    return vec / num;
}

Vector3 Vector3::operator+(const Vector3 &v) const noexcept {
    Vector3 res(*this);
    for (size_t i = 0; i < 3; ++i) {
        res[i] += v[i];
    }
    return res;
}

Vector3 Vector3::operator+(const Vector3 &&v) const noexcept {
    Vector3 res(*this);
    for (size_t i = 0; i < 3; ++i) {
        res[i] += v[i];
    }
    return res;
}

Vector3& Vector3::operator+=(const Vector3 &v) noexcept {
    for (size_t i = 0; i < 3; ++i) {
        coord[i] += v[i];
    }
    return *this;
}

Vector3& Vector3::operator+=(const Vector3 &&v) noexcept {
    for (size_t i = 0; i < 3; ++i) {
        coord[i] += v[i];
    }
    return *this;
}

Vector3 Vector3::operator-(const Vector3 &v) const noexcept {
    Vector3 res(*this);
    for (size_t i = 0; i < 3; ++i) {
        res[i] -= v[i];
    }
    return res;
}

Vector3 Vector3::operator-(const Vector3 &&v) const noexcept {
    Vector3 res(*this);
    for (size_t i = 0; i < 3; ++i) {
        res[i] -= v[i];
    }
    return res;
}

Vector3 Vector3::operator*(const Vector3 &v) const noexcept {
    Vector3 res(*this);
    for (size_t i = 0; i < 3; ++i) {
        res[i] *= v[i];
    }
    return res;
}

Vector3 Vector3::operator*(const Vector3 &&v) const noexcept {
    Vector3 res(*this);
    for (size_t i = 0; i < 3; ++i) {
        res[i] *= v[i];
    }
    return res;
}