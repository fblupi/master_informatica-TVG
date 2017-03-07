project(task1)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(task1 task1.cxx)

target_link_libraries(task1 ${ITK_LIBRARIES})