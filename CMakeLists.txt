cmake_minimum_required( VERSION 3.30.3 )

set( library_name Link-OpenSSL )

project( ${library_name} CXX )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( OpenSSL_location "C:/Program Files/OpenSSL" )

# Enable static linkage of runtime on MSVC
if( MSVC )
  set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" )
endif()

# Hide the console window in visual studio projects
if( MSVC )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
	set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()

file( GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.qrc )

if( CMAKE_SYSTEM_NAME STREQUAL "Windows" )
	add_executable( ${library_name} WIN32 ${SRC_FILES} )
elseif( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
	add_executable( ${library_name} ${SRC_FILES} )
elseif( CMAKE_SYSTEM_NAME STREQUAL "Darwin" )
	add_executable( ${library_name} ${SRC_FILES} )
endif()

# Set the correct Visual Studio startup project.
if ( MSVC )
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${library_name} )
endif()

# Link against the Qt libraries, and add required include directories and compile definitions.
target_link_libraries( ${library_name} PRIVATE ${OpenSSL_location}/lib/libcrypto_static.lib ${OpenSSL_location}/lib/libssl_static.lib crypt32.lib ws2_32.lib )

# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${OpenSSL_location}/include )
