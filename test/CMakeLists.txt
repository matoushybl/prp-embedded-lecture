find_package(GTest REQUIRED)
enable_testing()

set(TEST_LIBS
        project_shared
        GTest::GTest
        GTest::Main)

macro(declare_test NAME FILE)
    add_executable(${NAME} ${FILE})
    target_link_libraries(${NAME} PRIVATE ${LIBS} ${TEST_LIBS})
    add_test(NAME ${NAME} COMMAND ${FILE})
endmacro()

declare_test(udpSocketTests udpSocketTests.cpp)
declare_test(robotTests.cpp robotTests.cpp)
