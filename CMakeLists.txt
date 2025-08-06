cmake_minimum_required(VERSION 3.14)
project(MySDLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup source
add_executable(MySDLApp src/main.cpp)

# SDL2
find_package(SDL2 REQUIRED)
target_include_directories(MySDLApp PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(MySDLApp PRIVATE ${SDL2_LIBRARIES})

# SDL2_image
if(WIN32)
    find_package(SDL2_image CONFIG REQUIRED)
    target_include_directories(MySDLApp PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(MySDLApp PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
    target_link_libraries(MySDLApp PRIVATE PkgConfig::SDL2_IMAGE)
endif()
