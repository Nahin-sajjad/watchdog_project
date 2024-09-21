#include "Watchdog.h"
#include "gtest/gtest.h"
#include <fstream>

// Integration test for the complete workflow
class WatchdogIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a config file for the integration test
        std::ofstream configFile("integration_config.json");
        configFile << R"({
            "watchdog": {
                "monitor_interval": 5,
                "processes": [
                    {
                        "name": "TestIntegrationProcess",
                        "cmd": "/usr/bin/echo",
                        "args": ["IntegrationProcess"],
                        "start_delay": 1,
                        "restart_on_failure": true
                    }
                ]
            }
        })";
        configFile.close();

        watchdog = new Watchdog("integration_config.json");
    }

    void TearDown() override {
        delete watchdog;
        remove("integration_config.json");
    }

    Watchdog* watchdog;
};

// Test end-to-end process monitoring and restarting
TEST_F(WatchdogIntegrationTest, MonitorAndRestartTest) {
    watchdog->start();  // Start the watchdog
    
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Wait for process to start
    ASSERT_TRUE(watchdog->processes["TestIntegrationProcess"].pid > 0);  // Check if process is running

    // Simulate process failure
    pid_t pid = watchdog->processes["TestIntegrationProcess"].pid;
    kill(pid, SIGKILL);  // Kill the process to simulate a crash
    
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Allow time for restart
    ASSERT_NE(watchdog->processes["TestIntegrationProcess"].pid, pid);  // Ensure the process was restarted
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
