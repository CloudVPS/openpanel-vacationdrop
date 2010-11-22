# This file is part of OpenPanel - The Open Source Control Panel
# OpenPanel is free software: you can redistribute it and/or modify it 
# under the terms of the GNU General Public License as published by the Free 
# Software Foundation, using version 3 of the License.
#
# Please note that use of the OpenPanel trademark may be subject to additional 
# restrictions. For more information, please visit the Legal Information 
# section of the OpenPanel website on http://www.openpanel.com/

include makeinclude

OBJ	= main.o

OBJ_SETVACATION = setvacation.o

all: vacationdrop setvacation

vacationdrop: $(OBJ)
	$(LD) $(LDFLAGS) -o vacationdrop $(OBJ) $(LIBS)

setvacation: $(OBJ_SETVACATION)
	$(LD) $(LDFLAGS) -o setvacation $(OBJ_SETVACATION) $(LIBS)

clean:
	rm -f *.o
	rm -f vacationdrop
	rm -f setvacation

install:
	mkdir -p "${DESTDIR}/usr/bin/"
	mkdir -p "${DESTDIR}/etc/vacationdrop/recipients"
	
	install -m 755 vacationdrop "${DESTDIR}/usr/bin/vacationdrop"
	install -m 755 setvacation "${DESTDIR}/usr/bin/setvacation"


SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<
