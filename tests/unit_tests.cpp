#include "Watchdog.h"
#include "gtest/gtest.h"
#include <fstream>

// Setup the Watchdog object for testing
class WatchdogTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary config file for testing
        std::ofstream configFile("test_config.json");
        configFile << R"({
            "watchdog": {
                "monitor_interval": 5,
                "processes": [
                    {
                        "name": "TestProcess",
                        "cmd": "/usr/bin/echo",
                        "args": ["TestProcessRunning"],
                        "start_delay": 1,
                        "restart_on_failure": true
                    }
                ]
            }
        })";
        configFile.close();
        
        watchdog = new Watchdog("test_config.json");
    }

    void TearDown() override {
        delete watchdog;
        remove("test_config.json");
    }

    Watchdog* watchdog;
};

// Test configuration loading
TEST_F(WatchdogTest, LoadConfigTest) {
    watchdog->loadConfig();
    ASSERT_FALSE(watchdog->processes.empty());
    ASSERT_EQ(watchdog->processes.size(), 1);  // We have 1 process in the config file
    ASSERT_EQ(watchdog->processes["TestProcess"].name, "TestProcess");
}

// Test if process is started
TEST_F(WatchdogTest, StartProcessTest) {
    watchdog->start();
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Wait for process to start
    ASSERT_TRUE(watchdog->processes["TestProcess"].pid > 0);  // Check if PID is assigned
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
