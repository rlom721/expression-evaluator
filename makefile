# Made for specific directory organization
# compiler
CC := g++

# directory names!
SRCDIR := src
BUILDDIR := build
TESTDIR := test

# executable names
TARGET := bin/main  
TESTTARGET := bin/tester

# compiler flag vars
MAXERRORS := 3      # max num of errors to show in compiler

# SRCEXT := cpp         # src file extension ! DOESN'T WORK !
SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))   # patsubst pattern, replacement, text

# TESTSRCS := $(filter-out $(SRCDIR)/main.cpp, $(SOURCES)) $(shell find $(TESTDIR) -type f -name *.cpp)
# TESTOBJS := $(TESTSRCS:.cpp=.o) #$(filter-out $(BUILDDIR)/main.o, $(OBJECTS)) 

CFLAGS := -g -Wall -fmax-errors=$(MAXERRORS)
INC := -I include       # ensure all headers in include folder are accessible

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

run:
	@echo " Running executable main..."
	bin/./main

checkLeak:
	valgrind --leak-check=full --show-leak-kinds=all bin/./main

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(TESTTARGET)"; $(RM) -r $(BUILDDIR) $(TARGET) $(TESTTARGET)

.PHONY: clean
