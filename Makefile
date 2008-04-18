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

makeinclude:
	@echo please run ./configure
	@false

SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<
