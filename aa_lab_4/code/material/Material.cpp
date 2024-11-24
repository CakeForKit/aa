#include "Material.h"


Material::Material(Intensity &&_ka, Intensity &&_kd, Intensity &&_ks, double _n)
: ka(_ka), kd(_kd), ks(_ks), n(_n) {
    double xsum, ysum, zsum;
    xsum = ka.x() + kd.x() + 2 * ks.x();
    ysum = ka.y() + kd.y() + 2 * ks.y();
    zsum = ka.z() + kd.z() + 2 * ks.z();
    assert(0 <= xsum && xsum <= 1.0 + EPS);
    assert(0 <= ysum && ysum <= 1.0 + EPS);
    assert(0 <= zsum && zsum <= 1.0 + EPS);
}

const Intensity Material::getKa() const noexcept { return ka; }

const Intensity Material::getKd() const noexcept { return kd; }

const Intensity Material::getKs() const noexcept { return ks; }

double Material::getN() const noexcept { return n; }