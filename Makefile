vpath %.c src devices/src devices/hmo_voltage_sensor/src tests tests/init
vpath %.h include devices/include devices/hmo_voltage_sensor/include

# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Iinclude -Idevices/include -Idevices/hmo_voltage_sensor/include -Itests
LDLIBS_CPPUTEST ?= -L$(CPPUTEST_LIB_DIR) -L. -lCppUTest -lCppUTestExt

# Directories
SRCDIR = src
DEVICEDIR = devices
TESTDIR = tests
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj


# Device-specific source files
DEVICE_SOURCES = $(wildcard $(DEVICEDIR)/*/src/*.c)

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(DEVICEDIR)/src/*.c) $(DEVICE_SOURCES)

# Test source files
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp) $(wildcard $(TESTDIR)/*/*.cpp)
BUILDDIR = build
# Object files
OBJECTS = $(patsubst %.c, $(OBJDIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(patsubst %.cpp, $(OBJDIR)/%.o, $(TEST_SOURCES))

# Test executable
TEST_EXECUTABLE = $(BUILDDIR)/AllTests

# Create object directory if it doesn't exist
$(shell mkdir -p $(OBJDIR) $(OBJDIR)/$(SRCDIR) $(OBJDIR)/$(DEVICEDIR)/src $(OBJDIR)/$(DEVICEDIR)/hmo_voltage_sensor/src $(OBJDIR)/$(TESTDIR) $(OBJDIR)/$(TESTDIR)/init $(BUILDDIR))

# Default target
all: $(OBJECTS) $(TEST_EXECUTABLE)

# Rule to build object files
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

# Rule to build test executable
$(TEST_EXECUTABLE): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CFLAGS) $(LDLIBS_CPPUTEST) $(OBJECTS) $(TEST_OBJECTS) -o $@

# Clean up build files
clean:
	rm -rf $(BUILDDIR) $(TEST_EXECUTABLE)

.PHONY: all clean
