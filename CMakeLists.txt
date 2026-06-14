cmake_minimum_required(VERSION 3.28)

project(Mirelight LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TITAN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../titan_real/Titan" CACHE PATH "Path to Titan")

if (EXISTS "${TITAN_PATH}/CMakeLists.txt")
    add_subdirectory(${TITAN_PATH} ${CMAKE_BINARY_DIR}/titan-build)
else()
    include(FetchContent)
    FetchContent_Declare(Titan
        GIT_REPOSITORY https://github.com/HannesW101/Titan
        GIT_TAG        v1.0.1)
    FetchContent_MakeAvailable(Titan)
endif()

# ----------------------------------------------------------------------------
# Game sources (core / world / entities / scenes).
# ----------------------------------------------------------------------------
file(GLOB_RECURSE MIRELIGHT_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(Mirelight ${MIRELIGHT_SOURCES})

target_include_directories(Mirelight PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Titan re-exports nlohmann_json transitively; link it for the tile database.
target_link_libraries(Mirelight PRIVATE Titan::Titan nlohmann_json::nlohmann_json)

# Copy assets and data next to the binary so it finds them at runtime.
add_custom_command(TARGET Mirelight POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Mirelight>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:Mirelight>/data)
