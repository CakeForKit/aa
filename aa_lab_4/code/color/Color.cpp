#include "Color.h"

Color::Color(int r, int g, int b) {
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

Color::Color(const Color &c) {
    for (size_t i = 0; i < 3; ++i)
        rgb[i] = c[i];
}

Color::Color(Color &&c) {
    for (size_t i = 0; i < 3; ++i)
        rgb[i] = c[i];
}

Color::Color(Intensity &intens) {
    int c;
    for (size_t i = 0; i < 3; ++i) {
        c = static_cast<int>(std::round(intens[i] * 255)); 
        if (c >= 255)
            rgb[i] = 255;
        else if (c <= 0)
            rgb[i] = 0;
        else
            rgb[i] = c;
    }
    // std::cout << "Color() = " << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << "\n";
}


const QColor Color::getQColor() const {
    return QColor(rgb[0], rgb[1], rgb[2]);
}

// int Color::r() const noexcept {
//     return rgb[0];
// }

// int Color::g() const noexcept {
//     return rgb[1];
// }

// int Color::b() const noexcept {
//     return rgb[2];
// }

int Color::operator[](size_t ind) const {
    if (ind >= 3) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return rgb[ind];
}

int &Color::operator[](size_t ind) {
    if (ind >= 3) {
        time_t curTime = time(NULL);
        throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return rgb[ind];
}

Color& Color::operator=(const Color &c) noexcept {
    for (size_t i = 0; i < 3; ++i) 
        rgb[i] = c[i];
    return *this;
}

Color& Color::operator=(Color &&c) noexcept {
    for (size_t i = 0; i < 3; ++i) 
        rgb[i] = c[i];
    return *this;
}

// Color Color::operator*(double num) const noexcept {
//     Color c(*this);
//     for (size_t i = 0; i < 3; ++i) 
//         c[i] *- num;
// }

// Color Color::operator*(const double num, const Color& c) noexcept {

// }