set(COMMON_INC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${COMMON_INC})
message(STATUS " =========== common include file: ${COMMON_INC}")

set(COMMON_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${COMMON_LIB})
message(STATUS " =========== common include lib: ${COMMON_LIB}")
