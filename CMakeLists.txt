cmake_minimum_required(VERSION 3.5)

project(Build)

project(TD)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_LIB src_lib)

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML/lib")

set(SFML_SHARED_LIBRARIES TRUE)

include_directories("${PROJECT_SOURCE_DIR}/SFML/include")

add_executable(${PROJECT_NAME} "src/Main.cpp")

add_subdirectory(src)

include_directories(src)

target_link_libraries(${PROJECT_NAME} "${SFML_DIR}/libsfml-system.2.5.1.dylib"
                    "${SFML_DIR}/libsfml-network.2.5.1.dylib"
                    "${SFML_DIR}/libsfml-graphics.2.5.1.dylib"
                    "${SFML_DIR}/libsfml-audio.2.5.1.dylib"
                    "${SFML_DIR}/libsfml-window.2.5.1.dylib"
                    ${SOURCE_LIB}
)
