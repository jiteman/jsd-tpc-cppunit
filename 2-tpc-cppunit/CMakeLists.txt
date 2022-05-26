cmake_minimum_required( VERSION 3.16.3 )

project( jsd-tpc-cppunit C CXX )


JSD_SHOW_PROJECT_HEADER()


include( ${JSD_SSC_CMAKE_PATH}/tpc-cppunit-library-set-compiler-settings.cmake )
set( JSD_THIS_PROJECT_HEADER_PATH ${JSD_SSC_SOURCE_PATH}/libreoffice-cppunit/include )
set( JSD_THIS_PROJECT_SOURCE_PATH ${JSD_SSC_SOURCE_PATH}/libreoffice-cppunit/src )
set( JSD_THIS_PROJECT_ADHOCS_PATH ${JSD_SSC_SOURCE_PATH}/jsd_adhocs )

set( ${PROJECT_NAME}_TEST_SOURCE_DIRS_VAR ${JSD_SSC_SOURCE_PATH}/libreoffice-cppunit/examples/cppunittest )

## include dependencies
set( ${PROJECT_NAME}_DEPENDENCY_DIRS_VAR
	${JSD_PLATFORM_SOURCES}
	${JSD_THIS_PROJECT_HEADER_PATH} )

set( JSD_THIS_PROJECT_ADHOCS_DIRS ${JSD_THIS_PROJECT_ADHOCS_PATH}/common )

if( UNIX )
	list( APPEND JSD_THIS_PROJECT_ADHOCS_DIRS ${JSD_THIS_PROJECT_ADHOCS_PATH}/linux )
elseif ( WIN32 )
	list( APPEND JSD_THIS_PROJECT_ADHOCS_DIRS ${JSD_THIS_PROJECT_ADHOCS_PATH}/windows )
endif()

#include_directories( ${JSD_THIS_PROJECT_ADHOCS_DIRS} )
## or
list( APPEND ${PROJECT_NAME}_DEPENDENCY_DIRS_VAR ${JSD_THIS_PROJECT_ADHOCS_DIRS} )

list( REMOVE_DUPLICATES ${PROJECT_NAME}_DEPENDENCY_DIRS_VAR )
include_directories( ${${PROJECT_NAME}_DEPENDENCY_DIRS_VAR} )


## this project headers and sources enumeration section
file( GLOB_RECURSE header_and_source_files
	${JSD_THIS_PROJECT_HEADER_PATH}/cppunit/*.h*
	${JSD_THIS_PROJECT_HEADER_PATH}/cppunit/*.c*
	${JSD_THIS_PROJECT_SOURCE_PATH}/cppunit/*.h*
	${JSD_THIS_PROJECT_SOURCE_PATH}/cppunit/*.c* )

set( JSD_THIS_PROJECT_FILES_TO_REMOVE
	"DllMain" )

JSD_REMOVE_FILES_FROM_THE_LIST( header_and_source_files JSD_THIS_PROJECT_FILES_TO_REMOVE )

add_library( ${PROJECT_NAME} SHARED ${header_and_source_files} )


## definition section
set( ${PROJECT_NAME}_BUILD_DEFINITIONS_VAR
	-DCPPUNIT_BUILD_DLL )
JSD_LIST_TO_STRING( ${PROJECT_NAME}_BUILD_DEFINITIONS_VAR )
JSD_STRING_REMOVE_DUPLICATES( ${PROJECT_NAME}_BUILD_DEFINITIONS_VAR )
set( ${PROJECT_NAME}_LINK_DEFINITIONS_VAR
	-DCPPUNIT_DLL )
JSD_LIST_TO_STRING( ${PROJECT_NAME}_LINK_DEFINITIONS_VAR )
JSD_STRING_REMOVE_DUPLICATES( ${PROJECT_NAME}_LINK_DEFINITIONS_VAR )
add_definitions( "${${PROJECT_NAME}_BUILD_DEFINITIONS_VAR}" )


## required to be able to be linked into shared libraries.
set_target_properties( ${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON )
set_target_properties( ${PROJECT_NAME} PROPERTIES VERSION 0.1.0 )
set_target_properties( ${PROJECT_NAME} PROPERTIES SOVERSION 0.1 )


## project target section
if( WIN32 )
	set( ${PROJECT_NAME}_DEPENDENCY_LIBS_VAR
		"" )
elseif( UNIX )
	set( ${PROJECT_NAME}_DEPENDENCY_LIBS_VAR
		"dl" )
endif()

list( REMOVE_DUPLICATES ${PROJECT_NAME}_DEPENDENCY_LIBS_VAR )
target_link_libraries( ${PROJECT_NAME} ${${PROJECT_NAME}_DEPENDENCY_LIBS_VAR} )


## Expose public includes to other subprojects through cache variable.
include( ${JSD_CMAKE_PATH}/set-expose-dependencies.cmake )
include( ${JSD_CMAKE_PATH}/set-expose-test-source-directories.cmake )
JSD_SHOW_PROJECT_FOOTER()
