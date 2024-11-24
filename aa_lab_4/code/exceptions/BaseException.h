#pragma once

#include <exception>

class BaseException : public std::exception
{
public:
    BaseException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "no info") noexcept;

    const char* what() const noexcept override;

    virtual ~BaseException() {};
protected:
    char ErrorInfo[1000];
};

#pragma region Abstracts of groups

class TrianglesModelException: public BaseException
{
public:
    TrianglesModelException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "TrianglesModelException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class TriangleException: public BaseException
{
public:
    TriangleException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "TriangleException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class CameraException: public BaseException
{
public:
    CameraException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "CameraException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class SceneException: public BaseException
{
public:
    SceneException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "SceneException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class ReadException: public BaseException
{
public:
    ReadException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "ReadException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class BuilderException: public BaseException
{
public:
    BuilderException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "BuilderException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

// class DirectorException: public BaseException
// {
// public:
//     DirectorException(const char *time, const char *filename,
//                   const size_t line, const char *class_name,
//                   const char *method_name, const char *info = "DirectorException") noexcept:
//                   BaseException(time, filename, line, class_name, method_name, info){};
// };

class GuiException: public BaseException
{
public:
    GuiException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "GuiException") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

#pragma region end

#pragma region StandartException

class IndexException: public BaseException
{
public:
    IndexException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Index out of range") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class DivZeroException: public BaseException
{
public:
    DivZeroException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Division zero") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class ParameterFuncException: public BaseException
{
public:
    ParameterFuncException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Error parameter function") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};

class NormalizeDivZeroException: public BaseException
{
public:
    NormalizeDivZeroException(const char *time, const char *filename,
                  const size_t line, const char *class_name,
                  const char *method_name, const char *info = "Division zero in normalizing vector") noexcept:
                  BaseException(time, filename, line, class_name, method_name, info){};
};
#pragma region end