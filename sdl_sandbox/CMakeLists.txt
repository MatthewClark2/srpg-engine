# Loading SDL.
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Maybe add header files, though that shouldn't be needed.
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(sdlmain main.cpp exercise1.cpp exercise2.cpp exercise3.cpp exercise4.cpp setup.cpp exercise5.cpp exercise7.cpp exercise8.cpp exercise9.cpp exercise10.cpp exercise11.cpp exercise12.cpp exercise13.cpp)
target_link_libraries(sdlmain ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})