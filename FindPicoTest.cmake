set(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_DIR}")

add_library(PicoTest INTERFACE)
set_target_properties(PicoTest PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
)

include("${_IMPORT_PREFIX}/PicoTest.cmake")
