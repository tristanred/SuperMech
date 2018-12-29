#
# Super Mech Tools
#

cmake_minimum_required(VERSION 3.9)
project(SuperMechs-Tools)

set(ARCH x64)
set(CMAKE_CXX_STANDARD 11)

#
# Setup common properties
#
IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

include_directories("../game/include")
include_directories("../game/lib/MicroEngine/engine/include")
include_directories("../game/lib/MicroEngine/engine/lib/libtech/include")

##### CSV Stats Converter
file(GLOB_RECURSE CSVSTATS_SRC "CSVStatsConverter/*.cpp")
file(GLOB_RECURSE CSVSTATS_HEADERS "CSVStatsConverter/*.h")

add_executable(CSVStats ${CSVSTATS_HEADERS} ${CSVSTATS_SRC})
target_link_libraries(CSVStats LIBTECH)
target_link_libraries(CSVStats MICROENGINE)

IF(WIN32)
set_target_properties(CSVStats PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
ELSEIF(UNIX)
target_compile_options(CSVStats PRIVATE -Wall)
ENDIF(WIN32)
##### CSV Stats Converter