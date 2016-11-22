cmake_minimum_required(VERSION 2.8)
project (crconv C)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories (${CJSON_INCLUDE_DIR})

IF(DEFINED CRCONV_VERSION)
set_source_files_properties(version.c PROPERTIES
COMPILE_DEFINITIONS CRCONV_VERSION="${CRCONV_VERSION}")
ENDIF()

IF (CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=unused-but-set-variable")
ENDIF()
IF (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wsign-compare -Wall -Werror -Wno-unknown-pragmas -Wstrict-prototypes -Wpointer-arith -Wno-char-subscripts -Wno-long-long")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    add_definitions(-DHAVE__BOOL)
ELSEIF(MSVC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall /WX /MP")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrt.lib")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib")
ELSE()
    MESSAGE(STATUS "unknown compiler ${CMAKE_C_COMPILER_ID}")
ENDIF()

IF(CMAKE_COMPILER_IS_CLANG)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wtautological-compare -Weverything")
    MESSAGE(STATUS "compiler is clang: ${CMAKE_C_COMPILER_ID}")
ELSEIF(CMAKE_COMPILER_IS_GCC)
    EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -dumpversion
        OUTPUT_VARIABLE GCC_VERSION)
    IF (GCC_VERSION VERSION_GREATER 4.9)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfloat-conversion")
    ENDIF()
ENDIF(CMAKE_COMPILER_IS_CLANG)

set (CRCONV_SRC
  main.c
  crconv.c
)

add_library(version STATIC version.c)
add_executable(crconv ${CRCONV_SRC})
target_link_libraries(crconv
  version
  ${CJSON_LIBRARIES}
)

install(TARGETS crconv DESTINATION "bin")
