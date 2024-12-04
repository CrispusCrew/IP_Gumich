# cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B build
# cmake --build build
# cmake --install build

set(CMAKE_BUILD_TYPE Release)

project(fifo_ring)

cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0074 NEW)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON) 

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(FFRG_DIR ${PROJECT_SOURCE_DIR}/fifo_ring)

set(SOURCES
    ${SRC_DIR}/sample.c
    ${FFRG_DIR}/fifo_ring.c 
)

add_executable(sampleFFRG ${SOURCES})

target_include_directories(sampleFFRG PRIVATE ${FFRG_DIR})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install(TARGETS sampleFFRG RUNTIME DESTINATION bin)

