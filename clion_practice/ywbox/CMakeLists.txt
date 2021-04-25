cmake_minimum_required(VERSION 3.13)
project(ywbox C)

set(CMAKE_C_STANDARD 99)

add_executable(ywbox main.c src/voltameter.c src/io_check_ctl.c src/led_display.c src/temperature.c)