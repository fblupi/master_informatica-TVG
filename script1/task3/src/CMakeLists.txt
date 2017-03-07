project(task3)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(task3 task3.cxx)

target_link_libraries(task3 ${ITK_LIBRARIES})