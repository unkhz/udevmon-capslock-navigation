cmake_minimum_required(VERSION 3.0)

project(udevmon-capslock-navigation)

add_executable(udevmon-capslock-navigation udevmon-capslock-navigation.c)
target_compile_options(udevmon-capslock-navigation PRIVATE -Wall -Wextra)

install(TARGETS udevmon-capslock-navigation RUNTIME DESTINATION bin)
