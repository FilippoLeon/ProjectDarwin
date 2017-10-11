cmake_minimum_required(VERSION 3.8)
project(ProjectDarwin)

include(ExternalProject)
find_package(Git REQUIRED)


ExternalProject_Add(
    project_fmt
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/external
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    TIMEOUT 10
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_SOURCE_DIR}/external
)

ExternalProject_Get_Property(project_fmt source_dir)
ExternalProject_Get_Property(project_fmt install_dir)
set(FMTLIB_INCLUDE_DIR ${install_dir}/include CACHE INTERNAL "Path to include folder for fmtlib")
set(FMTLIB_ROOT_DIR ${source_dir} CACHE INTERNAL "Path to source folder for fmtlib")
set(FMTLIB_LIBRARIES ${install_dir}/lib CACHE INTERNAL "Path to source folder for fmtlib")
add_library(fmt STATIC IMPORTED)
set_property(TARGET fmt PROPERTY IMPORTED_LOCATION ${FMTLIB_LIBRARIES}/libfmt.a)

add_definitions("-std=c++17")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(Allegro 5.0 COMPONENTS main image REQUIRED)
find_package(Threads)

set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    ON)
find_package(Boost COMPONENTS log log_setup thread filesystem system REQUIRED)

include_directories(${allegro_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${FMTLIB_INCLUDE_DIR})

include_directories(src/)

file(GLOB_RECURSE SOURCES_LIST "src/*.cpp")

add_executable(main ${SOURCES_LIST})
add_dependencies(main project_fmt)

link_directories(${FMTLIB_LIBRARIES})
target_link_libraries(main ${allegro_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} fmt)