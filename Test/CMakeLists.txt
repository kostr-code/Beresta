project(tests VERSION 0.1.0)

add_executable(Test src/test_main.cpp)

target_link_libraries(Test PRIVATE App)

add_test(NAME Test COMMAND Test)

