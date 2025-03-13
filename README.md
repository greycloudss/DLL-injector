# DLL Injector

## Overview
This project is a simple DLL injector designed for educational purposes, primarily for students and professionals interested in red teaming and penetration testing. It demonstrates process manipulation in Windows, specifically the method of injecting a dynamic-link library (DLL) into another running process.

## Features
- Retrieves the process ID (PID) of a running executable.
- Allocates memory within the target process.
- Writes the DLL path into the allocated memory.
- Creates a remote thread to load the DLL into the target process.
- Includes basic error handling for process manipulation failures.

## Disclaimer
**This tool is strictly for educational and research purposes. Unauthorized use against any system without permission is illegal and may result in legal consequences. Always ensure compliance with local laws and obtain proper authorization before using such tools.**

## Requirements
- Windows OS
- C++ Compiler (MinGW, MSVC, or similar)
- Basic understanding of Windows API and process injection

## Installation
Clone the repository and build the project using any compatible C++ compiler.
```sh
$ git clone <repository_url>
$ cd <repository_folder>
$ g++ -o injector Source.cpp
```

## Usage
Run the executable from the command line, providing the process name and the DLL path:
```sh
$ injector.exe <process_name> <dll_path>
```
### Example:
```sh
$ injector.exe notepad.exe C:\path\to\your.dll
```
This will attempt to inject `your.dll` into the running instance of `notepad.exe`.

## Code Structure
### `header.h`
- Defines the `injector` class.
- Implements functions for retrieving process ID, allocating memory, writing to the process, and injecting the DLL.

### `Source.cpp`
- Handles command-line arguments and initializes the injection process.

## Error Codes
- `1` - Process not found.
- `2` - Failed to open target process.
- `3` - Memory allocation failed.
- `5` - Writing DLL path into process memory failed.
- `6` - Failed to create remote thread.

## Learning Resources
- [Windows API Documentation](https://docs.microsoft.com/en-us/windows/win32/api/)
- [DLL Injection Techniques](https://www.ired.team/miscellaneous-reversing-forensics/windows-kernel-internals/process-injection-techniques)
- [Process Memory Manipulation](https://www.geoffchappell.com/studies/windows/win32/memory/process/index.htm)

## Author
This project was developed for academic and research purposes. Contributions and suggestions are welcome.

