#include "Camera.h"

std::ostream& operator<<(std::ostream &os, const Camera &camera) {
    return camera.print(os);
}

std::ostream& Camera::print(std::ostream& os) const noexcept {
    os << "Camera: \n";
    os << "\tright=" << right << ", up=" << up << ", dir=" << dir <<std::endl;
    os << "\tcameraPos = " << cameraPos << std::endl;
    os << "\tfocalLength = " << focalLength << std::endl;
    os << "\tviewportWidth = " << viewportWidth << std::endl;
    os << "\tviewportHeight = " << viewportHeight << std::endl;
    os << "\tcountPixWidth = " << _countPixWidth << std::endl;
    os << "\tcountPixHeight = " << _countPixHeight << std::endl;
    os << "\twidth_of_one_pixel = " << width_of_one_pixel << "\n\theight_of_one_pixel = " << height_of_one_pixel << std::endl;
    os << "\tupperLeftPixelCoord = " << upperLeftPixelCoord << std::endl;
    return os;
}

Camera::Camera() noexcept 
: right(1, 0, 0), up(0, 1, 0), dir(0, 0, 1), 
focalLength(FOCAL_LENGHT), cameraPos(0, 0, focalLength), viewportHeight(VIEWPORT_HEIGHT) {
    // this->setCountPixelsViewport(COUNT_PIXELS_WIDTH, COUNT_PIXELS_HEIGHT);
    // updateUpperLeftPixelCoord();
}

void Camera::setCountPixelsViewport(size_t countPixWidth, size_t countPixHeight) {
    if (countPixWidth == 0 || countPixHeight == 0) {
        time_t curTime = time(NULL);
        throw CountPixelsCameraException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    _countPixWidth = countPixWidth;
    _countPixHeight = countPixHeight;

    viewportWidth = viewportHeight * (static_cast<float>(countPixWidth) / static_cast<float>(countPixHeight));

    width_of_one_pixel = viewportWidth * right / static_cast<float>(countPixWidth); // ширина одного пикселя
    height_of_one_pixel = viewportHeight * up / static_cast<float>(countPixHeight); // высота одного пикселя 
    
    countPixelsViewportSet = true;
    updateUpperLeftPixelCoord();

    // std::cout << "Use camera:\n" << *this;
}

void Camera::setFocalLength(float focal_length, bool update) {
    if (focal_length < EPS) {   // focal_length < 0
        time_t curTime = time(NULL);
        throw FocalLengthCameraException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    focalLength = focal_length;
    if (update)
        updateUpperLeftPixelCoord();
}

void Camera::setViewportHeight(float viewport_height, bool update) {
    if (viewport_height < EPS) {   // viewport_height < 0
        time_t curTime = time(NULL);
        throw ViewportHeightCameraException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    viewportHeight = viewport_height;
    if (update)
        updateUpperLeftPixelCoord();
}

void Camera::setCameraPos(Point3 pos, bool update) noexcept {
    cameraPos = pos;
    if (update)
        updateUpperLeftPixelCoord();
}

void Camera::updateUpperLeftPixelCoord() {
    if (!countPixelsViewportSet) {
        time_t curTime = time(NULL);
        throw NotSetPixelsCameraException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }

    // координаты левой верхней видимой точки
    Point3 upperLeftCoord = cameraPos - right * (viewportWidth / 2) + up * (viewportHeight / 2) - dir * focalLength;
    // координата центра пикселя (0, 0)
    upperLeftPixelCoord = upperLeftCoord + 0.5 * width_of_one_pixel - 0.5 * height_of_one_pixel;
}

Vector3 Camera::getCameraPos() const noexcept {
    return cameraPos;
}

Ray Camera::createRay(int ip, int jp) {
    if (!countPixelsViewportSet) {
        time_t curTime = time(NULL);
        throw NotSetPixelsCameraException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }

    Vector3 pixelCoord = upperLeftPixelCoord + static_cast<double>(ip) * width_of_one_pixel - static_cast<double>(jp) * height_of_one_pixel;
    Vector3 rayDirection = pixelCoord - cameraPos;
    rayDirection.normalize();
    return Ray(cameraPos, rayDirection);
}

void Camera::transform(const std::shared_ptr<TransformAction> action) {
    cameraPos = action->transform(cameraPos);
    right = action->transform(right);
    up = action->transform(up);
    dir = action->transform(dir);
}