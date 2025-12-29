cmake_minimum_required(VERSION 3.23)

project(Simple)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(start)
target_sources(start
  PRIVATE
    start.cpp
)

add_subdirectory(lib/catch2)
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

if (MSVC)
    target_compile_options(start PRIVATE
        $<$<CONFIG:Debug>:/Zi /Od /RTC1>
        $<$<CONFIG:Release>:/O2 /GL>
    )
    target_link_options(start PRIVATE
        $<$<CONFIG:Release>:/LTCG>
    )
else()
  target_compile_options(start PRIVATE
        $<$<CONFIG:Release>:-O3 -flto -ffunction-sections -fdata-sections>
  )
  target_link_options(start PRIVATE
      $<$<CONFIG:Release>:-Wl,--gc-sections>
  )
endif()

# ---------- GLFW ----------
# find_package(glfw3 3.3 REQUIRED)

# ---------- OpenGL ----------
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS      OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS     OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES  OFF CACHE BOOL "")
set(GLFW_INSTALL         OFF CACHE BOOL "")
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "")
add_subdirectory(lib/glfw) 

set(IMGUI_DIR lib/imgui)
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

add_executable(start_imgui WIN32 start_imgui.cpp)
target_link_libraries(start_imgui PRIVATE imgui)

if(MSVC)
    set_target_properties(start_imgui PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
