# Z16 Disassembler & Simulator
CSCE2303 Computer Organization and Assembly Language Programming (Spring 2025) - Project 1

Based on [Z16 ISA Specification](https://github.com/shalan/z16)

## Overview

This project is a C++ console app as a disassembler and a simulator for the [Z16 ISA](https://github.com/shalan/z16).

The program reads an assembled binary `.bin` file, prints the disassembled instructions and simulates their execution in an in-memory virtual memory and register file.

## Usage

The app can be used from console as follows:

`./Z16Simulator-vx.x-arch-os [-v] [-o <output_file>] <input_file>`

*You can easily download and use the prebuilt binaries from the repos the **GitHub Releases** page.*

### CLI Switches/Flags

- `<input_file>`: filename with the input written in the specified format below
- `-v` (optional): verbose output
- `-o <output_file>` (optional): filename to save the output to

### Accepted Input Files
The input file should be a binary file of a `.bin` extension pre-assembled with the [Z16 ISA](https://github.com/shalan/z16) assembler.

---

# For Developers

## Building from Source

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the source code using a C++ compiler (the project is `CMake`-dependent; `GCC` was used during developed period):

    ```bash
    cmake.exe --build cmake-build-profile_name --target Z16Simulator
    ```

   *Notice that you have to have CMake and a C++ compiler installed on your computer beforehand!*

   For release builds, [Zig](https://ziglang.org/) is used for more optimized and cross-compiled binaries (the `build.zig` file is already prepared in the repo)

    ```bash
    zig build --release
    ```    

   *Notice that you have to have the Zig compiler installed on your computer beforehand!*


4. Run the application:
   ```bash
   ./Z16Simulator [-v] [-o <output_file>] <input_file>
   ```

## Program Design & Architecture
Please head to the ['docs'](docs) folder for more information.

---

## Contributors

- [Mikhael Khalil](https://github.com/MikhaelMounay)
- [Kirollos Mounir](https://github.com/KirollosFady)
- [Nour Waleed](https://github.com/nourwaleedmo)
