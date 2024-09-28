fn main() {
    // tell cargo where to find the built library
    println!("cargo:rustc-link-search=../../libmatrix_c/build");
    // tell cargo to link the built library
    println!("cargo:rustc-link-lib=matrix_c_dynamic");
}
