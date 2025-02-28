cmake_minimum_required(VERSION 3.5)

project(Opencv_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories and link libraries for SeetaFace2
include_directories(/Users/areay7/Opencv/SeetaFace2/FaceDetector/include/seeta)
link_directories(/Users/areay7/Opencv/SeetaFace2/build/bin)

file(GLOB_RECURSE HEAD_FILE /Users/areay7/Opencv/SeetaFace2/*.h)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)
set(DyLIB
    SeetaFaceDetector
    SeetaFaceLandmarker
    SeetaFaceRecognizer
    SeetaFaceTracker
    SeetaNet
    SeetaQualityAssessor)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Opencv_test
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${HEAD_FILE}
        image.qrc
    )
else()
    if(ANDROID)
        add_library(Opencv_test SHARED
            ${PROJECT_SOURCES}
            ${HEAD_FILE}
        )
    else()
        add_executable(Opencv_test
            ${PROJECT_SOURCES}
            ${HEAD_FILE}
        )
    endif()
endif()

# Link libraries
target_link_libraries(Opencv_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network ${OpenCV_LIBS}
    ${DyLIB}
)

# 设置 Info.plist 文件路径
set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist.in)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Opencv_test)
endif()
set_target_properties(Opencv_test PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${MACOSX_BUNDLE_INFO_PLIST}
)

include(GNUInstallDirs)
install(TARGETS Opencv_test
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Opencv_test)
endif()

# add_definitions(-DPRO_FILE_PWD="${CMAKE_SOURCE_DIR}")
