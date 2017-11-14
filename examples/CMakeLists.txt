project(Dsim_examples)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/TestCommon")
file(GLOB COMMON_SRC ${CMAKE_CURRENT_SOURCE_DIR}/TestCommon/TestCommon.cpp)

add_executable(DevTest ${COMMON_SRC})
set_target_properties(DevTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
target_sources(DevTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DevTest/DevTest.cpp)
target_link_libraries(DevTest dsim)

