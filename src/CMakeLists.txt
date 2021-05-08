cmake_minimum_required(VERSION 3.16) 
project(SRC_LIB_PROJECT)

set(SOURCE_LIB "Adapter.cpp" "AnimationGame.cpp" "Additional.cpp" "Unit.cpp" "Creep.cpp" "Tower.cpp" "Game.cpp" "Maps.cpp" "AdditionalFunctions.cpp" "Gameplay.cpp" "Settings.cpp" "Menu.cpp")

add_library(src_lib STATIC ${SOURCE_LIB})
