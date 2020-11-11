# Versao minima do cmake
cmake_minimum_required(VERSION 3.3)

# Nome do meu projeto
project(EngrenagemDeMetalSolida)

#
add_executable(EngrenagemDeMetalSolida main.cpp viewer.cpp map.cpp controller.cpp element.cpp player.cpp collisionController.cpp camera.cpp camera_controller.cpp eventos.cpp porta.cpp porta_controller.cpp)
#add_executable(EngrenagemDeMetalSolida main.cpp viewer.cpp map.cpp controller.cpp element.cpp player.cpp collisionController.cpp)

# Especificar onde estao os header files
include_directories(.)

# Bibliotecas locais (estaticas)
#add_library(src/main.cpp)
#target_link_libraries(EngrenagemDeMetalSolida)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(EngrenagemDeMetalSolida SDL2)
target_link_libraries(EngrenagemDeMetalSolida SDL2_image)

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

