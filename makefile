# Compiler settings
CXX = g++
CXXFLAGS = -std=c++14 -Wall

# Source files
SOURCES = main.cpp Game.cpp Player.cpp Board.cpp Street.cpp TrainStation.cpp Utility.cpp SurpriseSlot.cpp JailSlot.cpp TaxSlot.cpp FreeParkingSlot.cpp GoToJailSlot.cpp GoSlot.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Test files
TEST_SOURCES = test.cpp
TEST_OBJECTS = test.o

# Target for the main game
monopoly: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o monopoly $(OBJECTS)

# Target for the test suite (exclude main.o)
test: $(TEST_OBJECTS) Game.o Player.o Board.o Street.o TrainStation.o Utility.o SurpriseSlot.o JailSlot.o TaxSlot.o FreeParkingSlot.o GoToJailSlot.o GoSlot.o
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJECTS) Game.o Player.o Board.o Street.o TrainStation.o Utility.o SurpriseSlot.o JailSlot.o TaxSlot.o FreeParkingSlot.o GoToJailSlot.o GoSlot.o

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f *.o monopoly test

# Additional test object rule
test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o
