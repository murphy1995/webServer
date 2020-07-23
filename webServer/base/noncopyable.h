#ifndef WEBSERVER_BASE_NONCOPYABLE_H
#define WEBSERVER_BASE_NONCOPYABLE_H

namespace webServer
{

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}  // namespace webServer

#endif  // MUDUO_BASE_NONCOPYABLE_H
