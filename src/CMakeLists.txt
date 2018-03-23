
add_executable(allocator main.cpp )

target_include_directories(allocator PRIVATE ../include)

#SET( CMAKE_VERBOSE_MAKEFILE ON )
set_target_properties(allocator PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wall -Wextra -Wpedantic 
)

#set(CMAKE_BUILD_TYPE Debug)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT lisstic.tt@gmail.com)

include (CPack)
