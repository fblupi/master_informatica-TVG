project(Image2)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(Image2 Image2.cxx)

target_link_libraries(Image2 ${ITK_LIBRARIES})