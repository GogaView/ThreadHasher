cmake_minimum_required(VERSION 3.14)
project(ThreadHasher)

set(CMAKE_CXX_STANDARD 14)

set(LOCAL_INCLUDE_DIR /opt/local/include)
set(Boost_LIBRARY_DIR /opt/local/lib)
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
include_directories(${LOCAL_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(Veeam main.cpp ArgumentParser.cpp ArgumentParser.h HasherException.h SafeFileReader.cpp SafeFileReader.h FileWriter.cpp FileWriter.h ThreadedHasher.cpp ThreadedHasher.h MultithreadedFileHasher.cpp MultithreadedFileHasher.h)
target_link_libraries( Veeam ${Boost_LIBRARIES} )