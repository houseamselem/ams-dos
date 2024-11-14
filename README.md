# AMS-DOS

**The Advanced Microcontroller System - DOS for Arduino**

AMS-DOS is a lightweight, efficient operating system designed specifically for Arduino microcontrollers. Built to maximize the potential of limited resources, AMS-DOS provides a structured environment for managing tasks, memory, and peripherals. This OS enables Arduino enthusiasts and developers to organize and execute complex programs on simple hardware, bringing multi-tasking and a more structured development approach to the Arduino platform.

### Key Features of AMS-DOS

1. **Basic Task Scheduler**  
   - Supports cooperative multitasking, allowing multiple tasks to run in sequence without interruption.
   - Provides delay and timing functions to schedule task execution.

2. **Memory Management**  
   - Allocates and deallocates memory dynamically to optimize limited SRAM usage.
   - Includes memory monitoring tools to help developers track and manage memory use efficiently.

3. **File System Support**  
   - Supports basic file management on connected SD cards, allowing file creation, reading, writing, and deletion.
   - Enables the storage and retrieval of data for persistent applications.

4. **Peripheral Management**  
   - Provides built-in drivers for common peripherals (e.g., UART, I2C, SPI, and GPIO management).
   - Simplifies interfacing with connected devices like sensors, displays, and communication modules.

5. **Command Line Interface (CLI)**  
   - Offers a simple CLI that can be accessed over serial communication for debugging and direct control of the Arduino.
   - Commands include system info, memory status, task listing, and file management.

6. **Real-Time Clock (RTC) Integration**  
   - Supports integration with RTC modules for time-based tasks and data logging.
   - Allows scheduling of tasks based on real-world time.

7. **Inter-Task Communication**  
   - Provides basic message-passing functionality for tasks to communicate and synchronize with each other.

8. **Debugging Tools**  
   - Includes debugging functions like logging, error tracking, and system diagnostics over serial output.
   - Helps developers monitor task execution, performance, and system status.

9. **Power Management**  
   - Optimizes power usage by enabling sleep modes and power-saving features, extending battery life for mobile applications.
   - Manages CPU cycles to reduce power usage during low-demand periods.

10. **Basic Networking Support**  
    - Compatible with Wi-Fi and Bluetooth modules (such as ESP8266, ESP32) for basic networking tasks.
    - Enables sending and receiving data over networks for IoT applications.

### AMS-DOS Benefits

AMS-DOS is built for developers who want more control and efficiency in their Arduino projects. By providing the essential features of an operating system, AMS-DOS allows for more structured and scalable programs, making Arduino applications more robust, reliable, and ready for real-world deployment. Whether it’s a complex robotics system or a simple sensor logger, AMS-DOS brings a new level of organization and capability to Arduino projects.