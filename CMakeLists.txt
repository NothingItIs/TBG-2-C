cmake_minimum_required(VERSION 3.16)

get_filename_component(REPO_NAME "${CMAKE_SOURCE_DIR}" NAME)

string(MAKE_C_IDENTIFIER "${REPO_NAME}" PROJECT_NAME_SAFE)

project(${PROJECT_NAME_SAFE} LANGUAGES C CXX)


# ------------------------------------------------------------
# The currently open source file is passed in from tasks.json:
#
#     -DACTIVE_SOURCE=${file}
#
# Example:
#
#     C:/Users/.../TBG-2-C/tests/test.c
# ------------------------------------------------------------

if(NOT DEFINED ACTIVE_SOURCE)
    message(FATAL_ERROR
        "ACTIVE_SOURCE was not supplied. "
        "Run the project through the VS Code task."
    )
endif()


# Convert Windows-style paths to normal CMake-style paths.
file(TO_CMAKE_PATH "${ACTIVE_SOURCE}" ACTIVE_SOURCE)


# Make sure the selected file actually exists.
if(NOT EXISTS "${ACTIVE_SOURCE}")
    message(FATAL_ERROR
        "The selected source file does not exist: ${ACTIVE_SOURCE}"
    )
endif()


# ------------------------------------------------------------
# Get the filename of the active source file.
#
# Example:
#
#     test.c
#
# becomes:
#
#     ACTIVE_OUTPUT_NAME = test
#
# ------------------------------------------------------------

get_filename_component(
    ACTIVE_OUTPUT_NAME
    "${ACTIVE_SOURCE}"
    NAME_WE
)


# CMake target names need to be safe identifiers.
#
# This allows something such as:
#
#     test-file.c
#
# to still output:
#
#     test-file.exe
#
# while internally using a safe CMake target name.
string(
    MAKE_C_IDENTIFIER
    "${ACTIVE_OUTPUT_NAME}"
    TARGET_NAME
)


# ------------------------------------------------------------
# Find all C and C++ source files in the project.
# ------------------------------------------------------------

file(
    GLOB_RECURSE
    ALL_SOURCES
    CONFIGURE_DEPENDS

    "${CMAKE_SOURCE_DIR}/*.c"
    "${CMAKE_SOURCE_DIR}/*.cc"
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.cxx"
)


# ------------------------------------------------------------
# Find all header files as well.
#
# This is mainly so their directories can automatically be added
# to the include search paths.
# ------------------------------------------------------------

file(
    GLOB_RECURSE
    ALL_HEADERS
    CONFIGURE_DEPENDS

    "${CMAKE_SOURCE_DIR}/*.h"
    "${CMAKE_SOURCE_DIR}/*.hh"
    "${CMAKE_SOURCE_DIR}/*.hpp"
    "${CMAKE_SOURCE_DIR}/*.hxx"
)


# ------------------------------------------------------------
# Do not include generated files inside build/ or compiled/.
# ------------------------------------------------------------

list(
    FILTER
    ALL_SOURCES
    EXCLUDE
    REGEX "/build/|/compiled/"
)

list(
    FILTER
    ALL_HEADERS
    EXCLUDE
    REGEX "/build/|/compiled/"
)


# ------------------------------------------------------------
# Start the target with the currently selected .c/.cpp file.
# ------------------------------------------------------------

set(
    TARGET_SOURCES
    "${ACTIVE_SOURCE}"
)


# ------------------------------------------------------------
# Add supporting source files automatically.
#
# Any other source file containing its own main() is NOT added,
# because that would result in multiple main() functions being
# linked into the same executable.
#
# Source files without main() are treated as library/supporting
# implementation files and are linked with the active file.
# ------------------------------------------------------------

foreach(SRC IN LISTS ALL_SOURCES)

    if("${SRC}" STREQUAL "${ACTIVE_SOURCE}")
        continue()
    endif()

    file(
        READ
        "${SRC}"
        SOURCE_CONTENT
    )

    string(
        REGEX MATCH
        "int[ \t\r\n]+main[ \t\r\n]*\\("
        SOURCE_HAS_MAIN
        "${SOURCE_CONTENT}"
    )

    if(NOT SOURCE_HAS_MAIN)
        list(
            APPEND
            TARGET_SOURCES
            "${SRC}"
        )
    endif()

endforeach()


# ------------------------------------------------------------
# Build one executable from:
#
#     currently active source file
#
# plus:
#
#     supporting source files without their own main()
# ------------------------------------------------------------

add_executable(
    ${TARGET_NAME}
    ${TARGET_SOURCES}
)


# ------------------------------------------------------------
# Build include-directory list automatically.
#
# This includes:
#
#     project root
#     every source directory
#     every header directory
#
# so headers can be found regardless of which project subfolder
# they live in.
# ------------------------------------------------------------

set(
    INCLUDE_DIRS
    "${CMAKE_SOURCE_DIR}"
)


foreach(SRC IN LISTS ALL_SOURCES)

    get_filename_component(
        SRC_DIR
        "${SRC}"
        DIRECTORY
    )

    list(
        APPEND
        INCLUDE_DIRS
        "${SRC_DIR}"
    )

endforeach()


foreach(HEADER IN LISTS ALL_HEADERS)

    get_filename_component(
        HEADER_DIR
        "${HEADER}"
        DIRECTORY
    )

    list(
        APPEND
        INCLUDE_DIRS
        "${HEADER_DIR}"
    )

endforeach()


list(
    REMOVE_DUPLICATES
    INCLUDE_DIRS
)


target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    ${INCLUDE_DIRS}
)


# ------------------------------------------------------------
# All final executables go into:
#
#     ./compiled/
#
# The internal CMake build files and object files remain in:
#
#     ./build/
# ------------------------------------------------------------

file(
    MAKE_DIRECTORY
    "${CMAKE_SOURCE_DIR}/compiled"
)


set_target_properties(
    ${TARGET_NAME}
    PROPERTIES

    OUTPUT_NAME
    "${ACTIVE_OUTPUT_NAME}"

    RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/compiled"
)


# ------------------------------------------------------------
# Also force the same output location for multi-configuration
# generators.
# ------------------------------------------------------------

foreach(
    CONFIG
    DEBUG
    RELEASE
    RELWITHDEBINFO
    MINSIZEREL
)

    set_target_properties(
        ${TARGET_NAME}
        PROPERTIES

        "RUNTIME_OUTPUT_DIRECTORY_${CONFIG}"
        "${CMAKE_SOURCE_DIR}/compiled"
    )

endforeach()