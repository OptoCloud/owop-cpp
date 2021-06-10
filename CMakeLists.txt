cmake_minimum_required (VERSION 3.9)

project (owopcpp
    VERSION 1.0.0
    DESCRIPTION "C++ library for owop api"
    LANGUAGES CXX
)

set (CMAKE_CXX_STANDARD 20)

set(owopcpp_sources
    src/client.cpp
    src/player.cpp
    src/world.cpp
    src/chat.cpp
    src/networking.cpp
    src/clientoptions.cpp
    src/chunksystem.cpp
    src/chunk.cpp
    src/color.cpp
    src/bucket.cpp
)
set(owopcpp_headers
    include/owopcpp.h
    include/client.h
    include/player.h
    include/world
    include/chat.h
    include/networking.h
    include/clientoptions.h
    include/chunksystem.h
    include/chunk.h
    include/color.h
    include/bucket.h
    include/opcodes.h
    include/captchastate.h
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

target_include_directories(owopcpp PRIVATE include)
