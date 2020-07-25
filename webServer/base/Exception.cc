// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#include "webServer/base/Exception.h"
#include "webServer/base/CurrentThread.h"

namespace webServer
{

Exception::Exception(string msg)
  : message_(std::move(msg)),
    stack_(CurrentThread::stackTrace(/*demangle=*/false))
{
}

}  // namespace webServer
