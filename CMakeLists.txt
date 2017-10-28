cmake_minimum_required(VERSION 3.8)
project(HashLife)

set(CMAKE_CXX_STANDARD 11)

add_executable(HashLife main.cpp Tree.cpp Tree.hpp Tree.inl Hashable.hpp Automaton.cpp Automaton.hpp Life.cpp Life.hpp Rule.cpp Rule.hpp Wireworld.cpp Wireworld.hpp Cave.cpp Cave.hpp Physics.cpp Physics.hpp Griffeath.cpp Griffeath.hpp)