cmake_minimum_required(VERSION 2.6)
project(Toy-Engine)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
# signals not needed because BOOST Signals2 is header only
find_package(Boost 1.46.1 COMPONENTS REQUIRED program_options log)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Toy-Engine_SOURCE_DIR}/include)

add_subdirectory(modules EXCLUDE_FROM_ALL)

add_executable(${CMAKE_PROJECT_NAME}
  src/glEntry.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})
