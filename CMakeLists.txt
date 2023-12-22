cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME pybs)
project(${PROJECT_NAME} LANGUAGES CXX)

message("configuring ${PROJECT_NAME}...")


find_package(Python COMPONENTS Interpreter Development)
    find_package(pybind11 CONFIG)

    # pybind11 method:
    pybind11_add_module(MyModule1 src1.cpp)

    # Python method:
    Python_add_library(MyModule2 src2.cpp)
    target_link_libraries(MyModule2 pybind11::headers)
    set_target_properties(MyModule2 PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION ON
        CXX_VISIBILITY_PRESET ON
        VISIBILITY_INLINES_HIDDEN ON
    )


if (NOT MINGW)

add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/JMC>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/Od>")
add_compile_options("$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RELWITHDEBINFO>>:/Ob0>")
add_compile_options($<$<CXX_COMPILER_ID:GNU>:-fvisibility=hidden>)


#set(PYBIND11_FINDPYTHON OFF)
#find_package(Python COMPONENTS Interpreter Development)

# find python executable (for msvc DEBUG)
if (MSVC)
    if(DEFINED Python_EXECUTABLE)
        set(my_python ${Python_EXECUTABLE})
    else()
        find_program (my_python python NO_CACHE)
    endif()
endif()

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED) #  Development 

#set(PYBIND11_FINDPYTHON ON)
#find_vcpkg_install_missing(pybind11)
#add_compile_definitions(PYBIND11_USE_SMART_HOLDER_AS_DEFAULT)
#git_include(pybind11 "https://github.com/pybind/pybind11.git" BRANCH smart_holder)

message("python: ${Python_EXECUTABLE}")

find_package(pybind11 CONFIG RQUIRED)

#pybind11_add_module(portfolio_module MODULE example.cpp)
add_compile_definitions(PY_NO_LINK_LIB)
add_compile_definitions(PYBIND11_DETAILED_ERROR_MESSAGES)
#add_compile_definitions(Py_DEBUG)


#pybind11_add_module(example example.cpp)
# Create an extension module
file(GLOB pm_srcs *.py)
add_source_group_and_list_together(. pm_srcs)
add_source_group_and_list_together(data pm_srcs)
add_source_group_and_list_together(database pm_srcs)
add_source_group_and_list_together(index pm_srcs)
add_source_group_and_list_together(portfolio pm_srcs)
add_source_group_and_list_together(time pm_srcs)
add_source_group_and_list_together_pattern(python pm_srcs *.py)

add_library(portfolio_module MODULE ${pm_srcs} README.md)
target_link_libraries(portfolio_module PRIVATE pybind11::module portfolio)
pybind11_extension(portfolio_module)

if (MSVC)
set_property(TARGET portfolio_module
             PROPERTY EXCLUDE_FROM_DEFAULT_BUILD_DEBUG TRUE)
endif()

# if python was not found on command line or otherwise
if (MSVC)
        if ("${my_python}" STREQUAL "my_python-NOTFOUND")
        MESSAGE("python not found on command line. Using ${Python_EXECUTABLE} instead")
        set(my_python ${Python_EXECUTABLE})
        endif()
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND "${my_python}")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${CMAKE_CURRENT_SOURCE_DIR}/python/demo_trend.py")
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
#file(GENERATE OUTPUT filename.txt CONTENT "${CMAKE_CURRENT_BINARY_DIR}/portfolio_module.pyi")
    MESSAGE("stubgen found at ${my_stubgen}")
add_custom_command(TARGET portfolio_module POST_BUILD
    COMMAND "${my_stubgen}" -p portfolio_module -o .
    COMMAND "${my_stubgen}" -p portfolio_module.portfolio -o .
    WORKING_DIRECTORY $<TARGET_FILE_DIR:portfolio_module>
    BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/portfolio_module.pyi" "${CMAKE_CURRENT_BINARY_DIR}/portfolio_module/portfolio.pyi"
    COMMENT "generating python stubs..."
)

endif()

else()
message("not adding python module")

endif()

message("... python module configuring done")
