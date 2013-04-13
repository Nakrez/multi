cmake_minimum_required(VERSION 2.8)

project(multi C)

set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -std=c99 -pedantic -I${CMAKE_CURRENT_SOURCE_DIR}/src -O0 -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -std=c99 -I${CMAKE_CURRENT_SOURCE_DIR}/src -O2 -s -DNDEBUG")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}")

add_executable(multi
               src/share/socket.c

               src/master/file.c
               src/master/main.c
               )

add_executable(multid
               src/share/socket.c

               src/deamon/main.c
               )

#######################
#######################
##    CLEAR RULE     ##
#######################
#######################

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_clear.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(distclean
  COMMAND ${CMAKE_BUILD_TOOL} clean
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake")
