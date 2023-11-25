# This file is to be given as "make USER_C_MODULES=..." when building Micropython port

find_package(Python3 REQUIRED COMPONENTS Interpreter)

separate_arguments(LV_CFLAGS_ENV UNIX_COMMAND $ENV{LV_CFLAGS})
list(APPEND LV_CFLAGS ${LV_CFLAGS_ENV} -Wno-unused-function)

if(ESP_PLATFORM)
    include(${CMAKE_CURRENT_LIST_DIR}/driver/esp32/lcd_bus/micropython.cmake)
endif(ESP_PLATFORM)

file(GLOB_RECURSE LVGL_HEADERS ${CMAKE_CURRENT_LIST_DIR}/lvgl/src/*.h ${CMAKE_CURRENT_LIST_DIR}/lv_conf.h)

# this MUST be an execute_process because of the order in which cmake does things
# if add_custom_command is used it errors becasue add_custom_command doesn't
# actually run before the lv_mp.c file gets added to the source list. That causes
# the compilation to error because the source file doesn't exist. It needs to
# exist before it gets added to the source list and this is the only way I have
# found to go about doing it.
execute_process(
    COMMAND
        ${Python3_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/gen/gen_mpy.py ${LV_CFLAGS} --output=${CMAKE_BINARY_DIR}/lv_mp.c --include=${CMAKE_CURRENT_LIST_DIR} --include=${CMAKE_CURRENT_LIST_DIR}/include --include=${CMAKE_CURRENT_LIST_DIR}/lvgl --board=esp32 --module_name=lvgl --module_prefix=lv --metadata=${CMAKE_BINARY_DIR}/lv_mp.c.json ${CMAKE_CURRENT_LIST_DIR}/lvgl/lvgl.h
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR}

    RESULT_VARIABLE mpy_result
    OUTPUT_VARIABLE mpy_output
)

if(${mpy_result} GREATER "0")
    message("OUTPUT: ${mpy_output}")
    message("RESULT: ${mpy_result}")
    message( FATAL_ERROR "Failed to generate ${CMAKE_BINARY_DIR}/lv_mp.c" )
endif()

# file(WRITE ${CMAKE_BINARY_DIR}/lv_mp.c ${mpy_output})

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/lvgl/src/*.c)

add_library(lvgl_interface INTERFACE)

target_sources(lvgl_interface INTERFACE ${SOURCES})
target_compile_options(lvgl_interface INTERFACE ${LV_CFLAGS})


set(LVGL_MPY_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/micropython
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)


add_library(usermod_lvgl INTERFACE)
target_sources(usermod_lvgl INTERFACE ${CMAKE_BINARY_DIR}/lv_mp.c)
target_include_directories(usermod_lvgl INTERFACE ${LVGL_MPY_INCLUDES})
target_link_libraries(usermod_lvgl INTERFACE lvgl_interface)
target_link_libraries(usermod INTERFACE usermod_lvgl)
