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