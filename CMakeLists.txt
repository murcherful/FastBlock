cmake_minimum_required(VERSION 2.7)

project(Game)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
add_executable(Game main.cpp ScreenDraw.cpp KeyBoard.cpp MainControl.cpp Scene.cpp Floor.cpp Player.cpp Record.cpp)
