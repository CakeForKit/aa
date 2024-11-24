#include "Matrix4.h"

std::ostream& Matrix4::print(std::ostream &os) const noexcept {
    std::cout << "Mat4:\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const Matrix4 &m) {
    return m.print(os);
}

Matrix4::Matrix4() : mat(glm::mat4(1.0f)) {}

Matrix4::Matrix4(glm::mat4 &m) : mat(m) {}

Matrix4::Matrix4(glm::mat4 &&m) : mat(m) {}


Matrix4& Matrix4::operator=(const Matrix4 &m) noexcept {
    mat = m.getGlm();
    return *this;
}

Matrix4& Matrix4::operator=(Matrix4 &&m) noexcept {
    mat = m.getGlm();
    return *this;
}

// double Matrix4::operator[](size_t ind) const {
//     return mat[int];
// }

// double &Matrix4::operator[](size_t ind);

Matrix4 Matrix4::operator*(const Matrix4 &m) const noexcept {
    return mat * m.getGlm();
}

Matrix4 Matrix4::operator*(const Matrix4 &&m) const noexcept {
    return mat * m.getGlm();
}

Matrix4& Matrix4::operator*=(const Matrix4 &m) noexcept {
    mat *= m.getGlm();
    return *this;
}
Matrix4& Matrix4::operator*=(const Matrix4 &&m) noexcept {
    mat *= m.getGlm();
    return *this;
}

const glm::mat4 &Matrix4::getGlm() const {
    return mat;
}

Vector3 operator*(const Matrix4 &m, const Vector3 &v) {
    glm::vec4 v4(v.x(), v.y(), v.z(), 1);
    v4 = m.getGlm() * v4;
    return Vector3(v4[0], v4[1], v4[2], v4[3]);
}