

# Create an INTERFACE library for our C module.
add_library(usermod_lcd_bus INTERFACE)

# list of source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.c)

set(I2C_BUS_SRC ${I2C_BUS_INC}/i2c_bus.c)
set(I80_BUS_SRC ${I80_BUS_INC}/i80_bus.c)
set(SPI_BUS_SRC ${SPI_BUS_INC}/spi_bus.c)
set(RGB_BUS_SRC ${RGB_BUS_INC}/rgb_bus.c)

set(INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/common
)

# compile options
target_compile_definitions(usermod_lcd_bus INTERFACE USE_ESP_LCD=1)

# Add our source files to the lib
target_sources(usermod_lcd_bus INTERFACE ${SOURCES})

target_compile_options(usermod_lcd_bus INTERFACE "-g")

# Add include directories.
target_include_directories(usermod_lcd_bus INTERFACE ${INCLUDES})

# Link our INTERFACE library to the usermod target.
target_link_libraries(usermod INTERFACE usermod_lcd_bus)
