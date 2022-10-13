# General configs
cmake_minimum_required(VERSION 3.24)
project(AngrySpartyLib)
set(CMAKE_CXX_STANDARD 17)

# Define a variable to hold a list of source files
set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h GameView.cpp GameView.h ids.h Game.cpp Game.h Consts.h)

# Grab the wxWidget library and include the use file
# Additionally, turn off wxWidget's built-in precompiled headers
set(wxBUILD_PRECOMP_OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

# Add source files to this library
add_library(${PROJECT_NAME} ${SOURCE_FILES})

# Link required libraries to this library
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Add precompiled headers to the project
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
