cmake_minimum_required(VERSION 2.9)

project(MinecraftCircleTool)

set(VERSION_MAJOR 1 CACHE STRING "")
set(VERSION_MINOR 0 CACHE STRING "")
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/release/Minecraft Perfect Circle Tool ${PROJECT_VERSION}")

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CMAKE_INSTALL_PREFIX})
include (InstallRequiredSystemLibraries)

set(SOURCE_FILES
	Circle.cpp
)

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