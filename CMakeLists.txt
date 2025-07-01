cmake_minimum_required(VERSION 3.10)
project(TapOutUgen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PLUGIN_NAME TapOut)

# === SuperCollider path ===
set(SC_PATH "" CACHE PATH "Path to SuperCollider source")

if(NOT SC_PATH OR NOT EXISTS "${SC_PATH}/include/plugin_interface/SC_PlugIn.hpp")
    message(FATAL_ERROR "
SC_PATH is missing or invalid.

Please set -DSC_PATH=/path/to/supercollider when running CMake.
Make sure this path contains the header: include/plugin_interface/SC_PlugIn.hpp
")
endif()

# === SharedRingBuffer path ===
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
)

# === macOS-specific include/lib (optional Homebrew paths) ===
if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

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

# === Optional Boost linking (only if you use non-header parts) ===
# find_package(Boost REQUIRED COMPONENTS system thread)
# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIRS})
#     target_link_libraries(${PLUGIN_NAME} ${Boost_LIBRARIES})
# endif()

# === Optional: Install plugin into SC build tree ===
# set(SC_PLUGIN_INSTALL_DIR "${SC_PATH}/install/share/SuperCollider/Extensions")
# install(TARGETS ${PLUGIN_NAME} DESTINATION ${SC_PLUGIN_INSTALL_DIR})
