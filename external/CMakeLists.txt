
# Load tomlc99
# Should be temporary until https://github.com/cktan/tomlc99/pull/37 is merged

target_sources(${EXE_NAME}
    PRIVATE
        tomlc99/toml.c
)

target_include_directories(${EXE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)