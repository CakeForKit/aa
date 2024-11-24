#pragma once

#include "Vector3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Matrix4 
{
protected:
    glm::mat4 mat;

public:
    Matrix4();
    Matrix4(glm::mat4 &m);
    Matrix4(glm::mat4 &&m);
    ~Matrix4() = default;

    Matrix4& operator=(const Matrix4 &m) noexcept;
    Matrix4& operator=(Matrix4 &&m) noexcept;

    // double operator[](size_t ind) const;
    // double &operator[](size_t ind);

    Matrix4 operator*(const Matrix4 &m) const noexcept;
    Matrix4 operator*(const Matrix4 &&m) const noexcept;

    Matrix4& operator*=(const Matrix4 &m) noexcept;
    Matrix4& operator*=(const Matrix4 &&m) noexcept;

    const glm::mat4 &getGlm() const;

    std::ostream& print(std::ostream &os) const noexcept;
};

Vector3 operator*(const Matrix4 &m, const Vector3 &v);

std::ostream& operator<<(std::ostream &os, const Matrix4 &m);

