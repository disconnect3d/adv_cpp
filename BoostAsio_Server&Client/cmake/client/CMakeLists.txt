cmake_minimum_required(VERSION 2.6)

project(log_client)

ADD_DEFINITIONS(
	-std=c++11
	-lboost_system
)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS system) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Client src/main.cxx src/tcp_client.cxx src/tcp_client.h) 
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()