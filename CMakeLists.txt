cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME pyblsc)
project(${PROJECT_NAME} LANGUAGES CXX)

message("configuring ${PROJECT_NAME}...")

add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/JMC>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/Od>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/Ob0>")

find_package(Boost REQUIRED) # COMPONENTS math)
find_package(TBB CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
# find_package(MKL CONFIG REQUIRED)
# find_path(BSHOSHANY_THREAD_POOL_INCLUDE_DIRS "BS_thread_pool.hpp")
find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

    # pybind11 method:
    pybind11_add_module(pyblsc pybs.cpp bs.cpp bs.h rando.cpp rando.h bsv.cpp bsv.h fbs.h fbs.cpp)

    # Python method:
    #Python_add_library(pybs bs.cpp)
    #target_link_libraries(pybs pybind11::headers)
    #set_target_properties(pybs PROPERTIES
    #    INTERPROCEDURAL_OPTIMIZATION ON
    #    CXX_VISIBILITY_PRESET ON
    #    VISIBILITY_INLINES_HIDDEN ON
    #)

target_link_libraries(pyblsc PRIVATE pybind11::module  Boost::boost TBB::tbb TBB::tbbmalloc TBB::tbbmalloc_proxy fmt::fmt-header-only ) # MKL::MKL  Boost::math)
target_include_directories(pyblsc PRIVATE ${BSHOSHANY_THREAD_POOL_INCLUDE_DIRS})
# target_link_libraries(main PRIVATE Boost::boost Boost::<lib1> Boost::<lib2> ...)

set_property(TARGET pyblsc PROPERTY CXX_STANDARD 23)

if (MSVC)
    if(DEFINED Python_EXECUTABLE)
        set(my_python ${Python_EXECUTABLE})
    else()
        find_program (my_python python NO_CACHE)
    endif()
endif()

if (MSVC)
        if ("${my_python}" STREQUAL "my_python-NOTFOUND")
        MESSAGE("python not found on command line. Using ${Python_EXECUTABLE} instead")
        set(my_python ${Python_EXECUTABLE})
        endif()
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND "${my_python}")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${CMAKE_CURRENT_SOURCE_DIR}/demo_noQ.py")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif(MSVC)

if (MSVC)
    if (NOT "${my_python}" STREQUAL "my_python-NOTFOUND")
        cmake_path(GET my_python PARENT_PATH my_python_root)
        message("my_python_root ${my_python_root}")
        cmake_path(APPEND my_python_root "Scripts")
        message("my_python_root ${my_python_root}")
        find_program (my_stubgen stubgen HINTS ${my_python_root})
    else()
        find_program (my_stubgen stubgen)
    endif()
else()
    find_program (my_stubgen stubgen)
endif()
if ("${my_stubgen}" STREQUAL "my_stubgen-NOTFOUND")
	MESSAGE("stubgen not found. Python IDE intellisense may not be available. Consider installing mypy (pip install mypy)")
else ()
#file(GENERATE OUTPUT filename.txt CONTENT "${CMAKE_CURRENT_BINARY_DIR}/pyblsc.pyi")
    MESSAGE("stubgen found at ${my_stubgen}")
add_custom_command(TARGET pyblsc POST_BUILD
    COMMAND "${my_stubgen}" -p pyblsc -o .
    # COMMAND "${my_stubgen}" -p pyblsc.pyblsc -o .
    WORKING_DIRECTORY $<TARGET_FILE_DIR:pyblsc>
    BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/pyblsc.pyi" "${CMAKE_CURRENT_BINARY_DIR}/pyblsc/pyblsc.pyi"
    COMMENT "generating python stubs..."
)

endif()


message("... {PROJECT_NAME} configuring done")

