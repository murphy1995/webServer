set(base_SRCS
  Timestamp.cc
  Exception.cc
  CountDownLatch.cc
  CurrentThread.cc
  Thread.cc
  )

add_library(webServer_base ${base_SRCS})
target_link_libraries(webServer_base pthread rt)

#add_library(muduo_base_cpp11 ${base_SRCS})
#target_link_libraries(muduo_base_cpp11 pthread rt)
#set_target_properties(muduo_base_cpp11 PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS webServer_base DESTINATION lib)
#install(TARGETS muduo_base_cpp11 DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/webServer/base)

if(WEBSERVER_BUILD_EXAMPLES)
  add_subdirectory(tests)
endif()
