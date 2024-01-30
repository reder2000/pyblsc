cmake_minimum_required(VERSION 3.5.0)
project(pyblsc_tests VERSION 0.1.0)

message("Configuring pyblsc/tests ...")


find_package(Catch2 CONFIG REQUIRED)

include_directories(..)

add_executable(pyblsc_tests prices<cpp ../fbs.cpp ../rando.cpp)

target_link_libraries(pyblsc_tests Catch2::Catch2WithMain TBB::tbb TBB::tbbmalloc) #  fmt::fmt  date::date date::date-tz ${additional_libraries})
set_property(TARGET pyblsc_tests PROPERTY CXX_STANDARD 23)

message("... done pyblsc/tests Configuring")