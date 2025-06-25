cmake_minimum_required(VERSION 3.10)
project(TapOutUgen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLUGIN_NAME TapOut)

# === REQUIRED: SuperCollider path ===
option(SC_PATH "Path to SuperCollider source" "")
if(NOT SC_PATH)
    message(STATUS "Usage: cmake .. -DSC_PATH=/path/to/supercollider -DSHARED_RINGBUFFER_PATH=/path/to/shared-ringbuffer")
    message(FATAL_ERROR "You must set -DSC_PATH to the root of the SuperCollider source.")
endif()

# === REQUIRED: SharedRingBuffer path ===
option(SHARED_RINGBUFFER_PATH "Path to SharedRingBuffer project" "")
if(NOT SHARED_RINGBUFFER_PATH)
    message(STATUS "Usage: cmake .. -DSC_PATH=/path/to/supercollider -DSHARED_RINGBUFFER_PATH=/path/to/shared-ringbuffer")
    message(FATAL_ERROR "You must set -DSHARED_RINGBUFFER_PATH to the root of shared-ringbuffer project.")
endif()

# === Include paths ===
include_directories(
    ${SC_PATH}/include/plugin_interface
    ${SC_PATH}/include/common
    ${SHARED_RINGBUFFER_PATH}/include
    /opt/homebrew/include
)

# === Link paths ===
link_directories(
    /opt/homebrew/lib
)

# === Plugin source ===
set(SOURCES
    TapOut.cpp
)

add_library(${PLUGIN_NAME} MODULE ${SOURCES})

set_target_properties(${PLUGIN_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins
    PREFIX ""
    SUFFIX ".scx"
)

# === Link with Boost if needed (no linking needed for header-only use) ===
# target_link_libraries(${PLUGIN_NAME} boost_system boost_thread) 
# Uncomment if you start using parts of Boost that require linking