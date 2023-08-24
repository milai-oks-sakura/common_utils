cmake_minimum_required(VERSION 3.15)

project(CommonUtils VERSION 1.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(USE_PYTHON ON)

enable_language(C CXX)

add_library(${PROJECT_NAME} OBJECT)

if(USE_PYTHON)
  find_package(Python COMPONENTS Interpreter Development)
endif(USE_PYTHON)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} Python::Python)
