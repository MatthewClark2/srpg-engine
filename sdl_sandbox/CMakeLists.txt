# Loading SDL.
find_package(SDL2 COMPONENTS graphics window REQUIRED)

# Maybe add header files, though that shouldn't be needed.
include_directories(${SDL2_INCLUDE_DIRECTORIES})
add_executable(sdlmain main.cpp)
target_link_libraries(sdlmain ${SDL2_LIBRARY})