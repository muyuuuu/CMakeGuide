set(PROJECT_INC_DIR, "${CMAKE_CURRENT_SOURCE_DIR}/inc")
set(PROJECT_PRIV_DIR, "${CMAKE_CURRENT_SOURCE_DIR}/priv")

macro(add_module module)

    set(MODULE_INC "${CMAKE_CURRENT_SOURCE_DIR}/${module}/inc")
    list(APPEND PROJECT_PRIV_DIR ${MODULE_INC})

    set(MODULE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${module}/src")
    aux_source_directory(${MODULE_SRC} MODULE_SRC)

endmacro(add_module)

add_module(calc)
add_module(color)

include_directories(${ALGOS_COMM_INC_DIR})
include_directories(${ALGO_INC_DIR})
include_directories(${ALGO_PRIV_DIR})

# build lib
add_library(mialgo_bokeh_depth STATIC ${NEW_MODULE_SRCS})

target_link_libraries(mialgo_bokeh_depth mialgo_basic)
target_link_libraries(mialgo_bokeh_depth mialgo_utils)