# db_test
file(GLOB DB_TEST_SRC db/db_test.cpp)

add_executable(db_test ${DB_TEST_SRC})

target_link_libraries(db_test dreamdb)

add_test(NAME DB_TEST COMMAND db_test)