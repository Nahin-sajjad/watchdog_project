# Watchdog Project

## Overview

The **Watchdog System** is a Linux-based tool designed to monitor and manage processes listed in a configuration file. It ensures the processes stay active by periodically checking their status and restarting them if necessary. Additionally, it monitors a foreground application, ensuring that it stays on top of all other windows.

### Features

- **Task 1**: Monitors background processes, automatically restarting them if they crash or stop.
- **Task 2**: Monitors a foreground process, keeping it on top of all other applications.
- **Dynamic configuration reloading**: Automatically applies configuration changes when the configuration file is modified.
- **Logging**: Logs all events and actions for future analysis.

---

## Prerequisites

Before you start, make sure you have the following installed on your system:

- **Linux OS**
- **g++**: GNU C++ compiler
- **CMake**: For building Google Test
- **Google Test**: Unit testing framework
- **xdotool**: For managing the foreground process
- **nlohmann/json**: JSON parser for C++ (installed via `nlohmann-json3-dev`)

---

## Installation Guide

### Step 1: Install Necessary Dependencies

#### 1.1. Install `g++` and `CMake`

```bash
sudo apt-get update
sudo apt-get install build-essential cmake -y
sudo apt-get install libgtest-dev -y

cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp *.a /usr/lib

sudo apt-get install xdotool -y
sudo apt-get install nlohmann-json3-dev -y
```

### Step 2: Clone and Build the Project

```bash
git clone https://github.com/Nahin-sajjad/watchdog_project.git
cd watchdog_project
```

### Step 3: Build the Project

Use the Makefile to compile the project.

```bash
make
```

### Step 4: Running the Watchdog

Once the project is built and configured, you can run the watchdog program:

```bash
./watchdog
```