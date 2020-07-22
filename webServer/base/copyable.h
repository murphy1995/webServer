#ifndef WEBSERVER_BASE_COPYABLE_H
#define WEBSERVER_BASE_COPYABLE_H

namespace webServer
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable
{
 protected:
  copyable() = default;
  ~copyable() = default;
};

}  // namespace webServer

#endif  // WEBSERVER_BASE_COPYABLE_H
