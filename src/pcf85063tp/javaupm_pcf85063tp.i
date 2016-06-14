%module javaupm_pcf85063tp
%include "../upm.i"
%include "arrays_java.i";
%include "../java_buffer.i"

%{
    #include "pcf85063tp.hpp"
%}

%include "pcf85063tp.hpp"

%pragma(java) jniclasscode=%{
    static {
        try {
            System.loadLibrary("javaupm_ds1307");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }
%}
