# Versao minima do cmake
cmake_minimum_required(VERSION 3.3)

# Nome do meu projeto
project(EngrenagemDeMetalSolida)

#
add_executable(EngrenagemDeMetalSolida src/main.cpp)
#add_executable(EngrenagemDeMetalSolida src/main.cpp src/viewer.cpp src/map.cpp src/controller.cpp src/element.cpp src/player.cpp src/collisionController.cpp src/camera.cpp src/camera_controller.cpp src/eventos.cpp src/porta.cpp src/porta_controller.cpp)

# Especificar onde estao os header files
include_directories(include)

add_library(controller src/controller.cpp)
target_link_libraries(controller viewer map element player collisionController camera camera_controller eventos porta porta_controller SDL2 SDL2_image)

# Bibliotecas locais (estaticas)
add_library(viewer src/viewer.cpp)
target_link_libraries(viewer player camera SDL2 SDL2_image)

add_library(map src/map.cpp)
target_link_libraries(map SDL2 SDL2_image)

add_library(element src/element.cpp)
target_link_libraries(element SDL2 SDL2_image)

add_library(player src/player.cpp)
target_link_libraries(player element)

add_library(collisionController src/collisionController.cpp)
target_link_libraries(collisionController player map)

add_library(camera src/camera.cpp)
target_link_libraries(camera element)

add_library(camera_controller src/camera_controller.cpp)
target_link_libraries(camera_controller camera player map)

add_library(eventos src/eventos.cpp)
target_link_libraries(eventos player camera player)

add_library(porta src/porta.cpp)
target_link_libraries(porta element)

add_library(porta_controller src/porta_controller.cpp)
target_link_libraries(porta_controller player porta map)

#target_link_libraries(EngrenagemDeMetalSolida viewer map controller element player collisionController camera camera_controller eventos porta porta_controller SDL2 SDL2_image)
target_link_libraries(EngrenagemDeMetalSolida controller)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
#target_link_libraries(EngrenagemDeMetalSolida SDL2)
#target_link_libraries(EngrenagemDeMetalSolida SDL2_image)

# Automatizacao do Doxygen
# dot: gerador de diagramas do graphviz
find_package(Doxygen REQUIRED dot)

set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN EXTRACT_STATIC YES)
set(DOXYGEN_TEMPLATE_RELATIONS YES)
set(DOXYGEN_COLLABORATION_GRAPH YES)
set(DOXYGEN_UML_LOOK YES)
set(DOXYGEN_CLASS_GRAPH YES)

doxygen_add_docs(doc)

