cmake_minimum_required(VERSION 3.16)
project(CerenkovSim)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# KRİTİK SATIR: Derleyiciye .hh dosyalarının nerede olduğunu söyler
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.cc")
file(GLOB headers "${PROJECT_SOURCE_DIR}/include/*.hh")

add_executable(CerenkovSim main.cc ${sources} ${headers})
target_link_libraries(CerenkovSim ${Geant4_LIBRARIES})

# Makroları kopyala
set(SCRIPTS vis.mac)
foreach(_script ${SCRIPTS})
  configure_file(${_script} ${CMAKE_CURRENT_BINARY_DIR}/${_script} COPYONLY)
endforeach()