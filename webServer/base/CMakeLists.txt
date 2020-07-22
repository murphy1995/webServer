set(base_SRCS
  Timestamp.cc
  )

add_library(webServer_base ${base_SRCS})
target_link_libraries(webServer_base pthread rt)

PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS webServer_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/webServer/base)

#if(MUDUO_BUILD_EXAMPLES)
#  add_subdirectory(tests)
#endif()
