cmake_minimum_required(VERSION 3.26)
project(The-Compilers)

set(CMAKE_CXX_STANDARD 17)

# Define source files with relative paths
set(SOURCES
        src/main.cpp
        src/Trie.cpp
        src/TST.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)


# Use target-specific includes (more modern)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)