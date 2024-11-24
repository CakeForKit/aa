#pragma once

#include <QColor>
#include "Exceptions.h"
#include "Vector3.h"

class Color 
{
protected:
    int rgb[3];

public:
    Color(int r, int g, int b);
    Color(const Color &c);
    Color(Color &&c);
    Color(Intensity &intens);

    const QColor getQColor() const;
    // int r() const noexcept;
    // int g() const noexcept;
    // int b() const noexcept;

    int operator[](size_t ind) const;
    int &operator[](size_t ind);

    Color& operator=(const Color &c) noexcept;
    Color& operator=(Color &&c) noexcept;

    // Color operator*(double num) const noexcept;
};

// Color operator*(const double num, const Color& c) noexcept;
