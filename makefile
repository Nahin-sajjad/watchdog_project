CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall -I./include
LDFLAGS = -lgtest -lgtest_main -lpthread
INCLUDES = -I./include
SOURCES = src/main.cpp src/Watchdog.cpp src/NativeOSAPI.cpp
TEST_SOURCES = tests/unit_tests.cpp tests/integration_tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TARGET = watchdog
TEST_TARGET = run_tests

# Default target for building the main executable
all: $(TARGET)

# Rule for building the main target (watchdog executable)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule for building the test executable
test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule for compiling .cpp files into .o object files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule for compiling test .cpp files into .o object files
tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up all the compiled object files and binaries
clean:
	rm -f $(TARGET) $(TEST_TARGET) src/*.o tests/*.o
