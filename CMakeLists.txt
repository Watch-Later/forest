cmake_minimum_required(VERSION 3.10)

project(forest LANGUAGES CXX VERSION 12.0.1)

# CMake Options

option(FOREST_BUILD_TESTS OFF)
option(FOREST_BUILD_EXAMPLES OFF)
option(FOREST_BUILD_BENCHMARKS OFF)

# Increase Stack on Windows

if(MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")
endif()

# Add Library

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

# Build Tests

if(FOREST_BUILD_TESTS)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/Catch2")
	enable_testing()
	macro(forest_add_test TESTNAME)
		add_executable(${TESTNAME} ${ARGN})
		target_link_libraries(${TESTNAME} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
		target_link_libraries(${TESTNAME} PRIVATE Catch2)
		add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
		set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
	endmacro()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()

# Build Examples

if(FOREST_BUILD_EXAMPLES)
	macro(forest_add_example EXAMPLENAME)
		add_executable(${EXAMPLENAME} ${ARGN})
		target_link_libraries(${EXAMPLENAME} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
		set_target_properties(${EXAMPLENAME} PROPERTIES FOLDER examples)
	endmacro()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/examples")
endif()

# Build Benchmarks

if(FOREST_BUILD_BENCHMARKS)
	set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/benchmark")
	macro(forest_add_benchmark BENCHMARKNAME)
		add_executable(${BENCHMARKNAME} ${ARGN})
		target_link_libraries(${BENCHMARKNAME} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
		target_link_libraries(${BENCHMARKNAME} PRIVATE benchmark)
		set_target_properties(${BENCHMARKNAME} PROPERTIES FOLDER benchmarks)
	endmacro()
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/benchmarks")
endif()

# Install Library

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

# Package Library

set(CPACK_PACKAGE_VENDOR "George Fotopoulos")
set(CPACK_PACKAGE_CONTACT "xorz57@protonmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Template Library of Tree Data Structures")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")

include(CPack)
