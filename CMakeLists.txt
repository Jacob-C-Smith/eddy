# Need CMake 3.0
cmake_minimum_required (VERSION 3.0)

# This is the name of the repository
project ("eddy")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif ()

# Find the array module
if ( NOT "${HAS_ARRAY}")
    
    # Log
    message("[eddy] Adding array project")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)

    # Let any parent project know that this project has array
    set(HAS_ARRAY true PARENT_SCOPE)
endif()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Log
    message("[eddy] Adding dict project")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    set(HAS_DICT true PARENT_SCOPE)
endif()

# Find the json module
if ( NOT "${HAS_JSON}")

    # Log
    message("[eddy] Adding json project")

    # Add the json directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)

    # Let any parent project know that this project has json
    set(HAS_JSON true PARENT_SCOPE)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[eddy] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Find the crypto module
if ( NOT "${HAS_CRYPTO}")
    
    # Log
    message("[eddy] Adding crypto project")
    
    # Add the crypto directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/crypto ${CMAKE_SOURCE_DIR}/build/crypto)

    # Let any parent project know that this project has crypto
    set(HAS_CRYPTO true PARENT_SCOPE)
endif()

# Find the log module
if ( NOT "${HAS_LOG}")
    
    # Log
    message("[eddy] Adding log project")
    
    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    set(HAS_LOG true PARENT_SCOPE)
endif()

# Find the base64 module
if ( NOT "${HAS_BASE64}")
    
    # Log
    message("[eddy] Adding base64 project")
    
    # Add the base64 directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/base-64 ${CMAKE_SOURCE_DIR}/build/base64)

    # Let any parent project know that this project has base64
    set(HAS_BASE64 true PARENT_SCOPE)
endif()


# Set the eddy module
if ( NOT "${HAS_EDDY}")

    # Log
    message("[eddy] Adding eddy project")

    # Let any parent project know that it has the eddy project
    set(HAS_EDDY true PARENT_SCOPE)
endif()

# Add source to this project's executable.
add_executable (eddy_example "main.c" "eddy.c" "program.c")
add_dependencies(eddy_example json array dict sync log base64)
target_include_directories(eddy_example PUBLIC include include/eddy ${CMAKE_SOURCE_DIR}/extern/log/include/ ${CMAKE_SOURCE_DIR}/extern/json/include/ ${CMAKE_SOURCE_DIR}/extern/array/include/ ${CMAKE_SOURCE_DIR}/extern/dict/include/ ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(eddy_example json array dict sync log base64)
