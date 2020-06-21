goal:	ExoMatch_unit_tests.exe

GCC = g++

CCFLAGS = -fbounds-check -Wall -fopenmp -O2

OBJ = tests.o Input.o ObsLinelist.o CalcLinelist.o LinearAssigProb.o \
      CombinationDiffs.o Timer.o Utils.o

ExoMatch_unit_tests.exe: $(OBJ) runtests.o
	$(GCC) -o ExoMatch_unit_tests.exe $(OBJ) $(CCFLAGS) runtests.o

runtests.o: runtests.cpp
	$(GCC) -c runtests.cpp $(CCFLAGS)

tests.o: tests.cpp
	$(GCC) -c tests.cpp $(CCFLAGS)

Input.o: ../Input.cpp
	$(GCC) -c ../Input.cpp $(CCFLAGS)

BaseLinelist.o: ../BaseLinelist.cpp
	$(GCC) -c ../BaseLinelist.cpp $(CCFLAGS)

ObsLinelist.o: ../ObsLinelist.cpp
	$(GCC) -c ../ObsLinelist.cpp $(CCFLAGS)

CalcLinelist.o: ../CalcLinelist.cpp
	$(GCC) -c ../CalcLinelist.cpp $(CCFLAGS)

LinearAssigProb.o: ../LinearAssigProb.cpp
	$(GCC) -c ../LinearAssigProb.cpp $(CCFLAGS)

CombinationDiffs.o: ../CombinationDiffs.cpp
	$(GCC) -c ../CombinationDiffs.cpp $(CCFLAGS)

Timer.o: ../Timer.cpp
	$(GCC) -c ../Timer.cpp $(CCFLAGS)

Utils.o: ../Utils.cpp
	$(GCC) -c ../Utils.cpp $(CCFLAGS)

clean:
	rm $(OBJ) runtests.o