# Create an INTERFACE library for our C module.

add_library(usermod_lcd_bus INTERFACE)

set(INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/modlcd_bus.c
    ${CMAKE_CURRENT_LIST_DIR}/src/i2c_bus.c
    ${CMAKE_CURRENT_LIST_DIR}/src/spi_bus.c
    ${CMAKE_CURRENT_LIST_DIR}/src/i80_bus.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rgb_bus.c
)


# Add our source files to the lib
target_sources(usermod_lcd_bus INTERFACE ${SOURCES})

# Add include directories.
target_include_directories(usermod_lcd_bus INTERFACE ${INCLUDES})

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_lcd_bus)
