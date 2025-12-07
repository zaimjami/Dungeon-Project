cmake_minimum_required(VERSION 3.14)


# cmake_minimum_required (VERSION 2.8.11)

# set default build to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#suppressed the warnings about unused variables
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-unused-variable -Wall" CACHE INTERNAL "")

# get folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# define cmake variables for file locations
file(GLOB USER_FILES_1
"*.h"
"*.cpp"
"*.hpp"
)


file(GLOB TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"test_*.cpp"
)



# Try to Find GTest
find_package(GTest QUIET)

if(GTEST_FOUND)
	message(">> GTest was found among local libraries.")
	include_directories(${GTEST_INCLUDE_DIRS})

	# create an executable for all tests 
	## commented out these two lines so it doesn't make the test executable
	add_executable( 
		my_tests 
		test_case.cc
		enemy_graph.cpp
        enemy_graph.hpp
        hash.cpp
        hash.hpp
        PriorityQueue.cpp
        PriorityQueue.hpp
		)
	target_link_libraries( my_tests gtest_main ${GTEST_LIBRARIES} pthread)

else()
	message(">> Couldn't find Local GTest library, Downloading one instead ...")

	# Download and unpack googletest at configure time
	configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()

	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
		${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	        EXCLUDE_FROM_ALL)

	# create an executable for all tests 
  # commented out these two lines because there are no tests in this example
	add_executable( run_tests ${TEST_FILES} ${USER_FILES_1} )
	target_link_libraries( run_tests gtest_main)

endif()

ENABLE_TESTING()


 add_executable(
        crawl
		driver.cpp
		enemy_graph.cpp
        enemy_graph.hpp
        hash.cpp
        hash.hpp
        PriorityQueue.cpp
        PriorityQueue.hpp
)

