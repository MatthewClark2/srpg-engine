project(fire_engine)

add_executable(fire_engine_test unit_test.cpp)
target_link_libraries(fire_engine_test fire_engine ${Boost_LIBRARIES})
