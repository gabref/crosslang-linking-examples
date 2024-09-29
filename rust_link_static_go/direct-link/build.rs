use std::env;

fn main() {
    let architecture =
        env::var("CARGO_CFG_TARGET_ARCH").expect("Failed to get target architecture");
    let target = env::var("TARGET").expect("Failed to get target");

    // get the name of the output directory
    let out_dir = if target.contains("windows") {
        let arch_dir = if architecture == "x86" { "x86" } else { "x64" };
        format!("win/{}", arch_dir)
    } else {
        let arch_dir = if architecture == "x86" { "x86" } else { "x64" };
        format!("lin/{}", arch_dir)
    };

    // set the output directory
    // let out_dir = format!("../../libmatrix_go/build/{}", out_dir);

    // when using cross we need to copy the libraries to this folder project
    let out_dir = format!("build/{}", out_dir);

    // tell cargo where to find the built library
    println!("cargo:rustc-link-search={}", out_dir);

    // tell cargo to link the built library
    println!("cargo:rustc-link-lib=static=matrix_go_static");
    // workaround for windows
    if target.contains("windows") {
        println!("cargo:rustc-link-lib=static=workaround");
    };
}
