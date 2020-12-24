cmake_minimum_required(VERSION 3.17)
project(JJgame)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR C:/SDL2-devel-2.0.12-VC/SDL2-2.0.12/include)
set(SDL2_LIB_DIR C:/SDL2-devel-2.0.12-VC/SDL2-2.0.12/lib/x86)

set(SDL2_TTF_INCLUDE_DIR C:/SDL2_ttf-2.0.15/include)
set(SDL2_TTF_LIB_DIR C:/SDL2_ttf-2.0.15/lib/x86)

include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
)
link_directories(
        ${SDL2_LIB_DIR}
        ${SDL2_TTF_LIB_DIR}
)

add_executable(JJgame main.cpp view.h view.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf)