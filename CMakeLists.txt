# Need CMake 3.28.0
cmake_minimum_required (VERSION 3.28.0)

# The name of the repository
project ("eddy")

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set the output paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Build sync with semaphore
add_compile_definitions(BUILD_SYNC_WITH_SEMAPHORE)

# Build sync with monitor
add_compile_definitions(BUILD_SYNC_WITH_MONITOR)

# Find the log module
if ( NOT "${HAS_LOG}")
    
    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")
    
    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the stack module
if ( NOT "${HAS_STACK}")
    
    # Add the stack directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/stack ${CMAKE_SOURCE_DIR}/build/stack)

    # Let any parent project know that this project has stack
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_STACK true PARENT_SCOPE)
        set(STACK_INCLUDE_DIR ${STACK_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the base64 module
if ( NOT "${HAS_BASE64}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/base64 ${CMAKE_SOURCE_DIR}/build/base64)

    # Let any parent project know that this project has base64
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_BASE64 true PARENT_SCOPE)
        set(BASE64_INCLUDE_DIR ${JSON_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the json module
if ( NOT "${HAS_JSON}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)

    # Let any parent project know that this project has json
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_JSON true PARENT_SCOPE)
        set(JSON_INCLUDE_DIR ${JSON_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the array module
if ( NOT "${HAS_ARRAY}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)

    # Let any parent project know that this project has array
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_ARRAY true PARENT_SCOPE)
        set(ARRAY_INCLUDE_DIR ${ARRAY_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_DICT true PARENT_SCOPE)
        set(DICT_INCLUDE_DIR ${DICT_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add the eddy project
if ( NOT "${HAS_EDDY}")

    set (EDDY_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the log project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_EDDY true PARENT_SCOPE)
        set(EDDY_INCLUDE_DIR ${EDDY_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif ()

# Add source to this project's executable.
add_executable (eddy_example "main.c")
add_dependencies(eddy_example eddy base64 stack log crypto json array dict sync)
target_include_directories(eddy_example PUBLIC ${EDDY_INCLUDE_DIR} ${BASE64_INCLUDE_DIR} ${STACK_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR} ${CRYPTO_INCLUDE_DIR})
target_link_libraries(eddy_example eddy base64 stack log crypto eddy json array dict sync)

## Add source to the tester
#add_executable (eddy_test "eddy_test.c")
#add_dependencies(eddy_test array dict sync)
#target_include_directories(eddy_test PUBLIC include include/eddy  ${CMAKE_SOURCE_DIR}/extern/eddy/include ${CMAKE_SOURCE_DIR}/extern/array/include/ ${CMAKE_SOURCE_DIR}/extern/dict/include/ ${CMAKE_SOURCE_DIR}/extern/sync/include/)
#target_link_libraries(eddy_test eddy json array dict sync)

# Add source to this project's library
add_library (eddy SHARED "eddy.c" "program.c")
add_dependencies(eddy base64 stack log crypto json array dict sync)
target_include_directories(eddy PUBLIC ${EDDY_INCLUDE_DIR} ${BASE64_INCLUDE_DIR} ${STACK_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR} ${CRYPTO_INCLUDE_DIR})
target_link_libraries(eddy PRIVATE base64 stack log crypto json array dict sync)
