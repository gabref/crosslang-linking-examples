use std::ffi::{c_char, CStr, CString};

extern "C" {
    fn Add(a: i32, b: i32) -> i32;
    fn Multiply(a: i32, b: i32) -> i32;
    fn Concat(a: *const c_char, b: *const c_char) -> *mut c_char;
    fn Repeat(s: *const c_char, n: i32) -> *mut c_char;
}

fn c_string_to_rust_string(c_string: *mut c_char) -> Option<String> {
    if c_string.is_null() {
        return None;
    }
    let cstr_input = unsafe { CStr::from_ptr(c_string) };
    match cstr_input.to_str() {
        Ok(s) => Some(s.to_owned()),
        Err(_) => None,
    }
}

fn rust_string_to_c_string(rust_string: String) -> *mut c_char {
    let cstr_output = CString::new(rust_string).unwrap();
    cstr_output.into_raw()
}

fn main() {
    println!("\nCalling C functions from Rust\n\n");

    let a = 10;
    let b = 20;
    let result = unsafe { Add(a, b) };
    println!("{} + {} =\t{}\n", a, b, result);

    let result = unsafe { Multiply(a, b) };
    println!("{} * {} =\t{}\n", a, b, result);

    let a = rust_string_to_c_string(String::from("Hello, "));
    let b = rust_string_to_c_string(String::from("World!"));
    let result = unsafe { Concat(a, b) };
    let result = c_string_to_rust_string(result).unwrap();
    println!("Hello + World =\t{}\n", result);

    let s = CString::new("hello ").unwrap();
    let n = 3;
    let result = unsafe { Repeat(s.as_ptr(), n) };
    let result = c_string_to_rust_string(result).unwrap();
    println!("hello * {}\t{}\n", n, result);
}
