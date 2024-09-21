#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <string>
#include <unordered_map>
#include <thread>
#include <atomic>
#include <nlohmann/json.hpp>
#include "NativeOSAPI.h"

class Watchdog {
public:
    Watchdog(const std::string& configFilePath);
    ~Watchdog();
    void start();
    void stop();

private:
    void loadConfig();
    void monitorConfigChanges();
    void monitorProcesses();
    void handleProcess(const nlohmann::json& processConfig);
    void reloadConfigIfChanged();

    std::string configFilePath;
    std::atomic<bool> running;
    std::thread configMonitorThread;
    std::thread processMonitorThread;
    std::unordered_map<std::string, nlohmann::json> processesConfig;
    std::unordered_map<std::string, pid_t> monitoredProcesses;
    NativeOSAPI osApi;
    time_t lastConfigModifyTime;
};

#endif // WATCHDOG_H