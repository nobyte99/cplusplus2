cmake_minimum_required(VERSION 2.8.12)

project(cplusplus2)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

aux_source_directory(. DIR_SRCS)

add_executable(${PROJECT_NAME}  ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
