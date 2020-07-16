
# Load tomlc99
target_sources(${EXE_NAME}
    PRIVATE
        tomlc99/toml.c
)

target_include_directories(${EXE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)