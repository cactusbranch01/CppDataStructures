# Compiler and compiler flags
CC = g++
CFLAGS = -Wall -g

# Source, header, and object files
SOURCES = main.cpp queue.cpp stack.cpp
HEADERS = queue.h linked_list.h stack.h chaining_vector_hash.h
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = main

# Default target
all: $(EXECUTABLE)

# Link object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Compile .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)