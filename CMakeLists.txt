cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME pybs)
project(${PROJECT_NAME} LANGUAGES CXX)

message("configuring ${PROJECT_NAME}...")

find_package(Boost REQUIRED) # COMPONENTS math)
find_package(TBB CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

    # pybind11 method:
    pybind11_add_module(pybs pybs.cpp bs.cpp bs.h rando.cpp rando.h bsv.cpp bsv.h)

    # Python method:
    #Python_add_library(pybs bs.cpp)
    #target_link_libraries(pybs pybind11::headers)
    #set_target_properties(pybs PROPERTIES
    #    INTERPROCEDURAL_OPTIMIZATION ON
    #    CXX_VISIBILITY_PRESET ON
    #    VISIBILITY_INLINES_HIDDEN ON
    #)

target_link_libraries(pybs PRIVATE pybind11::module  Boost::boost TBB::tbb TBB::tbbmalloc TBB::tbbmalloc_proxy fmt::fmt-header-only) #   Boost::math)
# target_link_libraries(main PRIVATE Boost::boost Boost::<lib1> Boost::<lib2> ...)


message("... {PROJECT_NAME} configuring done")
