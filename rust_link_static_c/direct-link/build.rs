fn main() {
    // tell cargo where to find the built library
    println!("cargo:rustc-link-search=../../libmatrix_c/build");
    // tell cargo to link the built library
    println!("cargo:rustc-link-lib=static=matrix_c_static");
}
