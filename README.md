* Efficient Black Scholes library for python

  There are so many libraries that just implement BS for python, but none takes it to the needed level

  * setup
  	* you'll need boost.math, intel tbb and fmt
	* one may need to set something like CMAKE_ARGS=-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg-pybind11/scripts/buildsystems/vcpkg.cmake if you're using vcpkg
	* just run pip install ./pyblsc
	
