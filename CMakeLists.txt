cmake_minimum_required(VERSION 2.9)

project(MinecraftCircleTool)

set(VERSION_MAJOR 1 CACHE STRING "")
set(VERSION_MINOR 1 CACHE STRING "")
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/release/Minecraft Perfect Circle Tool ${PROJECT_VERSION}")

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_PREFIX})
include (InstallRequiredSystemLibraries)

set(SOURCE_FILES
	src/main.cpp
	src/CircleCalculator.h
	src/CircleCalculator.cpp
)

#sort files into a singel folder for visual studio
foreach(source IN LISTS SOURCE_FILES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "/" "\\" source_path_msvc "${source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
endforeach()

add_executable("MinecraftCircleTool" ${SOURCE_FILES})

set(OTHER_INSTALL_FILES
	HowToUse.txt
)
set(OTHER_INSTALL_FOLDER
	redist
)

#install executable
install (TARGETS MinecraftCircleTool
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)

#Install source
install(FILES ${SOURCE_FILES} DESTINATION src)

#install readme and other files
install(FILES ${OTHER_INSTALL_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${OTHER_INSTALL_FOLDER} DESTINATION ${CMAKE_INSTALL_PREFIX})