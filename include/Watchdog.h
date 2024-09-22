#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <string>
#include <unordered_map>
#include <thread>
#include <atomic>
#include <nlohmann/json.hpp>
#include "NativeOSAPI.h"

// Alias for JSON data type
using json = nlohmann::json;

class Watchdog {
public:
    Watchdog(const std::string& configFilePath);
    ~Watchdog();
    void start();
    void stop();

private:
    // Core functions for process monitoring and configuration
    void loadConfig();
    void monitorConfigChanges();
    void monitorProcesses();
    void handleProcess(const json& processConfig);
    void reloadConfigIfChanged();

    // Foreground process-related methods
    void bringForeground(pid_t pid);
    
    // Configuration file path and process details
    std::string configFilePath;

    // Process control and monitoring
    std::atomic<bool> running;
    std::thread configMonitorThread;
    std::thread processMonitorThread;
    std::thread foregroundMonitorThread;  // Thread for monitoring foreground process

    // Process and configuration tracking
    std::unordered_map<std::string, json> processesConfig;
    std::unordered_map<std::string, pid_t> monitoredProcesses;
    NativeOSAPI osApi;

    // Time tracking for config changes
    time_t lastConfigModifyTime;

    // Foreground process tracking
    json foregroundProcessConfig;   // Stores the foreground process configuration
    pid_t foregroundPid;            // Tracks the PID of the foreground process
};

#endif // WATCHDOG_H
