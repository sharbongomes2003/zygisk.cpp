cmake_minimum_required(VERSION 3.6)

project(zygisk_injector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

add_library(zygisk SHARED zygisk.cpp)

target_compile_options(zygisk PRIVATE -fPIC -Wall -Oz -fvisibility=hidden)

find_library(log-lib log)
find_library(dl-lib dl)

target_link_libraries(zygisk ${log-lib} ${dl-lib})
