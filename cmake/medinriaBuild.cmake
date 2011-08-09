### medBuild.cmake ---
##
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Tue Apr  6 21:41:29 2010 (+0200)
## Version: $Id$
## Last-Updated: Tue May  3 16:50:17 2011 (+0200)
##           By: Julien Wintz
##     Update #: 2
######################################################################
##
### Commentary:
##
######################################################################
##
### Change log:
##
######################################################################

if (WIN32)
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

## ###################################################################
## INCLUDE RULES
## ###################################################################
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/medCore
    ${PROJECT_SOURCE_DIR}/src/medGui
    ${PROJECT_SOURCE_DIR}/src/medPacs
    ${PROJECT_SOURCE_DIR}/src/medSql
    ${PROJECT_SOURCE_DIR}/src/medGui/commonWidgets
    ${PROJECT_SOURCE_DIR}/src/medGui/factories
    ${PROJECT_SOURCE_DIR}/src/medGui/LUT
    ${PROJECT_SOURCE_DIR}/src/medGui/settingsWidgets
    ${PROJECT_SOURCE_DIR}/src/medGui/toolboxes
    ${PROJECT_SOURCE_DIR}/src/medGui/viewContainers
	${PROJECT_SOURCE_DIR}/src/medGui/database)

include_directories(${${PROJECT_NAME}_INCLUDE_DIRS})

set(${PROJECT_NAME}_INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include/medCore
    ${CMAKE_INSTALL_PREFIX}/include/medGui
    ${CMAKE_INSTALL_PREFIX}/include/medPacs
    ${CMAKE_INSTALL_PREFIX}/include/medSql
    ${CMAKE_INSTALL_PREFIX}/include/medGui/commonWidgets
    ${CMAKE_INSTALL_PREFIX}/include/medGui/factories
    ${CMAKE_INSTALL_PREFIX}/include/medGui/LUT
    ${CMAKE_INSTALL_PREFIX}/include/medGui/settingsWidgets
    ${CMAKE_INSTALL_PREFIX}/include/medGui/toolboxes
    ${CMAKE_INSTALL_PREFIX}/include/medGui/viewContainers
	${CMAKE_INSTALL_PREFIX}/include/medGui/database)


## ###################################################################
## INSTALL RULES
## ###################################################################
if( EXISTS ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake)

install(FILES
  ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
  ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake
  DESTINATION
  cmake)

endif( EXISTS ${${PROJECT_NAME}_BINARY_DIR}/install/${PROJECT_NAME}Config.cmake
   AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Use.cmake
   AND EXISTS ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Uninstall.cmake)
