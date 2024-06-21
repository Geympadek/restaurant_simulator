cmake_minimum_required(VERSION 3.7)
project(restaurant_simulator_project)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_RELEASE "/Ox")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DRELEASE ")

file(GLOB restaurant_simulator_SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

link_directories("libraries/lib")
include_directories("libraries/include")

add_executable(restaurant_simulator ${restaurant_simulator_SRC})
target_link_options(restaurant_simulator PRIVATE ${SUBSYSTEM_LINKER_OPTIONS})

target_link_libraries(restaurant_simulator SDL2main)
target_link_libraries(restaurant_simulator SDL2)
target_link_libraries(restaurant_simulator SDL2_image)
target_link_libraries(restaurant_simulator SDL2_mixer)

target_compile_features(restaurant_simulator PRIVATE cxx_std_20)