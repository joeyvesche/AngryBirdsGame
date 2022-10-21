# General configs
cmake_minimum_required(VERSION 3.24)
project(AngrySpartyLib)
set(CMAKE_CXX_STANDARD 17)

# Define a variable to hold a list of source files
set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h GameView.cpp GameView.h ids.h Game.cpp Game.h Consts.h Item.cpp Item.h Block.cpp Block.h SlingShot.cpp SlingShot.h Scoreboard.cpp Scoreboard.h ItemVisitor.cpp ItemVisitor.h Foe.cpp Foe.h AngrySparty.cpp AngrySparty.h GruffSparty.cpp GruffSparty.h HelmetSparty.cpp HelmetSparty.h Level.cpp Level.h Physics.cpp Physics.h Background.cpp Background.h ItemBody.cpp ItemBody.h Poly.cpp Poly.h)

# Grab the wxWidget library and include the use file
# Additionally, turn off wxWidget's built-in precompiled headers
set(wxBUILD_PRECOMP_OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

# Add source files to this library
add_library(${PROJECT_NAME} ${SOURCE_FILES})

# Add Box2D to the project
include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d)
include_directories(${box2d_SOURCE_DIR}/include/box2d)

# Link required libraries to this library
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} box2d)

# Add precompiled headers to the project
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)


