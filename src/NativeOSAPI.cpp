#include "NativeOSAPI.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>

pid_t NativeOSAPI::startProcess(const std::string& command, const std::vector<std::string>& args) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        char* argv[args.size() + 2];
        argv[0] = const_cast<char*>(command.c_str());
        for (size_t i = 0; i < args.size(); ++i) {
            argv[i + 1] = const_cast<char*>(args[i].c_str());
        }
        argv[args.size() + 1] = nullptr;
        execvp(command.c_str(), argv);
        exit(EXIT_FAILURE); // Should not reach here
    } else if (pid > 0) {
        // Parent process
        return pid;
    } else {
        // Fork failed
        std::cerr << "Failed to fork process.\n";
        return -1;
    }
}

bool NativeOSAPI::isProcessRunning(pid_t pid) {
    if (kill(pid, 0) == 0) {
        return true;
    }
    return false;
}

void NativeOSAPI::stopProcess(pid_t pid) {
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
}