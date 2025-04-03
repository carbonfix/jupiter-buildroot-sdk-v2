
cmake_minimum_required(VERSION 3.0)

# determine if jetson-utils is being built as a submodule inside another repo,
# or if it's being build standalone (if the later, we need to do some configuration)
get_directory_property(hasParent PARENT_DIRECTORY)

if(hasParent)
	message("-- jetson-utils:  building as submodule, ${hasParent}")
else()
	message("-- jetson-utils:  building as standalone")

	# standalone project
	project(jetson-utils)

	# -std=gnu++11
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-write-strings")
#[[
	# setup CUDA
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cuda")
	find_package(CUDA)
	message("-- CUDA version: ${CUDA_VERSION}")

	set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -O3)

	if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
		message("-- CUDA ${CUDA_VERSION} detected (${CMAKE_SYSTEM_PROCESSOR}), enabling SM_53 SM_62")
		set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=compute_53,code=sm_53 -gencode arch=compute_62,code=sm_62)

		if(CUDA_VERSION_MAJOR GREATER 9)
			message("-- CUDA ${CUDA_VERSION} detected (${CMAKE_SYSTEM_PROCESSOR}), enabling SM_72")
			set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=compute_72,code=sm_72)
		endif()

		if(CUDA_VERSION_MAJOR GREATER 10)
			message("-- CUDA ${CUDA_VERSION} detected (${CMAKE_SYSTEM_PROCESSOR}), enabling SM_87")
			set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=compute_87,code=sm_87)
		endif()
	endif()
]]
	# setup project output paths
	set(PROJECT_OUTPUT_DIR  ${PROJECT_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR})
	set(PROJECT_INCLUDE_DIR ${PROJECT_OUTPUT_DIR}/include)

	file(MAKE_DIRECTORY ${PROJECT_INCLUDE_DIR})
	file(MAKE_DIRECTORY ${PROJECT_OUTPUT_DIR}/bin)

	message("-- system arch:  ${CMAKE_SYSTEM_PROCESSOR}")
	message("-- output path:  ${PROJECT_OUTPUT_DIR}")

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/lib)

	# detect distro version
	find_program(LSB_RELEASE_EXEC lsb_release)

	execute_process(COMMAND "${LSB_RELEASE_EXEC}" --short --id OUTPUT_VARIABLE LSB_RELEASE_ID OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND "${LSB_RELEASE_EXEC}" --short --release OUTPUT_VARIABLE LSB_RELEASE_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
	execute_process(COMMAND "${LSB_RELEASE_EXEC}" --short --codename OUTPUT_VARIABLE LSB_RELEASE_CODENAME OUTPUT_STRIP_TRAILING_WHITESPACE)

	message("-- distro ID:       ${LSB_RELEASE_ID}")
	message("-- distro version:  ${LSB_RELEASE_VERSION}")
	message("-- distro codename: ${LSB_RELEASE_CODENAME}")

	# build C/C++ interface
	include_directories(${PROJECT_INCLUDE_DIR})
	#include_directories(/usr/include/gstreamer-1.0 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/include /usr/include/glib-2.0 /usr/include/libxml2 /usr/lib/aarch64-linux-gnu/glib-2.0/include/)

endif()

# To find OpenCV, one may need to set OpenCV_DIR variable to the
# absolute path to the directory containing OpenCVConfig.cmake file.
# Otherwise, try to set OPENCV_INC and OPENCV_LIB variables via the
# command line or GUI.
if ((NOT DEFINED OPENCV_INC OR OPENCV_INC STREQUAL "") OR ((NOT DEFINED OPENCV_LIB OR OPENCV_LIB STREQUAL "")))
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs videoio highgui)
if (OpenCV_FOUND)
  if (NOT DEFINED OPENCV_INC OR OPENCV_INC STREQUAL "")
    set(OPENCV_INC "${OpenCV_INCLUDE_DIRS}")
  endif()
  if (NOT DEFINED OPENCV_LIB OR OPENCV_LIB STREQUAL "")
    get_target_property(OpenCV_LIB_PATH opencv_core LOCATION)
    get_filename_component(OPENCV_LIB ${OpenCV_LIB_PATH} DIRECTORY)
    set(OPENCV_LIBS ${OpenCV_LIBS})
  endif()
endif()
endif()

if (NOT DEFINED OPENCV_INC OR OPENCV_INC STREQUAL "")
  message(FATAL_ERROR "OpenCV include dirs not found for platform ${CMAKE_GENERATOR_PLATFORM}")
endif()

link_directories(${OPENCV_LIB} ${OPENCV_LIB}/3rdparty)
include_directories(${OPENCV_INC})

# option for enabling/disabling NVMM memory in multimedia stack
find_library(NVBUF_UTILS NAMES nvbuf_utils PATHS /usr/lib/aarch64-linux-gnu/tegra)
message("-- nvbuf_utils:  ${NVBUF_UTILS}")

if(NVBUF_UTILS)
	set(ENABLE_NVMM_DEFAULT ON)
else()
	set(ENABLE_NVMM_DEFAULT OFF)
endif()

option(ENABLE_NVMM "Enable use of NVMM zero-copy memory in video and camera streaming" ${ENABLE_NVMM_DEFAULT})
message("-- NVMM zero-copy memory:  ENABLE_NVMM=${ENABLE_NVMM}")

if(ENABLE_NVMM)
	add_definitions(-DENABLE_NVMM)
endif()

set(project_dir ${PROJECT_SOURCE_DIR})
#message("-- project_dir is ${PROJECT_SOURCE_DIR}")

# additional paths for includes and libraries
include_directories(${PROJECT_INCLUDE_DIR}/jetson-utils)
#include_directories(/usr/include/gstreamer-1.0 /usr/include/glib-2.0 /usr/include/libxml2 /usr/include/json-glib-1.0 /usr/include/libsoup-2.4 /usr/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu/gstreamer-1.0/include /usr/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu/glib-2.0/include/)
include_directories(${project_dir} ${project_dir}/glib ${project_dir}/gst ${project_dir}/rtsp-server ${project_dir}/spm)

link_directories(${project_dir}/sensors/lib)
#[[
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
	include_directories(/usr/src/jetson_multimedia_api/include)
	link_directories(/usr/lib/aarch64-linux-gnu/tegra)
endif()
]]

# build library
#file(GLOB jetsonUtilitySources *.cpp camera/*.cpp codec/*.cpp cuda/*.cu cuda/*.cpp display/*.cpp image/*.cpp input/*.cpp network/*.cpp threads/*.cpp video/*.cpp)
#file(GLOB jetsonUtilityIncludes *.h *.hpp camera/*.h codec/*.h cuda/*.h cuda/*.cuh display/*.h image/*.h image/*.inl input/*.h network/*.h threads/*.h threads/*.inl video/*.h)
file(GLOB jetsonUtilitySources *.cpp camera/*.cpp codec/*.cpp input/*.cpp network/*.cpp threads/*.cpp display/*.cpp image/*.cpp json-glib/*.c video/*.cpp)
file(GLOB jetsonUtilityIncludes *.h *.hpp camera/*.h codec/*.h input/*.h network/*.h threads/*.h threads/*.inl display/*.h image/*.h image/*.inl json-glib/*.h video/*.h sensors/include/*.h)

#cuda_add_library(jetson-utils SHARED ${jetsonUtilitySources})
#target_link_libraries(jetson-utils GL GLU GLEW gstreamer-1.0 gstapp-1.0 gstpbutils-1.0 gstwebrtc-1.0 gstsdp-1.0 gstrtspserver-1.0 json-glib-1.0 soup-2.4 ${CUDA_nppicc_LIBRARY})

add_library(jetson-utils SHARED ${jetsonUtilitySources})
target_link_libraries(jetson-utils gstreamer-1.0 gstapp-1.0 gstpbutils-1.0 gstwebrtc-1.0 gstsdp-1.0 gstrtspserver-1.0 glib-2.0 gio-2.0 gobject-2.0 gstbase-1.0 gstrtsp-1.0 soup-2.4
						opencv_core opencv_imgproc opencv_videoio opencv_imgcodecs opencv_highgui
						cam_sensors cppfw-2.0 cpp ispeagle isp sdkcam tuningtools vi)

## add test file
set(SRC_LIST test/test_1.cpp) # error "OpenCV 4.x+ requires enabled C++11 support
add_executable(jetson-test ${SRC_LIST})
target_link_directories(jetson-test PRIVATE ./ build/x64_64/lib/)
target_link_libraries(jetson-test PUBLIC jetson-utils gstreamer-1.0 gstapp-1.0 gstpbutils-1.0 gstwebrtc-1.0 gstsdp-1.0 gstrtspserver-1.0 glib-2.0 gio-2.0 gobject-2.0 gstbase-1.0 gstrtsp-1.0 soup-2.4
						opencv_core opencv_imgproc opencv_videoio opencv_imgcodecs opencv_highgui
						cam_sensors cppfw-2.0 cpp ispeagle isp sdkcam tuningtools vi)

#[[
if(NVBUF_UTILS)
	target_link_libraries(jetson-utils nvbuf_utils)
endif()

# transfer all headers to the include directory
file(MAKE_DIRECTORY ${PROJECT_INCLUDE_DIR}/jetson-utils)

foreach(include ${jetsonUtilityIncludes})
	message("-- Copying ${include}")
	configure_file(${include} ${PROJECT_INCLUDE_DIR}/jetson-utils COPYONLY)
endforeach()

# install headers
foreach(include ${jetsonUtilityIncludes})
	install(FILES "${include}" DESTINATION include/jetson-utils)
endforeach()
]]

# install the shared library
#install(TARGETS jetson-utils DESTINATION lib EXPORT jetson-utilsConfig)

# install the cmake project, for importing
#install(EXPORT jetson-utilsConfig DESTINATION share/jetson-utils/cmake)

# build python bindings + samples
# add_subdirectory(python)
# add_subdirectory(video/video-viewer)

add_subdirectory(camera/camera-viewer)
add_subdirectory(display/gl-display-test)
add_subdirectory(network/webrtc-server)
add_subdirectory(network/rtsp-server)

