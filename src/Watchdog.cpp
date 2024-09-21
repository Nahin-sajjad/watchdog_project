#include "Watchdog.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <chrono>

using json = nlohmann::json;

Watchdog::Watchdog(const std::string& configFilePath)
    : configFilePath(configFilePath), running(false), lastConfigModifyTime(0) {}

Watchdog::~Watchdog() {
    stop();
}

void Watchdog::start() {
    running = true;
    loadConfig();
    configMonitorThread = std::thread(&Watchdog::monitorConfigChanges, this);
    processMonitorThread = std::thread(&Watchdog::monitorProcesses, this);
}

void Watchdog::stop() {
    running = false;
    if (configMonitorThread.joinable()) {
        configMonitorThread.join();
    }
    if (processMonitorThread.joinable()) {
        processMonitorThread.join();
    }
}

void Watchdog::loadConfig() {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        std::cerr << "Failed to open configuration file.\n";
        return;
    }

    json configJson;
    configFile >> configJson;

    std::unordered_map<std::string, json> newProcessesConfig;

    for (const auto& process : configJson["processes"]) {
        std::string name = process["name"];
        newProcessesConfig[name] = process;
        if (processesConfig.find(name) == processesConfig.end()) {
            handleProcess(process);
        }
    }

    // Handle removed processes
    for (auto it = processesConfig.begin(); it != processesConfig.end(); ) {
        if (newProcessesConfig.find(it->first) == newProcessesConfig.end()) {
            // Stop monitoring
            osApi.stopProcess(monitoredProcesses[it->first]);
            monitoredProcesses.erase(it->first);
            it = processesConfig.erase(it);
        } else {
            ++it;
        }
    }

    processesConfig = newProcessesConfig;
}

void Watchdog::monitorConfigChanges() {
    while (running) {
        reloadConfigIfChanged();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Watchdog::monitorProcesses() {
    while (running) {
        for (const auto& [name, config] : processesConfig) {
            pid_t pid = monitoredProcesses[name];
            if (!osApi.isProcessRunning(pid)) {
                handleProcess(config);
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void Watchdog::handleProcess(const json& processConfig) {
    std::string command = processConfig["command"];
    std::vector<std::string> args = processConfig["args"].get<std::vector<std::string>>();

    pid_t pid = osApi.startProcess(command, args);
    if (pid != -1) {
        monitoredProcesses[processConfig["name"]] = pid;
        // Log process start
    } else {
        // Log error
    }
}

void Watchdog::reloadConfigIfChanged() {
    struct stat fileStat;
    if (stat(configFilePath.c_str(), &fileStat) != 0) {
        std::cerr << "Failed to get file status.\n";
        return;
    }

    if (fileStat.st_mtime != lastConfigModifyTime) {
        lastConfigModifyTime = fileStat.st_mtime;
        loadConfig();
        // Log config reload
    }
}