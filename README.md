# Metronerm

A command-line metronome application built in C++ using the `libao` library for audio output. This tool is designed for musicians and performers who need a reliable, lightweight metronome to keep time during practice.

## Usage
```bash
./Metronerm <bpm>               #BPM (120,200, and etc.) 
./Metronerm -h, --help          #help menu
```

## Prerequisites

To build and run this application, you need:

- **CMake:** For building the project.
- **C++ Compiler:** Compatible with C++17 or newer.
- **libao:** For audio output. Ensure the `libao` library is installed on your system.

### Installing `libao`
For **Debian/Ubuntu**:
```bash
sudo apt-get install libao-dev
```
For **MacOs**:
```bash
brew install libao
```

### Building Metronerm
`The CMakeLists.txt in this project is created for MacOs. If you are on Linux or Windows, please specify the local path to your Libao library and update the CMakeLists.txt file before building.` 
Once you have the prerequisites, you are ready to build your own copy of Metronerm:
```bash
cmake .
make
./Metronerm 120         #Run it! 
```

### Happy Playing :)
