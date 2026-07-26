cmake_minimum_required(VERSION 3.16)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML" CACHE PATH "SFML config directory")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SpaceShooter src/main.cpp)

target_link_libraries(SpaceShooter PRIVATE sfml-graphics sfml-window sfml-system)