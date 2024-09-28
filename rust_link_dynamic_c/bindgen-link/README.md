# Rust and C dynamic library with bindgen

This is a simple example of how to use a dynamic library written in C from Rust. The C library is a simple matrix library that provides basic operations on matrices. The Rust program uses the dynamic library to perform some operations on matrices.

## Usage

To run this program, you need to specify the path of the dynamic library:

```bash
LD_LIBRARY_PATH=../../libmatrix_c/build cargo run
```

That means of course that before anything else, you need to build the dynamic library. You can do that by running the following command:

```bash
cd ../../libmatrix_c
make
cd -
```
