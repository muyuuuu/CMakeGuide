# algos test
set(NEW_ALGO_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algo/inc")
set(NEW_ALGO_INC_DIR_PRIV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algo/priv")

list(APPEND ALGO_INC_DIR ${NEW_ALGO_INC_DIR})
list(APPEND ALGO_PRIV_DIR ${NEW_ALGO_INC_DIR_PRIV_DIR})

if(WITH_OPENCL)
    set(NEW_ALGO_INC_DIR_PRIV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/algo/priv/opencl")
    list(APPEND ALGO_PRIV_DIR ${NEW_ALGO_INC_DIR_PRIV_DIR})
endif()

get_property(ALGO_TEST_SRCS GLOBAL PROPERTY "algo_test_srcs")
list(APPEND ALL_ALGO_TEST_SRCS ${ALGO_TEST_SRCS})

get_property(PRIV_DIR GLOBAL PROPERTY "algo_priv_dir")
list(APPEND ALGO_PRIV_DIR ${PRIV_DIR})

list(APPEND RUNTIME_HOST_SRC_DIR ${ALGO_TEST_SRCS})

list(APPEND ALGO_LIBS mialgo_bokeh_depth)
list(APPEND ALGO_LIBS mialgo_basic)
list(APPEND ALGO_LIBS mialgo_utils)
if(HOST_WITH_MVPU)
    list(APPEND ALGO_LIBS mage_mvpu_runtime)
    if(ANDROID)
        list(APPEND ALGO_LIBS mvpu_runtime_shim)
    endif()
endif()

get_property(RUNTIME_HOST_DIR GLOBAL PROPERTY "RUNTIME_HOST_DIR")
set(RUNTIME_HOST_INC_DIR "${RUNTIME_HOST_DIR}/priv")
set(RUNTIME_HOST_SRC_DIR "${RUNTIME_HOST_DIR}/src")

get_property(ALGO_HEXAGON_INC_DIR GLOBAL PROPERTY "ALGO_HEXAGON_INC_DIR")

# add inc dir
set(UNIT_TEST_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/inc")

if(WITH_OPENCL)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/test/tools/" NEW_MODULE_CL_TEST_SRCS)
endif()

include_directories(${ALGO_INC_DIR})
include_directories(${ALGO_PRIV_DIR})
include_directories(${RUNTIME_HOST_INC_DIR})
include_directories(${UNIT_TEST_INC_DIR})
include_directories(${ALGO_HEXAGON_INC_DIR})

aux_source_directory(${RUNTIME_HOST_SRC_DIR} ALL_ALGO_TEST_SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/test/src/comm" ALL_ALGO_TEST_SRCS)

# build unit test
if(WITH_UNIT_TEST)

    if(WITH_OPENCL)
        add_executable(algos_cl_string ${NEW_MODULE_CL_TEST_SRCS} ${ALL_ALGO_TEST_SRCS})
        target_link_libraries(algos_cl_string ${ALGO_LIBS} ${OpenCV_LIBS})
        install(TARGETS algos_cl_string DESTINATION test)
    endif()

    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/test/src/main" ALL_ALGO_TEST_SRCS)
    add_executable(algos_test ${ALL_ALGO_TEST_SRCS})
    target_link_libraries(algos_test ${ALGO_LIBS} ${OpenCV_LIBS})

    install(TARGETS algos_test DESTINATION test)
endif()

# install sample
install(DIRECTORY sample/ DESTINATION samples)
