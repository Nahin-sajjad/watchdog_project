CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall
LDFLAGS = -lgtest -lgtest_main -lpthread
INCLUDES = -I./include
SOURCES = src/main.cpp src/Watchdog.cpp src/NativeOSAPI.cpp
TEST_SOURCES = tests/unit_tests.cpp tests/integration_tests.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TARGET = watchdog
TEST_TARGET = run_tests

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET) src/*.o tests/*.o
