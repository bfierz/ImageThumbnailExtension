#
# This file is part of the Visual Computing Library (VCL) release under the
# MIT license.
#
# Copyright (c) 2017 Basil Fierz
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
cmake_minimum_required(VERSION 2.8.2)
project(VclGraphicsThumbnailExtension)

# DirectXTex project
file(GLOB_RECURSE DIRECTXTEX_SRC "external/DirectXTex/DirectXTex/*.cpp" "external/DirectXTex/DirectXTex/*.h")
add_library(DirectXTex STATIC ${DIRECTXTEX_SRC})
target_include_directories(DirectXTex
	PUBLIC
		"external/DirectXTex"
)

# Define the source
set(EXT_SRC
	classfactory.cpp
	classfactory.h
	common.h
	dllmain.cpp
	registryhelpers.cpp
	registryhelpers.h
	thumbnailprovider.cpp
	thumbnailprovider.def
	thumbnailprovider.h
	version.h
	version.rc
)

set(TEST_SRC
	main.cpp
)

# Create the target
add_library(VclGraphicsThumbnailExt SHARED "")

# Use unicode
target_compile_definitions(VclGraphicsThumbnailExt
	PRIVATE
		UNICODE
		_UNICODE
)

# Add GLI to the project
#set(GLI_INCLUDE_DIR "" CACHE PATH "Include path to the GLI")
#target_include_directories(VclGraphicsThumbnailExt
#	PRIVATE
#		${GLI_INCLUDE_DIR}
#		${GLI_INCLUDE_DIR}/external/glm
#)

target_link_libraries(VclGraphicsThumbnailExt
	PRIVATE
		DirectXTex
		Shlwapi.lib
)

target_sources(VclGraphicsThumbnailExt
	PRIVATE
		${EXT_SRC}
)

# Create the target
add_executable(imageconv "")

target_link_libraries(imageconv
	PRIVATE
		DirectXTex
)

target_sources(imageconv
	PRIVATE
		${TEST_SRC}
)
