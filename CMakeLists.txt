cmake_minimum_required(VERSION 3.16)

project(GitManager VERSION 0.0.0 LANGUAGES C)

set(EXE_NAME "gitmanager")

add_executable(${EXE_NAME} "")

add_subdirectory(external)
add_subdirectory(src)

# install(TARGETS ${EXE_NAME} DESTINATION bin)