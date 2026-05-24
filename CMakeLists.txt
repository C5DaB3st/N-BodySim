cmake_minimum_required(VERSION 3.20)
project(N_Body_Space)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure internal dependency behaviors
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "")
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

# Fixes the operator mismatch error between ImGui and ImGui-SFML
add_compile_definitions(ImTextureID=void*)

# 1. Add compiled local subdirectories
add_subdirectory(sfml)
add_subdirectory(box2d)

# 2. Tell imgui-sfml where your local imgui folder is
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_subdirectory(imgui-sfml)

# 3. Executable definition
add_executable(N_Body_Space
        main.cpp
        bodies.cpp
        world.cpp
        camera.cpp
)

# 4. Bind include paths and link targets
target_include_directories(N_Body_Space PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/box2cpp/include
)

target_link_libraries(N_Body_Space PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
        box2d
        ImGui-SFML::ImGui-SFML
)

