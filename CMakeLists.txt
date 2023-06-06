cmake_minimum_required(VERSION 3.0)
project(MyProject)

# Add the source files
set(DATA_SOURCES
    detector.cpp
    config.cpp
)

# Add the static library targets
add_library(detector_lib STATIC ${DATA_SOURCES})
add_library(data_provider_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/data_provider.cpp)
add_library(visualizer_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/visualizer.cpp)

# Add the executable target
add_executable(my_program ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Link the static libraries to the executable
target_link_libraries(my_program PRIVATE detector_lib data_provider_lib visualizer_lib)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

# Include the OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Link the OpenCV library to the executable
target_link_libraries(my_program PRIVATE ${OpenCV_LIBS})
