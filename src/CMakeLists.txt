#  This file used for make on the CSDMS system
#
cmake_minimum_required(VERSION 2.6)

set (BUILD_SHARED_LIBS OFF)

#OBJFILES includes classes, structures, and constants common to all files
set (common_srcs commonLib.cpp tiffIO.cpp ReadOutlets.cpp aux_nodata.cpp)

set (D8FILES aread8mn.cpp aread8.cpp ${common_srcs})
set (DINFFILES areadinfmn.cpp areadinf.cpp ${common_srcs})
set (D8 D8FlowDirmn.cpp d8.cpp Node.cpp ${common_srcs})
set (D8EXTREAMUP D8flowpathextremeup.cpp D8FlowPathExtremeUpmn.cpp
     ${common_srcs})
set (D8HDIST D8HDistToStrm.cpp D8HDistToStrmmn.cpp ${common_srcs})
set (DINFAVA DinfAvalanche.cpp DinfAvalanchemn.cpp ${common_srcs})
set (DINFCONCLIM DinfConcLimAccum.cpp DinfConcLimAccummn.cpp
     ${common_srcs})
set (DINFDECAY dinfdecayaccum.cpp DinfDecayAccummn.cpp
     ${common_srcs})
set (DINFDISTDOWN DinfDistDown.cpp DinfDistDownmn.cpp ${common_srcs})
set (DINFDISTUP DinfDistUp.cpp DinfDistUpmn.cpp ${common_srcs})
set (DINF DinfFlowDirmn.cpp dinf.cpp Node.cpp
     ${common_srcs})
set (DINFREVACCUM DinfRevAccum.cpp DinfRevAccummn.cpp ${common_srcs})
set (DINFTRANSLIMACCUM DinfTransLimAccum.cpp DinfTransLimAccummn.cpp
     ${common_srcs})
set (DINFUPDEPEND DinfUpDependence.cpp DinfUpDependencemn.cpp ${common_srcs})
set (DROPANALYSISFILES DropAnalysis.cpp DropAnalysismn.cpp
     ${common_srcs})
set (GAGEWATERSHED gagewatershed.cpp gagewatershedmn.cpp ${common_srcs})
set (GRIDNET gridnetmn.cpp gridnet.cpp
     ${common_srcs})
set (LENGTHAREA LengthArea.cpp LengthAreamn.cpp ${common_srcs})
set (MVOUTLETSTOSTRMFILES MoveOutletsToStrm.cpp MoveOutletsToStrmmn.cpp
     ${common_srcs})
set (PEUKERDOUGLAS PeukerDouglas.cpp PeukerDouglasmn.cpp ${common_srcs})
set (PITREMOVE flood.cpp PitRemovemn.cpp ${common_srcs})
set (SLOPEAREA SlopeArea.cpp SlopeAreamn.cpp ${common_srcs})
set (SLOPEAREARATIO SlopeAreaRatio.cpp SlopeAreaRatiomn.cpp ${common_srcs})
set (SLOPEAVEDOWN SlopeAveDown.cpp SlopeAveDownmn.cpp ${common_srcs})
set (STREAMNET streamnetmn.cpp streamnet.cpp
     ${common_srcs})
set (THRESHOLD Threshold.cpp Thresholdmn.cpp ${common_srcs})
#set (READTIFFILES ReadTif.cpp ReadTifmn.cpp ${common_srcs})


add_executable (aread8 ${D8FILES})
add_executable (areadinf ${DINFFILES})
add_executable (d8flowdir ${D8})
add_executable (d8flowpathextremeup ${D8EXTREAMUP})
add_executable (d8hdisttostrm ${D8HDIST})
add_executable (dinfavalanche ${DINFAVA})
add_executable (dinfconclimaccum ${DINFCONCLIM})
add_executable (dinfdecayaccum ${DINFDECAY})
add_executable (dinfdistdown ${DINFDISTDOWN})
add_executable (dinfdistup ${DINFDISTUP})
add_executable (dinfflowdir ${DINF})
add_executable (dinfrevaccum ${DINFREVACCUM})
add_executable (dinftranslimaccum ${DINFTRANSLIMACCUM})
add_executable (dinfupdependence ${DINFUPDEPEND})
add_executable (dropanalysis ${DROPANALYSISFILES})
add_executable (gagewatershed ${GAGEWATERSHED})
add_executable (gridnet ${GRIDNET})
add_executable (lengtharea ${LENGTHAREA})
add_executable (moveoutletstostrm ${MVOUTLETSTOSTRMFILES})
add_executable (peukerdouglas ${PEUKERDOUGLAS})
add_executable (pitremove ${PITREMOVE})
add_executable (slopearea ${SLOPEAREA})
add_executable (slopearearatio ${SLOPEAREARATIO})
add_executable (slopeavedown ${SLOPEAVEDOWN})
add_executable (streamnet ${STREAMNET})
add_executable (threshold ${THRESHOLD})
#add_executable (ReadTif ${READTIFFILES})
#add_executable (compare ${OBJFILES} compare.cpp)
#add_executable (extract ${OBJFILES} extract.cpp)

find_package(MPI REQUIRED)
if(NOT ${MPI_CXX_COMPILER})	# no mpicxx on win32
  include_directories(${MPI_CXX_INCLUDE_PATH})
  target_link_libraries(aread8 ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (areadinf ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (d8flowdir ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (d8flowpathextremeup ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (d8hdisttostrm ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfavalanche ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfconclimaccum ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfdecayaccum ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfdistdown ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfdistup ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfflowdir ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfrevaccum ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinftranslimaccum ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dinfupdependence ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (dropanalysis ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (gagewatershed ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (gridnet ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (lengtharea ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (moveoutletstostrm ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (peukerdouglas ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (pitremove ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (slopearea ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (slopearearatio ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (slopeavedown ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (streamnet ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
  target_link_libraries (threshold ${MPI_CXX_LIBRARIES} ${LIBSHP_LIBRARIES})
endif(NOT ${MPI_CXX_COMPILER})

install(TARGETS aread8 
                areadinf
                d8flowdir
                d8flowpathextremeup
                d8hdisttostrm
                dinfavalanche
                dinfconclimaccum
                dinfdecayaccum
                dinfdistdown
                dinfdistup
                dinfflowdir
                dinfrevaccum
                dinftranslimaccum
                dinfupdependence
                dropanalysis
                gagewatershed
                gridnet
                lengtharea
                moveoutletstostrm
                peukerdouglas
                pitremove
                slopearea
                slopearearatio
                slopeavedown
                streamnet
                threshold
        DESTINATION bin)

