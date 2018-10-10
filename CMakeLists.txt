##
##  CmakeLists.txt
##
##  Copyright (c) 2013-2018 Matthias Melcher. All rights reserved.
##


cmake_minimum_required (VERSION 3.1)

project (IotaSlicer)

set (IotaSlicer_VERSION_MAJOR 0)
set (IotaSlicer_VERSION_MINOR 3)
set (IotaSlicer_VERSION_BUILD 0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_OSX_ARCHITECTURES=i386;x86_64)

# APPLE WIN32 MSVC UNIX
if (APPLE)
	set (PLATFORM_DIR platforms/MacOS)
endif()

if (MSVC)
#	set(CMAKE_CXX_FLAGS_DEBUG_INIT "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
#	set(CMAKE_CXX_FLAGS_RELEASE_INIT        "/MT /O2 /Ob2 /D NDEBUG")
endif()

# configure_file ("${PROJECT_SOURCE_DIR}/TutorialConfig.h.in")
# #define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@


function(FLTK_RUN_FLUID TARGET SOURCES)
    set (CXX_FILES)
    foreach(src ${SOURCES})
        if ("${src}" MATCHES "\\.fl$")
            string(REGEX REPLACE "(.*).fl" \\1 basename ${src})
            get_filename_component (src_name ${src} NAME)
            get_filename_component (src_absolute ${src} ABSOLUTE)
            get_filename_component (srcdir_absolute ${src_absolute} DIRECTORY)
            add_custom_command(
                OUTPUT "${basename}.cxx" "${basename}.h"
                COMMAND
                    cd ${srcdir_absolute} &&
                    ${PROJECT_SOURCE_DIR}/${PLATFORM_DIR}/bin/fluid -c ${src_name}
                DEPENDS ${src}
                MAIN_DEPENDENCY ${src}
            )
            list(APPEND CXX_FILES "${basename}.cxx")
        endif ("${src}" MATCHES "\\.fl$")
        set (${TARGET} ${CXX_FILES} PARENT_SCOPE)
    endforeach(src)
endfunction(FLTK_RUN_FLUID TARGET SOURCES)

FLTK_RUN_FLUID (IotaSlicer "src/view/IAGUIMain.fl")

# message (${CXX_FILES})

link_directories (
	${PLATFORM_DIR}/lib/
)

include_directories (
	include
	src
)

add_executable (IotaSlicer MACOSX_BUNDLE
	src/Iota.cpp
	src/Iota.h
	src/app/IAError.cpp
	src/app/IAError.h
	src/app/IAMacros.h
	src/app/IAPreferences.cpp
	src/app/IAPreferences.h
	src/app/IAVersioneer.cpp
	src/app/IAVersioneer.h
	src/controller/IAController.cpp
	src/controller/IAController.h
	src/controller/IAPrinterListController.cpp
	src/controller/IAPrinterListController.h
	src/data/binaryData.cpp
	src/data/binaryData.h
	src/fileformats/IAFmtObj3ds.cpp
	src/fileformats/IAFmtObj3ds.h
	src/fileformats/IAFmtTexJpeg.cpp
	src/fileformats/IAFmtTexJpeg.h
	src/fileformats/IAGeometryReader.cpp
	src/fileformats/IAGeometryReader.h
	src/fileformats/IAGeometryReaderBinaryStl.cpp
	src/fileformats/IAGeometryReaderBinaryStl.h
	src/fileformats/IAGeometryReaderTextStl.cpp
	src/fileformats/IAGeometryReaderTextStl.h
	src/geometry/IAEdge.cpp
	src/geometry/IAEdge.h
	src/geometry/IAMath.cpp
	src/geometry/IAMath.h
	src/geometry/IAMesh.cpp
	src/geometry/IAMesh.h
	src/geometry/IASlice.cpp
	src/geometry/IASlice.h
	src/geometry/IATriangle.cpp
	src/geometry/IATriangle.h
	src/geometry/IAVector3d.cpp
	src/geometry/IAVector3d.h
	src/geometry/IAVertex.cpp
	src/geometry/IAVertex.h
	src/opengl/IAFramebuffer.cpp
	src/opengl/IAFramebuffer.h
	src/potrace/IAPotrace.cpp
	src/potrace/IAPotrace.h
	src/potrace/auxiliary.h
	src/potrace/bitmap.h
	src/potrace/config.h
	src/potrace/curve.c
	src/potrace/curve.h
	src/potrace/decompose.c
	src/potrace/decompose.h
	src/potrace/lists.h
	src/potrace/platform.h
	src/potrace/potracelib.c
	src/potrace/potracelib.h
	src/potrace/progress.h
	src/potrace/trace.c
	src/potrace/trace.h
	src/printer/IAPrinter.cpp
	src/printer/IAPrinter.h
	src/printer/IAPrinterFDM.cpp
	src/printer/IAPrinterFDM.h
	src/printer/IAPrinterFDMBelt.cpp
	src/printer/IAPrinterFDMBelt.h
	src/printer/IAPrinterInkjet.cpp
	src/printer/IAPrinterInkjet.h
	src/printer/IAPrinterLasercutter.cpp
	src/printer/IAPrinterLasercutter.h
	src/printer/IAPrinterList.cpp
	src/printer/IAPrinterList.h
	src/printer/IAPrinterSLS.cpp
	src/printer/IAPrinterSLS.h
	src/printer/IASetting.cpp
	src/printer/IASetting.h
	src/property/IAProperty.cpp
	src/property/IAProperty.h
	src/toolpath/IADxfWriter.cpp
	src/toolpath/IADxfWriter.h
	src/toolpath/IAGcodeWriter.cpp
	src/toolpath/IAGcodeWriter.h
	src/toolpath/IAToolpath.cpp
	src/toolpath/IAToolpath.h
	src/view/IAGUIMain.cpp
	src/view/IAGUIMain.h
	src/view/IAProgressDialog.cpp
	src/view/IAProgressDialog.h
	src/widget/IACamera.cpp
	src/widget/IACamera.h
	src/widget/IAGLButton.cpp
	src/widget/IAGLButton.h
	src/widget/IAGLRangeSlider.cpp
	src/widget/IAGLRangeSlider.h
	src/widget/IASceneView.cpp
	src/widget/IASceneView.h
)

source_group(src\\ src/)
source_group(src\\app src/app)
source_group(src\\controller src/controller)
source_group(src\\data src/data)
source_group(src\\fileformats src/fileformats)
source_group(src\\geometry src/geometry)
source_group(src\\opengl src/opengl)
source_group(src\\potrace src/potrace)
source_group(src\\printer src/printer)
source_group(src\\property src/property)
source_group(src\\toolpath src/toolpath)
source_group(src\\view src/view)
source_group(src\\widget src/widget)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(IotaSlicer ${OPENGL_LIBRARIES})

# APPLE WIN32 MSVC UNIX
if (APPLE)
#   set( OSX_ICON_FILES vvv.icns vvv-document.icns )
#	set_target_properties(IotaSlicer PROPERTIES BUNDLE TRUE)
#    set (MACOSX_BUNDLE_INFO_PLIST ${PLATFORM_DIR}/Info.plist)
    set_target_properties( IotaSlicer PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/${PLATFORM_DIR}/Info.plist)
	target_link_libraries (IotaSlicer
		"-framework AppKit"
		"-framework CoreText"
		"-framework CoreGraphics"
		"-framework CoreFoundation"
		"-framework OpenGL"
	)
#   set_target_properties( vvv PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/vvv-Info.plist )
endif()
if (UNIX AND NOT APPLE)
endif()

target_link_libraries (IotaSlicer 
	fltk
	fltk_gl
	fltk_images
	fltk_jpeg
	fltk_png
	fltk_z
	3ds
)

#add_custom_command (
#	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#	COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
#	DEPENDS MakeTable
#)


