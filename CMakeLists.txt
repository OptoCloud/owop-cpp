cmake_minimum_required (VERSION 3.9)

project (owopcpp
    VERSION 1.0.0
    DESCRIPTION "C++ library for owop api"
    LANGUAGES CXX
)

set (CMAKE_CXX_FLAGS -DCOMPILE_GOAPI)
set (CMAKE_CXX_STANDARD 20)

set(owopcpp_sources
    src/goapi.cpp
    src/player.cpp
    src/world.cpp
    src/worldmanager.cpp
    src/uuid.cpp
    src/chunksystem.cpp
    src/chunk.cpp
)
set(owopcpp_headers
    include/goapi.h
    include/godef.h
    include/owopcpp.h
    include/player.h
    include/world.h
    include/worldmanager.h
    include/uuid.h
    include/chunksystem.h
    include/chunk.h
    include/pixel.h
    include/opcodes.h
    include/constants.h
    include/tooltype.h
    include/playerrank.h
    include/constexpr_math.h
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
    vendor/parallel-hashmap/parallel_hashmap
    include
)
