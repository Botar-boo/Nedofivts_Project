cmake_minimum_required(VERSION 3.5)

project(Test)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "SingletonTest.cpp" "../src/Game.cpp")
target_include_directories(${PROJECT_NAME}
	PRIVATE
	${GTEST_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
	PRIVATE
	GTest::GTest
	Threads::Threads)

