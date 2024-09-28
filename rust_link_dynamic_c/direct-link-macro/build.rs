fn main() {
    // tell cargo where to find the built library
    println!("cargo:rustc-link-search=../../libmatrix_c/build");
}
