# General configs
cmake_minimum_required(VERSION 3.24)
project(Project1)
set(CMAKE_CXX_STANDARD 17)

# Define a variable to hold the name of the application library
set(APPLICATION_LIBRARY AngrySpartyLib)

# Define a variable to hold a list of source files
set(SOURCE_FILES main.cpp AngrySpartyApp.cpp AngrySpartyApp.h)

# Grab the wxWidget library and include the use file
# Additionally, turn off wxWidget's built-in precompiled headers
set(wxBUILD_PRECOMP_OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

# Add the application library to this project
add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

# Add the testing library to this project
add_subdirectory(Tests)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

#Load in image files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

#Load in test files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/test/)
#Load in level files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)

# Add precompiled headers to the project
target_precompile_headers(${PROJECT_NAME} PRIVATE ./${APPLICATION_LIBRARY}/pch.h)