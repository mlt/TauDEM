cmake_minimum_required(VERSION 2.8)
project(taudem)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(libshp)
if(LIBSHP_FOUND)
  message("Using system libshp")
else(LIBSHP_FOUND)
  include(ExternalProject)
  if(MSVC)
    set(LIBSHP_MAKEFILE Makefile.vc)
  else()
    if(MINGW)
      # This helps gcc with MS HPC Pack
      add_definitions(-include _mingw.h)
    endif(MINGW)
    set(LIBSHP_MAKEFILE Makefile)
  endif(MSVC)
  ExternalProject_Add(
    shapelib
    INSTALL_COMMAND ""
    URL http://download.osgeo.org/shapelib/shapelib-1.3.0.tar.gz
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND $(MAKE) -f ${LIBSHP_MAKEFILE}

    # CVS_REPOSITORY :pserver:cvsanon@cvs.maptools.org:/cvs/maptools/cvsroot
    # CVS_MODULE shapelib
    # # CMAKE_ARGS -DBUILD_SHARED_LIBS:BOOL=OFF
    )
  include_directories(${CMAKE_BINARY_DIR}/shapelib-prefix/src/shapelib)
  link_directories(${CMAKE_BINARY_DIR}/shapelib-prefix/src/shapelib-build
    ${CMAKE_BINARY_DIR}/shapelib-prefix/src/shapelib)
  if(MSVC)
    set(LIBSHP_LIBRARIES shapelib_i.lib)
  else()
    set(LIBSHP_LIBRARIES -lshp)
    if(NOT LIBSHP_FOUND AND 0)
      # Unless we use static libshp, do not place shared object to /usr/lib/
      set(LIBSHP_LIBRARIES -Wl,-rpath=/usr/lib/taudem ${LIBSHP_LIBRARIES})
      install(FILES
	${CMAKE_BINARY_DIR}/shapelib-prefix/src/shapelib-build/libshp.so.1
	${CMAKE_BINARY_DIR}/shapelib-prefix/src/shapelib-build/libshp.so.1.0.1
	DESTINATION lib/taudem)
    endif()
  endif()
endif(LIBSHP_FOUND)
add_subdirectory(src)
