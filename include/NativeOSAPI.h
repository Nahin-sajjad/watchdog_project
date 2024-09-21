#ifndef NATIVE_OS_API_H
#define NATIVE_OS_API_H

#include <string>
#include <vector>
#include <sys/types.h>

class NativeOSAPI {
public:
    pid_t startProcess(const std::string& command, const std::vector<std::string>& args);
    bool isProcessRunning(pid_t pid);
    void stopProcess(pid_t pid);

private:
    // Internal helper methods if needed
};

#endif // NATIVE_OS_API_H