set (libname "vcap")
set (libdescription "upm Video Frame Capture and image save utility")
set (module_src ${libname}.cxx)
set (module_hpp ${libname}.hpp)

find_package (JPEG)
if (JPEG_FOUND)
    set (reqlibname "jpeg")
    upm_module_init()
    target_link_libraries(${libname} jpeg)
    if (BUILDSWIG)
      if (BUILDSWIGNODE)
        swig_link_libraries (jsupm_${libname} jpeg)
      endif()
      if (BUILDSWIGPYTHON)
        swig_link_libraries (pyupm_${libname} jpeg)
      endif()
      if (BUILDSWIGJAVA)
        swig_link_libraries (javaupm_${libname} jpeg)
      endif()
    endif()
endif()