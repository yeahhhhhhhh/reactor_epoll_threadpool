cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(MY_LIB 
 src/MyEpoll.cc 
 src/Socket.cc 
 src/TcpSocket.cc 
 src/TcpServerSocket.cc 
 src/Utils.cc 
# src/MyReactor.cc 
 src/MyEpoll.cc 
 src/MyThread.cc 
 src/MyCondition.cc 
 src/MyThreadPool.cc  
 src/MyHandler.cc 
 src/MyLoop.cc 
 )
 
add_library(mylib ${MY_LIB})
target_link_libraries(mylib pthread)

add_subdirectory(test)
