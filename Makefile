vpath %.c src
vpath %.h include

BUILD_DIR = build

# Setup variables for the module
SRC_DIR ?= src
INCLUDE_DIR ?= include

MODULE_NAME ?= voltage_sensor

sources = $(wildcard $(SRC_DIR)/*.c)
includes = $(wildcard $(INCLUDE_DIR)/*.h)
objects = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(sources))
TARGET ?= $(BUILD_DIR)/lib$(MODULE_NAME).a

CFLAGS += -Iinclude


# Setup variables for the tests
TEST_SRC_DIR ?= tests

# Find all .cpp files in the test source directory and its subdirectories
test_sources = $(shell find $(TEST_SRC_DIR) -name '*.cpp')
test_objects = $(patsubst $(TEST_SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(test_sources))

# Extract the base name for the test target
test_root_sources = $(shell find $(TEST_SRC_DIR) -maxdepth 1 -name '*.cpp')
test_base_name = $(basename $(notdir $(test_root_sources)))
TEST_TARGET ?= $(BUILD_DIR)/$(test_base_name)

CPPUTEST_HOME ?= ../cpputest
CPPUTEST_LIB_DIR ?= $(CPPUTEST_HOME)/lib
LDLIBS_CPPUTEST ?= -L$(CPPUTEST_LIB_DIR) -L. -lCppUTest -lCppUTestExt
CXXFLAGS += -Iinclude

# Define a function to create the required directories
define make-build-dir
  @mkdir -p $(dir $@)
endef

.PHONY: all clean run_tests

# Default target
all: $(TEST_TARGET) $(TARGET) run_tests

# Module targets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(make-build-dir)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(objects) | $(BUILD_DIR)
	$(AR) rv $@ $(objects)


# Test targets
$(BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TEST_TARGET): $(test_objects) $(TARGET) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS_CPPUTEST) -o $@


run_tests:
	$(TEST_TARGET)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	
clean:
	rm $(objects) $(test_objects) $(TARGET) $(TEST_TARGET)



# Include generated dependencies
-include $(objects:.o=.d)
-include $(test_objects:.o=.d)
