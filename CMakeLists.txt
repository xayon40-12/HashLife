cmake_minimum_required(VERSION 3.9)
project(HashLife)


set(RESSOURCES_PATH /Users/nathan/Programmation/ressources)
set(CMAKE_MODULE_PATH ${RESSOURCES_PATH}/CMake)

find_package(GAPI)

include_directories(${GAPI_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_executable(HashLife main.cpp Tree.cpp Tree.hpp Tree.inl Hashable.hpp Automaton.cpp Automaton.hpp Life.cpp Life.hpp Rule.cpp Rule.hpp Wireworld.cpp Wireworld.hpp Cave.cpp Cave.hpp Physics.cpp Physics.hpp Griffeath.cpp Griffeath.hpp)


target_link_libraries(HashLife ${GAPI_LIBRARY})