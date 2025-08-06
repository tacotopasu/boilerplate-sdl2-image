cmake_minimum_required(VERSION 3.14)
project(Scalpel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup source directory
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(Scalpel ${SRC_FILES})

# Add include directory
target_include_directories(Scalpel PRIVATE ${PROJECT_SOURCE_DIR}/src/include)

# SDL2
find_package(SDL2 REQUIRED)
target_include_directories(Scalpel PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Scalpel PRIVATE ${SDL2_LIBRARIES})

# SDL2_image
if(WIN32)
    find_package(SDL2_image CONFIG REQUIRED)
    target_include_directories(Scalpel PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(Scalpel PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
    target_link_libraries(Scalpel PRIVATE PkgConfig::SDL2_IMAGE)
endif()
