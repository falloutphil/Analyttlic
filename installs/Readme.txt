C++ Bindings to Python are not generated automatically.

You need to install boost-python, gccxml pygccxml and then Py++.  Note I've included the 1.33 libs for Boost python, as these definately work, but you'll probably need a full install with the includes too!

After install you'll have a program called pyplusplus_gui which takes in header files and generated the C++ code to cut and paste into pyInterface.cpp.

Note this could have been made part of the makefile by generating the XML
and then using the gui to generate a Python script to write out the
C++.  Obviously I wasn't feeling ambitious enough to automate this!

Also we have a previous version of the software here, which is fully
working for the Bloomberg parser only.  Not sure if I ever got the
DMO parser working.

