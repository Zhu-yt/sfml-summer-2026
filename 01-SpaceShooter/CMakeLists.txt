cmake_minimum_required(VERSION 3.16)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML" CACHE PATH "SFML config directory")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SpaceShooter
    src/main.cpp
    src/Game.cpp
    src/World.cpp
    src/Entity.cpp
    src/Aircraft.cpp
    src/Command.cpp
    src/CommandQueue.cpp
)

target_link_libraries(SpaceShooter PRIVATE sfml-graphics sfml-window sfml-system)

set(SFML_DLL_DIR "C:/SFML-2.6.2/bin")

add_custom_command(TARGET SpaceShooter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_DLL_DIR}/sfml-graphics-2.dll"
        "${SFML_DLL_DIR}/sfml-window-2.dll"
        "${SFML_DLL_DIR}/sfml-system-2.dll"
        $<TARGET_FILE_DIR:SpaceShooter>
)