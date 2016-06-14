// Include doxygen-generated documentation
%include "pyupm_doxy2swig.i"
%module pyupm_pcf85063tp
%include "../upm.i"

%feature("autodoc", "3");

#ifdef DOXYGEN
%include "pcf85063tp_doc.i"
#endif

%include "pcf85063tp.hpp"
%{
    #include "pcf85063tp.hpp"
%}
