
cmake_minimum_required(VERSION 3.31)
project(MMLE)

# version info
set(MMLE_VER_MAJ 0)
set(MMLE_VER_MIN 1)
set(MMLE_VER_REL 0)

include("${PROJECT_SOURCE_DIR}/cmake/options.cmake")

configure_file("config.h.in" "include/${PROJECT_NAME}/config.h")

include_directories(
	# use binary output tree so "config.h" is included
	"${PROJECT_BINARY_DIR}/include"
)

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

if(BUILD_SHARED_LIBS)
	add_library(libMMLE_shared SHARED ${SRC_FILES})
	set_target_properties(
		libMMLE_shared PROPERTIES
		OUTPUT_NAME "MMLE"
		ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
		# .dll on Windows
		RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
	)
	if(NOT DEBUG)
		add_custom_command(
			TARGET libMMLE_shared POST_BUILD
			# strip debugging symbols
			COMMAND ${CMAKE_OBJCOPY} --strip-debug "$<TARGET_FILE:libMMLE_shared>"
		)
		if(MINGW OR CYGWIN)
			# strip shared linking library archive (.dll.a)
			add_custom_command(
				TARGET libMMLE_shared POST_BUILD
				# strip debugging symbols
				COMMAND ${CMAKE_OBJCOPY} --strip-debug "${PROJECT_BINARY_DIR}/lib/libMMLE.dll.a"
			)
		endif()
	endif()
	message("-- Configured to build shared libs")
endif()
if(BUILD_STATIC_LIBS)
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
			COMMAND ${CMAKE_OBJCOPY} --strip-debug "$<TARGET_FILE:libMMLE_static>"
		)
	endif()
	message("-- Configured to build static libs")
endif()

file(COPY "${PROJECT_SOURCE_DIR}/include" DESTINATION "${PROJECT_BINARY_DIR}")

if(BUILD_TESTS)
	file(GLOB TEST_SRC_FILES "${PROJECT_SOURCE_DIR}/tests/*.cpp")
	foreach(TEST_SRC ${TEST_SRC_FILES})
		get_filename_component(TEST_NAME "${TEST_SRC}" NAME_WLE)
		add_executable("${TEST_NAME}" "${TEST_SRC}")
		target_link_libraries("${TEST_NAME}" PRIVATE -L"${PROJECT_BINARY_DIR}/lib" -lMMLE)
		set_target_properties(
			"${TEST_NAME}" PROPERTIES
			OUTPUT_NAME "test_${TEST_NAME}"
			RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
		)
		target_include_directories("${TEST_NAME}" PRIVATE
			"${PROJECT_BINARY_DIR}/include"
		)
		message(DEBUG "-- Configured compilation of test: ${TEST_NAME}")
	endforeach()
	message("-- Configured to build tests")
endif()
