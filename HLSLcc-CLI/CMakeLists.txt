cmake_minimum_required(VERSION 2.8)

project(hlslcc-cli)

find_package(hlslcc REQUIRED)
find_package(CLI11 REQUIRED)

add_executable(hlslcc-cli cli.cpp)
target_link_libraries(hlslcc-cli hlslcc)

install(TARGETS hlslcc-cli DESTINATION bin)