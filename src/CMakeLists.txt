project (Dsim)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/math/linear_algebra.cpp)
list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Render/GL/GLRender.cpp)
list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Render/GL/GLBufferObject.cpp)
list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Render/GL/GLShaderObject.cpp)
list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Render/ShaderObject.cpp)
list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsWindowGLFW.cpp)
list(APPEND SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/debug.cpp)

add_library(dsim SHARED ${SOURCE_FILES})
set_target_properties(dsim PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)
target_include_directories(dsim PUBLIC "/usr/include/GLFW")
target_link_libraries(dsim PRIVATE glfw GL GLEW)

