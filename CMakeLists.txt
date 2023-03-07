cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

add_subdirectory(pico-pio-loader)

project(pico_dshot C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_library(pico_dshot
  src/dshot_encoder.cpp)

target_include_directories(pico_dshot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(pico_dshot PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src )

target_link_libraries(pico_dshot
  pico_stdlib
  hardware_pio
  pico_pio_loader
)

pico_generate_pio_header(pico_dshot ${CMAKE_CURRENT_LIST_DIR}/src/pio/dshot_encoder.pio)
