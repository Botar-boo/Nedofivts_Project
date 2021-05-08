cmake_minimum_required(VERSION 3.5)

project(Build)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_LIB src_lib)

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML/lib")
find_package(SFML 2.5.1 COMPONENTS graphics audio window network system)

include_directories("${PROJECT_SOURCE_DIR}/SFML/include")

add_executable(${PROJECT_NAME} "src/Main.cpp")

add_subdirectory(src)

include_directories(src)

target_link_libraries(${PROJECT_NAME} SHARED "-lsfml-graphics"
                    "-lsfml-audio"
                    "-lsfml-window"
                    "-lsfml-network"
                    "-lsfml-system"
                    ${SOURCE_LIB}
)
