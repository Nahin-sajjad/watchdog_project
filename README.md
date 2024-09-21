# Watchdog Application

## Overview

A watchdog application that monitors and manages specified processes on a Linux system. It dynamically reloads configuration changes and ensures configured processes are running.

## Features

- Monitors processes specified in a JSON configuration file.
- Dynamically reloads configuration when changes are detected.
- Automatically restarts processes if they stop or are killed.
- Encapsulates OS-specific API calls in a separate component (`NativeOSAPI`).

## Getting Started

### Prerequisites

- Linux system
- C++17 compatible compiler
- `nlohmann/json` library
- `pthread` library

### Building the Application

```bash
make
