cmake_minimum_required (VERSION 3.1)
project(ERDatabaseSystem)
include_regular_expression("^([^b]|b[^o]|bo[^o]|boo[^s]|boos[^t]|boost[^/]).*$")

set (OpenCV_DIR /home/emanuele/opencv/build)

find_package( OpenCV REQUIRED )
find_package( Boost COMPONENTS system thread filesystem REQUIRED)

#find_package (sqlite3)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql XmlPatterns Xml)
#include_directories(${SQLITE3_INCLUDE_DIRS})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsqlite3")
##target_link_libraries (new ${SQLITE3_LIBRARIES})


###
### make sure we use c++11
###
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

###
###boost include stuff (required for all libcam)
###
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

###
### QT stuff (required if you want a GUI)
###
set(CMAKE_AUTOMOC ON)  #This will autogenerate qt gui stuff
set(CMAKE_AUTORCC ON)  #this needs to be on so cmake will know what to do with QT resource Files

find_package(Qt5Widgets)
find_package(Qt5PrintSupport)
#find all the qt UI stuff
file(GLOB UI
    "ui/*.ui"
)
#make them into headers
qt5_wrap_ui (UI_HDRS  ${UI})

###
### add all your non QT sources
###

# find all non ui sources
file(GLOB SRCS
    "src/*.h"
    "src/*.cpp"
    "src/*.hpp"
)

# find all ui related sources
file(GLOB UI_SRCS
    "ui/*.h"
    "ui/*.cpp"
    "ui/*.hpp"
)

###
### Add executables
###

add_executable(ERDatabaseSystem main/main.cpp ui/qrc/res.qrc ${SRCS} ${UI_HDRS} ${UI_SRCS})
target_link_libraries (ERDatabaseSystem  Qt5::Widgets  ${Boost_LIBRARIES} ${OpenCV_LIBS} Qt5::PrintSupport Qt5::Core Qt5::Quick Qt5::Sql Qt5::XmlPatterns Qt5::Xml)

###
### Add Library
###

SET(QT_USE_QTXML TRUE)

add_library(ERDatabaseSystem_lib SHARED ui/qrc/res.qrc ${SRCS} ${UI_HDRS} ${UI_SRCS})
target_include_directories (ERDatabaseSystem_lib PUBLIC "src/" "ui/")
target_link_libraries (ERDatabaseSystem_lib Qt5::Widgets  ${Boost_LIBRARIES} ${OpenCV_LIBS} Qt5::PrintSupport Qt5::Core Qt5::Quick Qt5::Sql Qt5::XmlPatterns Qt5::Xml)
