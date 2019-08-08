project(Interface-Test)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCL REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
add_subdirectory(pybind11)

set(SOURCE_FILES src/DiscoveryUtils.cpp src/PythonModule.cpp)

add_library(TestModule SHARED ${SOURCE_FILES})
target_include_directories(TestModule PUBLIC ${OpenCL_INCLUDE_DIRS} ./include ${PYTHON_INCLUDE_DIRS})
target_link_libraries(TestModule PUBLIC pybind11::pybind11 ${OpenCL_LIBRARIES} ${PYTHON_LIBRARIES} )
set_target_properties(TestModule PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")

set(TEST_FILES src/Test.cpp )
add_executable(Test ${TEST_FILES})
target_include_directories(Test PUBLIC ./include)
target_link_libraries(Test PUBLIC TestModule)
