#include <cstdio>
#include "BaseException.h"

BaseException::BaseException(const char *time, const char *filename,
                            const size_t line, const char *class_name,
                            const char *method_name, const char *info) noexcept
{
    int ind = 0;
    ErrorInfo[0] = '\0';

    if (info)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - static_cast<size_t>(ind), "ERROR:\nInfo: %s, \n", info);

    if (filename)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - static_cast<size_t>(ind), "File: %s, \n", filename);

    ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - static_cast<size_t>(ind), "Line: %zu, \n", line);

    if (class_name)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - static_cast<size_t>(ind), "Class: %s, \n", class_name);

    if (method_name)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - static_cast<size_t>(ind), "Method: %s, \n", method_name);

    if (time)
        ind += snprintf(&ErrorInfo[ind], sizeof(ErrorInfo) - static_cast<size_t>(ind), "Time: %s \n", time);
}

const char *BaseException::what() const noexcept
{
    return ErrorInfo;
}