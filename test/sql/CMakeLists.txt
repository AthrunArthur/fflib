#add_executable(ntobject use_ntobject.cpp)
#add_executable(full full_use.cpp)
#add_executable(use_ntobject_in_namespace use_ntobject_in_namespace.cpp)
#add_executable(use_ntobject_in_class use_ntobject_in_class.cpp)
#add_executable(use_ntarray use_ntarray.cpp)
#add_executable(ntarray_benchmark ntarray_benchmark.cpp)

#target_link_libraries(ntobject mysqlcppconn ff_net)
#target_link_libraries(full mysqlcppconn)


add_executable(binary binary.cpp)
add_executable(blob blob.cpp)
add_executable(enum_set enum_set.cpp)
add_executable(native_type native_type.cpp)
add_executable(test_multithread test_multithread.cpp)
add_executable(test_transaction test_transactions.cpp)
add_executable(table use_table.cpp)


target_link_libraries(binary mysqlcppconn)
target_link_libraries(blob mysqlcppconn)
target_link_libraries(enum_set mysqlcppconn)
target_link_libraries(native_type mysqlcppconn)
target_link_libraries(test_multithread mysqlcppconn -lpthread)
target_link_libraries(test_transaction mysqlcppconn)
target_link_libraries(table mysqlcppconn)
