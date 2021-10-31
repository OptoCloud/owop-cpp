cmake_minimum_required (VERSION 3.9)

project (owopcpp
    VERSION 1.0.0
    DESCRIPTION "C++ library for owop api"
    LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/parallel-hashmap)
add_subdirectory(vendor/websocketpp)
add_subdirectory(vendor/fmt)

set(owopcpp_sources
    src/server.cpp
    src/ipinfo.cpp
    src/connection.cpp
    src/player.cpp
    src/world.cpp
    src/worldmanager.cpp
    src/uuid.cpp
    src/chunksystem.cpp
    src/chunk.cpp
)
set(owopcpp_headers
    include/owopcpp.h
    include/server.h
    include/ipinfo.h
    include/connection.h
    include/player.h
    include/world.h
    include/worldmanager.h
    include/uuid.h
    include/chunksystem.h
    include/chunk.h
    include/serialization.h
    include/pixel.h
    include/opcodes.h
    include/constants.h
    include/tooltype.h
    include/playerrank.h
    include/constexpr_math.h
    include/networking_includes.h
)

if (OWOP_SHARED)
    add_library (owopcpp SHARED
        ${owopcpp_sources}
        ${owopcpp_headers}
    )
else ()
    add_library (owopcpp STATIC
        ${owopcpp_sources}
        ${owopcpp_headers}
    )
endif ()

target_include_directories(owopcpp PRIVATE
    vendor/asio/asio/include
    vendor/parallel-hashmap
    vendor/fmt/include
    vendor/websocketpp
    include
)
target_link_libraries(owopcpp PRIVATE
    pthread
    fmt
)
