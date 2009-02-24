PROJECT_NAME=imcc_test
CPP=cl /c
LINK=cl /Fe$(PROJECT_NAME).exe
ADD_INCLUDE=
ADD_LIBRARY=IMCC\lib\mcconfc.lib IMCC\lib\mccorec.lib IMCC\lib\mcnetc.lib IMCC\lib\mcutilc.lib
DEFINITIONS=/D"WIN32" /D"_DEBUG" /ZI /Fd"imcc_test.pdb"
CPPFLAGS=/EHsc /MDd $(ADD_INCLUDE) $(DEFINITIONS)

imcc_test : main.obj stdafx.obj Conference.obj $(ADD_LIBRARY)
	$(LINK) main.obj stdafx.obj Conference.obj $(ADD_LIBRARY)

stdafx.obj : stdafx.cpp
	$(CPP) $(CPPFLAGS) stdafx.cpp

main.obj : stdafx.obj Conference.obj main.cpp
	$(CPP) $(CPPFLAGS) main.cpp

Conference.obj : stdafx.obj Conference.cpp
	$(CPP) $(CPPFLAGS) Conference.cpp
