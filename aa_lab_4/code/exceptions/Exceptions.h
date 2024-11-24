#pragma once
#include "BaseException.h"

#pragma region Build

class NoSelectedModelException: public GuiException
{
public:
    NoSelectedModelException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "You need to choose a model") noexcept:
                  GuiException(time, filename, line, class_name, method_name, info){};
};

#pragma region end


#pragma region Build

class NoFacesBuilderException: public BuilderException
{
public:
    NoFacesBuilderException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Can not build model with 0 faces") noexcept:
                  BuilderException(time, filename, line, class_name, method_name, info){};
};

#pragma region end

#pragma region Read
class NoFileReadException: public ReadException
{
public:
    NoFileReadException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Error open file") noexcept:
                  ReadException(time, filename, line, class_name, method_name, info){};
};

class SymbolReadException: public ReadException
{
public:
    SymbolReadException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Unexpected symbol read") noexcept:
                  ReadException(time, filename, line, class_name, method_name, info){};
};

class FloatReadException: public ReadException
{
public:
    FloatReadException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Expected read float") noexcept:
                  ReadException(time, filename, line, class_name, method_name, info){};
};

class EndReadException: public ReadException
{
public:
    EndReadException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Unexpected end of file") noexcept:
                  ReadException(time, filename, line, class_name, method_name, info){};
};

#pragma region end

#pragma region Scene

class LastCameraSceneException: public SceneException
{
public:
    LastCameraSceneException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Can't delete the last camera") noexcept:
                  SceneException(time, filename, line, class_name, method_name, info){};
};

class NoModelsSceneException: public SceneException
{
public:
    NoModelsSceneException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "There are no models left on the scene") noexcept:
                  SceneException(time, filename, line, class_name, method_name, info){};
};

#pragma region end

#pragma region Camera

class NotSetPixelsCameraException: public CameraException
{
public:
    NotSetPixelsCameraException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Count pixels viewport not set") noexcept:
                  CameraException(time, filename, line, class_name, method_name, info){};
};

class CountPixelsCameraException: public CameraException
{
public:
    CountPixelsCameraException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Count pixels wight or height can not be 0") noexcept:
                  CameraException(time, filename, line, class_name, method_name, info){};
};

class FocalLengthCameraException: public CameraException
{
public:
    FocalLengthCameraException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Focal length can not be < 0") noexcept:
                  CameraException(time, filename, line, class_name, method_name, info){};
};

class ViewportHeightCameraException: public CameraException
{
public:
    ViewportHeightCameraException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Viewport height can not be < 0") noexcept:
                  CameraException(time, filename, line, class_name, method_name, info){};
};

#pragma region end


#pragma region TrianglesModel

// class PointExistsTrianglesModelException: public TrianglesModelException
// {
// public:
//     PointExistsTrianglesModelException(const char *time, const char *filename,
//                   const size_t line, const char *class_name,
//                   const char *method_name, const char *info = "Try to add existing point to triangleModel") noexcept:
//                   TrianglesModelException(time, filename, line, class_name, method_name, info){};
// };

// class TriangleExistsTrianglesModelException: public TrianglesModelException
// {
// public:
//     TriangleExistsTrianglesModelException(const char *time, const char *filename,
//                   const size_t line, const char *class_name,
//                   const char *method_name, const char *info = "Try to add existing triangle to triangleModel") noexcept:
//                   TrianglesModelException(time, filename, line, class_name, method_name, info){};
// };

class SizeFaceTrianglesModelException: public TrianglesModelException
{
public:
    SizeFaceTrianglesModelException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Number of vertices in a face is not 3") noexcept:
                  TrianglesModelException(time, filename, line, class_name, method_name, info){};
};

#pragma region end

#pragma region Triangle

class SamePointsTriangleException: public TriangleException
{
public:
    SamePointsTriangleException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Try create Triangle from same points") noexcept:
                  TriangleException(time, filename, line, class_name, method_name, info){};
};

class DegenerateTriangleException: public TriangleException
{
public:
    DegenerateTriangleException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Try create degenerate Triangle") noexcept:
                  TriangleException(time, filename, line, class_name, method_name, info){};
};

#pragma region end