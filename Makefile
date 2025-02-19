# Created by Ben Roberts 2024
CC = g++
CFLAGS = -Wall -g -UNDEBUG -MMD -MP

# The only source file
SOURCES = main.cpp
OBJECTS = main.o
DEPENDS = $(OBJECTS:.o=.d)

EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Compile main.cpp into main.o, generating a .d file tracking headers
main.o: main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Include the generated .d file if it exists
-include $(DEPENDS)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXECUTABLE)
