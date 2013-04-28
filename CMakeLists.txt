cmake_minimum_required(VERSION 2.8)

project(multi C)

set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -std=c99 -pedantic -I${CMAKE_CURRENT_SOURCE_DIR}/src -O0 -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -std=c99 -I${CMAKE_CURRENT_SOURCE_DIR}/src -O2 -s -DNDEBUG")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}")

add_library(multi_lib SHARED
            src/share/utils.c
            src/share/language.c
            src/share/compile.c
            src/share/config.c
            src/share/arg.c
            src/share/socket.c)

SET_TARGET_PROPERTIES(
    multi_lib
    PROPERTIES
    VERSION 1.0.0
    OUTPUT_NAME multi
)

add_executable(multi
               src/master/file.c
               src/master/usage.c
               src/master/config.c
               src/master/arg.c
               src/master/client.c
               src/master/main.c
               )

target_link_libraries(multi multi_lib)

add_executable(multi-server
               src/deamon/config.c
               src/deamon/arg.c
               src/deamon/usage.c
               src/deamon/server.c
               src/deamon/file.c
               src/deamon/main.c
               )

target_link_libraries(multi-server multi_lib)
target_link_libraries(multi-server pthread)

# DOC

option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML based API documentation" ON)

FIND_PACKAGE(Doxygen)
if (DOXYGEN_FOUND)
    #-- Configure the Template Doxyfile for our specific project
    configure_file(cmake/Doxyfile.in
                   ${PROJECT_BINARY_DIR}/Doxyfile  @ONLY IMMEDIATE)
    add_custom_target(docs ALL
                      COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
                      SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
                      # IF you do NOT want the documentation to be generated EVERY time you build the project
                      # then leave out the 'ALL' keyword from the above command.
endif()
#######################
#######################
##   DISTCLEAN RULE  ##
#######################
#######################

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_clear.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(distclean
  COMMAND ${CMAKE_BUILD_TOOL} clean
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake")
