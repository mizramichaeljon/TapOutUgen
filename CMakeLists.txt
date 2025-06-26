cmake_minimum_required(VERSION 3.10)
project(TapOutUgen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLUGIN_NAME TapOut)

# === REQUIRED: SuperCollider path ===
set(SC_PATH "" CACHE PATH "Path to SuperCollider source")

if(NOT SC_PATH OR NOT EXISTS "${SC_PATH}/include/plugin_interface/SC_PlugIn.hpp")
    message(FATAL_ERROR "
SC_PATH is missing or invalid.

Please set -DSC_PATH=/path/to/supercollider when running CMake.
Make sure this path contains the header: include/plugin_interface/SC_PlugIn.hpp
")
endif()

# === REQUIRED: SharedRingBuffer path ===
set(SHARED_RINGBUFFER_PATH "" CACHE PATH "Path to shared-ringbuffer project")

if(NOT SHARED_RINGBUFFER_PATH OR NOT EXISTS "${SHARED_RINGBUFFER_PATH}/include/SharedRingBufferHeader.hpp")
    message(FATAL_ERROR "
SHARED_RINGBUFFER_PATH is missing or invalid.

Please set -DSHARED_RINGBUFFER_PATH=/path/to/shared-ringbuffer when running CMake.
Make sure this path contains the 'include' directory.
")
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