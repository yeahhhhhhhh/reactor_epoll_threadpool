set(TEST 
 MyEpollTest.cc 
 )

add_executable(out ${TEST})

add_dependencies(out mylib)

target_link_libraries(out mylib pthread)
