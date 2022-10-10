# General configs
cmake_minimum_required(VERSION 3.24)
project(Project1)
set(CMAKE_CXX_STANDARD 17)

# Define a variable to hold the name of the application library
set(APPLICATION_LIBRARY AngrySpartyLib)

# Define a variable to hold a list of source files
set(SOURCE_FILES main.cpp AngrySpartyApp.cpp AngrySpartyApp.h pch.h)

# Grab the wxWidget library and include the use file
# Additionally, turn off wxWidget's built-in precompiled headers
set(wxBUILD_PRECOMP_OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

# add the application library to this project
add_subdirectory(${APPLICATION_LIBRARY})
include_directories(${APPLICATION_LIBRARY})

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link required libraries to the executable
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

# Add precompiled headers to the project
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)