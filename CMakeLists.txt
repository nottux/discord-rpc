cmake_minimum_required(VERSION 3.22)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(
    discord-rpc
    discord-rpc.cpp
)

target_link_libraries(discord-rpc "${PROJECT_SOURCE_DIR}/lib/libdiscord-rpc.so")

install(
    TARGETS discord-rpc
    RUNTIME
        DESTINATION "bin"
        CONFIGURATIONS Release
    BUNDLE
        DESTINATION "bin"
        CONFIGURATIONS Release
)
