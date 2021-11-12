cmake_minimum_required(VERSION 3.20)
project(Practice_SFML)

set(CMAKE_CXX_STANDARD 14)

set(SFML_ROOT "C:/Users/User/SFML-2.5.1-32")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED system window graphics)

add_executable(Practice_SFML main.cpp)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
