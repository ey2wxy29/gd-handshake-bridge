cmake_minimum_required(VERSION 3.25)

project(GDHandshakeMod VERSION 1.0.0)

find_package(Geode REQUIRED)

add_geode_mod(
    nobo.gd_handshake_bridge
    VERSION 1.0.0
    RESOURCES
    SOURCES src/main.cpp
)
