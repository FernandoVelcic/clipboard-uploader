cmake_minimum_required(VERSION 3.1)
PROJECT ( clipboard-uploader C CXX )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lboost_system")

set(THREADS_PREFER_PTHREAD_FLAG ON)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package (Threads)

file(GLOB clipboard-uploader_SRC
    "*.h"
    "*.cpp"
)

find_package(Boost COMPONENTS system date_time REQUIRED)

if(Boost_FOUND)
	message(STATUS "Boost include dir: " ${Boost_INCLUDE_DIRS})
	message(STATUS "Boost libraries: " ${Boost_LIBRARIES})

    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(clipboard-uploader ${clipboard-uploader_SRC}) 
    target_link_libraries(clipboard-uploader ${Boost_LIBRARIES})

	if(MSVC)
		add_definitions("/EHsc")
	endif()
endif()

#Clip dependency
# Disable clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
#set(CLIP_X11_PNG_LIBRARY "${PNG_LIBRARY}")
add_subdirectory("third_party/clip")
target_link_libraries(clipboard-uploader clip)