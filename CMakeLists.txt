cmake_minimum_required( VERSION 3.16.3 )

project( tpc-cppunit ) # separate source component


JSD_SHOW_PROJECT_GROUP_HEADER()


set( JSD_SSC_CMAKE_PATH ${PROJECT_SOURCE_DIR}/0-tpc-cmake )
set( JSD_SSC_SOURCE_PATH ${PROJECT_SOURCE_DIR}/1-tpc-repository )


add_subdirectory( 2-tpc-cppunit )


JSD_SHOW_PROJECT_GROUP_FOOTER()
