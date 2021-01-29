cmake_minimum_required(VERSION 3.16)
project(moduleLearn)

set(CMAKE_CXX_STANDARD 17)

add_executable(moduleLearn
        mutiThreadProgramming/code1.cpp mutiThreadProgramming/future_test.cpp mutiThreadProgramming/promise_test.cpp mutiThreadProgramming/atomic_test.cpp mutiThreadProgramming/atomic_flag_test.cpp mutiThreadProgramming/spinLock_test.h mutiThreadProgramming/singleInstance.cpp)

add_executable(test mutiThreadProgramming/code1.cpp)
add_executable(future_test mutiThreadProgramming/future_test.cpp)
add_executable(promise_test mutiThreadProgramming/promise_test.cpp)
add_executable(atomic_test mutiThreadProgramming/atomic_test.cpp)
TARGET_LINK_LIBRARIES(atomic_test -latomic)

add_executable(atomic_flag_test mutiThreadProgramming/atomic_flag_test.cpp)