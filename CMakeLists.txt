cmake_minimum_required (VERSION 2.6)
project (WhimsyTestBenchmark)

#set(DEBUG_MODE Yes)

#if(DEBUG_MODE)
#    set(CMAKE_BUILD_TYPE Debug)
#else()
#    set(CMAKE_BUILD_TYPE Release)
#endif()

# Enable Warnings
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# Include C++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Create our test programs
add_subdirectory(Test01)
add_subdirectory(Test02)
add_subdirectory(Test03)
add_subdirectory(Test04)
add_subdirectory(Test05)
