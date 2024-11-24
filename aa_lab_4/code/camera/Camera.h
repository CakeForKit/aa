#pragma once

#include "ObjectScene.h"
#include "Exceptions.h"
#include "Ray.h"
#include "Vector3.h"

class Camera
{
protected:
    // параметры которые устанавливаются при создании
    Vector3 right, up, dir; // базис x, y, z
    float focalLength;
    Vector3 cameraPos;
    float viewportHeight;

    // флаг, установлены ли параметры размера экрана в пикселях для данной камеры
    // Если нет то создать луч не получится
    bool countPixelsViewportSet = false; 

    // параметры которые рассчитываются из функции updateUpperLeftPixelCoord()
    float viewportWidth;                                // высота области просмотра, в координатах
    Vector3 width_of_one_pixel;                         // ширина и высота одного пикселя
    Vector3 height_of_one_pixel;    
    Point3 upperLeftPixelCoord;                         // координата центра пикселя (0, 0)

    // not need, just see
    size_t _countPixWidth;
    size_t _countPixHeight;

public:
    Camera() noexcept;

    void setFocalLength(float focal_length, bool update = true);
    void setViewportHeight(float viewport_height, bool update = true);
    void setCameraPos(Point3 pos, bool update = true) noexcept;
    void setCountPixelsViewport(size_t countPixWidth, size_t countPixHeight);

    void updateUpperLeftPixelCoord();
    Vector3 getCameraPos() const noexcept;

    /// @brief Создает луч направленный в пиксель (xp, yp)
    /// @param ip коорд пикселя по X
    /// @param jp коорд пикселя по Y
    /// @return Нормализованный луч
    Ray createRay(int ip, int jp);

    void transform(const std::shared_ptr<TransformAction> action);

    std::ostream& print(std::ostream& os) const noexcept;
};

std::ostream& operator<<(std::ostream &os, const Camera &camera);

