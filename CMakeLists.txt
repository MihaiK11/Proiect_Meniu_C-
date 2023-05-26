cmake_minimum_required(VERSION 3.24)
project(VaccinC__)

set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_STANDARD 17)

add_executable(VaccinC__ main.cpp modules/afisare.cpp modules/programare.cpp clases/rezervare.cpp)
