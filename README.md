* Efficient Black Scholes module for python : millions of prices/greeks per sec, hundred of ks of immplied vols per sec.

  There are so many libraries that just implement BS for python, but none takes it to the needed level

  * setup
  	* you'll need boost.math, intel tbb and fmt
	* one may need to set something like CMAKE_ARGS=-DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg-pybind11/scripts/buildsystems/vcpkg.cmake if you're using vcpkg
	* just run pip install ./pyblsc
	
* prices/delta/gamma/vega and implied vol are parallelized above a certain threshold

* TODO:
	* add simd (when EVE is ported to windows maybe)
 	* port to pypi
  	* contributions welcome
