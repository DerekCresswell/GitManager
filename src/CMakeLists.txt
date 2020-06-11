
target_sources(${EXE_NAME}
    PRIVATE
        main.c
        Logger.c
)

target_include_directories(${EXE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(Commands)
add_subdirectory(Profile)