#include "Watchdog.h"

int main() {
    Watchdog watchdog("config/processes.json");
    watchdog.start();

    // Keep the main thread alive
    while (true) {
        // You can add a mechanism to exit the loop if needed
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    watchdog.stop();
    return 0;
}
