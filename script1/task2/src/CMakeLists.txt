project(task2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(task2 task2.cxx)

target_link_libraries(task2 ${ITK_LIBRARIES})