
cmake_minimum_required(VERSION 3.31)
project(MMLE)

# version info
set(MMLE_VER_MAJ 0)
set(MMLE_VER_MIN 1)
set(MMLE_VER_REL 0)

include("${PROJECT_SOURCE_DIR}/cmake/options.cmake")

configure_file("config.h.in" "include/${PROJECT_NAME}/config.h")

include_directories(
	"include"
	# add the binary tree to the search path to include "config.h"
	"${PROJECT_BINARY_DIR}"
)

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

if(BUILD_SHARED_LIBS)
	message("-- Configuring to build shared libs")
	add_library(libMMLE_shared SHARED ${SRC_FILES})
	set_target_properties(
		libMMLE_shared PROPERTIES
		OUTPUT_NAME "MMLE"
		ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
		# .dll on Windows
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
	)
	if(NOT DEBUG)
		add_custom_command(
			TARGET libMMLE_shared POST_BUILD
			# strip debugging symbols
			COMMAND ${CMAKE_OBJCOPY} --strip-all "$<TARGET_FILE:libMMLE_shared>"
		)
		if(MINGW OR CYGWIN)
			# shared linking library (.dll.a) doesn't get stripped by default under GNU C for Windows
			add_custom_command(
				TARGET libMMLE_shared POST_BUILD
				COMMAND ${CMAKE_OBJCOPY} --strip-all "$<TARGET_FILE:libMMLE_shared>.a"
			)
		endif()
	endif()
endif()
if(BUILD_STATIC_LIBS)
	message("-- Configuring to build static libs")
	add_library(libMMLE_static STATIC ${SRC_FILES})
	set_target_properties(
		libMMLE_static PROPERTIES
		OUTPUT_NAME "MMLE"
		ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
	)
	if(NOT DEBUG)
		add_custom_command(
			TARGET libMMLE_static POST_BUILD
			# strip debugging symbols
			COMMAND ${CMAKE_OBJCOPY} --strip-all "$<TARGET_FILE:libMMLE_static>"
		)
	endif()
endif()

file(COPY "${PROJECT_SOURCE_DIR}/include" DESTINATION "${PROJECT_BINARY_DIR}")
