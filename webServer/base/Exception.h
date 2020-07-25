#ifndef WEBSERVER_BASE_EXCEPTION_H
#define WEBSERVER_BASE_EXCEPTION_H

#include "webServer/base/Types.h"
#include <exception>

namespace webServer
{

class Exception : public std::exception
{
 public:
  Exception(string what);
  ~Exception() noexcept override = default;

  // default copy-ctor and operator= are okay.

  const char* what() const noexcept override
  {
    return message_.c_str();
  }

  const char* stackTrace() const noexcept
  {
    return stack_.c_str();
  }

 private:
  string message_;
  string stack_;
};

}  // namespace webServer

#endif  // MUDUO_BASE_EXCEPTION_H
