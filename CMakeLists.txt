cmake_minimum_required(VERSION 3.26)
project(oms)

########################################################################################
########################################################################################
################################### toolchains #########################################
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set to your preferred compiler
set(CMAKE_C_COMPILER /opt/mio/rel/x86-64-linux/v1/llvm/bin/clang CACHE FILEPATH "C compiler")
set(CMAKE_CXX_COMPILER /opt/mio/rel/x86-64-linux/v1/llvm/bin/clang++ CACHE FILEPATH "C++ compiler")

set(CMAKE_CXX_FLAGS_INIT "-nostdinc++")

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
        "/opt/mio/rel/x86-64-linux/v1/llvm/include/c++/v1"
        "/opt/mio/rel/x86-64-linux/v1/llvm/include/x86_64-unknown-linux-gnu/c++/v1"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -Wl,-rpath,/opt/mio/rel/x86-64-linux/v1/llvm/lib/x86_64-unknown-linux-gnu")

#set(CMAKE_CXX_STANDARD_LIBRARIES "-stdlib=libc++ \"-Wl,-rpath, /opt/mio/rel/x86-64-linux/v1/llvm/lib/x86_64-unknown-linux-gnu\" -fuse-ld=lld")

set(_COMMON_COMPILER_FLAGS "-Werror -Wextra -Wall -Wno-deprecated -Wno-unqualified-std-cast-call")

set(CMAKE_CXX_FLAGS_DEBUG "${_COMMON_COMPILER_FLAGS} -g3 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${_COMMON_COMPILER_FLAGS} -g -mavx -O3 -DNDEBUG")
#######################################################################################
#######################################################################################
#######################################################################################


#######################################################################################
#######################################################################################
################################### packages ##########################################
include(FetchContent)

# Catch
FetchContent_Declare(
        Catch2
        GIT_SHALLOW    TRUE
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.9.0)
FetchContent_MakeAvailable(Catch2)

# For catch 2 only
# list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/contrib)
# For catch 3 only
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

# Nlohmann
set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.2.tar.gz)

FetchContent_GetProperties(nlohmann_json)

if (NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
    add_subdirectory(${nlohmann_json_SOURCE_DIR} ${nlohmann_json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

#######################################################################################
#######################################################################################
#######################################################################################

add_subdirectory(cpp)