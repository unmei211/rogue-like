cmake_minimum_required(VERSION 3.25)
project(ECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wno-unused-parameter -fPIC -march=native")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

# find lib
# include
# link

find_package(BearLibTerminal REQUIRED)
include_directories(SYSTEM ${BLT_INCLUDE_DIRS})

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES}
        include/rogue/tools/data/field_food_data.h
        include/rogue/tools/EntityMapsHandler.h
        include/rogue/tools/map-random/floor.h
        include/rogue/tools/map-random/map_generator.h
        include/rogue/tools/map-random/floor_filler.h
        include/rogue/tools/map-random/tunnel.h
        include/rogue/tools/map-random/tunnel_filler.h
        src/rogue/math/Rand.cpp
        include/rogue/math/Rand.h
        include/rogue/tools/map-random/gen_fun.h
        include/rogue/tools/map-random/map_bypass.h
        include/rogue/tools/graphics_changer.h
        include/rogue/tools/config/graphics_associate.h
        src/rogue/systems/floor_traps_system.cpp
        include/rogue/systems/floor_traps_system.h
        include/rogue/components/tags/trap_component.h
        include/rogue/components/attributes/traps_slot_component.h
        src/rogue/systems/take_trap_system.cpp
        include/rogue/systems/take_trap_system.h
        include/rogue/components/indicators/floor_counter_component.h
)

include_directories(${PROJECT_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARIES})
file(COPY ${BLT_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add linting before compilation
include(CppLint)
ADD_STYLE_CHECK_TARGET(lint ${PROJECT_NAME} ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})
add_dependencies(${PROJECT_NAME} lint)
