# Linking Rust with a Static Golang Library

This is a simple example of how to link Rust with a static Golang library. The Golang library is compiled with the `-buildmode=c-archive` flag, which creates a static library that can be linked with Rust.

## Requirements

First of all, of course you need rust installed, refer to the [rust official website](https://www.rust-lang.org/tools/install) for instructions on how to install it.

You also need to have the Golang compiler installed. You can download it from the [official website](https://golang.org/dl/).

You will also need some dependencies to build the Golang library. You can install them by running the following command:

```bash
./install_requirements.sh
```

This script will install mingw so that we can compile the Golang library for Windows. Also it will install the 

## Building the Golang Library and Rust code

To build the Golang library, run the following command:

```bash
./build.sh
```

This command will build the Golang library for Linux and Windows in the `../../libmatrix_go` directory and will copy all the necessary files to the build directory. 

After, it will build the `windows_workaround.c` file, which is necessary to compile the Rust code on Windows. And finally, it will compile the Rust code using cross-compilation for Windows and Linux.

## Run

You can run the linux code with a simple `cargo run`, and for the windows, you can either transfer the file to a windows machine or use wine64:

```bash
sudo apt update && sudo apt install wine64
wine target/x86_64-pc-windows-gnu/debug/direct-link.exe
```
