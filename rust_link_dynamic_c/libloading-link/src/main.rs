mod lib_matrix;
use lib_matrix::Matrix;
use std::ffi::{c_char, CStr, CString};

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

/*
    Now lets implement some utils functions to use in main
*/

fn initialize_matrix(matrix: *mut Matrix, mut start_value: f64) {
    unsafe {
        assert!(!(*matrix).data.is_null(), "Matrix data is null");
        for i in 0..(*matrix).rows {
            let row_ptr = *((*matrix).data.offset(i as isize));
            assert!(!row_ptr.is_null(), "Matrix row is null");
            for j in 0..(*matrix).cols {
                *(row_ptr.offset(j as isize)) = start_value;
                start_value += 1.0;
            }
        }
    }
}

fn populate_matrix_random(matrix: *mut Matrix) {
    unsafe {
        for i in 0..(*matrix).rows {
            let row_ptr = *((*matrix).data.offset(i as isize));
            for j in 0..(*matrix).cols {
                *(row_ptr.offset(j as isize)) = fastrand::f64();
            }
        }
    }
}

fn pretty_print_matrix(matrix: *mut Matrix) {
    let name = c_string_to_rust_string(unsafe { (*matrix).name }).unwrap();
    println!("{}", name);
    print!("┌");
    unsafe {
        for _ in 0..(*matrix).cols - 1 {
            print!("          ");
        }
        println!("         ┐");
        for i in 0..(*matrix).rows {
            print!("│");
            let row_ptr = *((*matrix).data.offset(i as isize));
            for j in 0..(*matrix).cols {
                print!("{:8.3} ", *(row_ptr.offset(j as isize)));
            }
            println!(" │");
            if i < (*matrix).rows - 1 {
                print!("│");
                for _ in 0..(*matrix).cols - 1 {
                    print!("          ");
                }
                println!("         │");
            }
        }
        print!("└");
        for _ in 0..(*matrix).cols - 1 {
            print!("          ");
        }
    }
    println!("         ┘");
}

fn main() {
    let lm = lib_matrix::get_lib_matrix();
    let a = lm.matrix_create(2, 2, rust_string_to_c_string("A".to_string()));
    let b = lm.matrix_create(2, 2, rust_string_to_c_string("B".to_string()));

    initialize_matrix(a, 1.0);
    populate_matrix_random(b);

    println!("\nInitialized t_matrix A:\n");
    pretty_print_matrix(a);
    println!("\nInitialized t_matrix B:\n");
    pretty_print_matrix(b);

    let c = lm.matrix_mul(a, b, rust_string_to_c_string("A * B".to_string()));
    pretty_print_matrix(c);

    lm.matrix_destroy(a);
    lm.matrix_destroy(b);
    lm.matrix_destroy(c);
}
