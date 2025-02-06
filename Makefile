# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g # Add -O2 for optimization if needed

# Source files
SOURCES = petcare.cpp user.cpp pet.cpp schedule.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = petcarepro

# Rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean