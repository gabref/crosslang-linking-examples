use std::ffi::c_char;
use std::os::raw::c_double;
use std::sync::{Arc, Mutex, MutexGuard};

/*
    * Transalation of the C library interfaces to Rust
    typedef struct s_matrix
    {
        int		rows;
        int		cols;
        char	*name;
        double	**data;
    }			t_matrix;

    t_matrix	*matrix_create(int rows, int cols, char *name);
    t_matrix	*matrix_add(t_matrix *a, t_matrix *b, char *new_matrix_name);
    t_matrix	*matrix_sub(t_matrix *a, t_matrix *b, char *new_matrix_name);
    t_matrix	*matrix_mul(t_matrix *a, t_matrix *b, char *new_matrix_name);
    t_matrix	*matrix_transpose(t_matrix *matrix, char *new_matrix_name);
    void		matrix_destroy(t_matrix *matrix);
    void		matrix_print(t_matrix *matrix);
*/

// This tells rust to follow the same memory layout as the C struct
#[repr(C)]
pub struct Matrix {
    pub rows: i32,
    pub cols: i32,
    pub name: *mut c_char,
    pub data: *mut *mut c_double,
}

type MatrixCreate = unsafe extern "C" fn(i32, i32, *mut c_char) -> *mut Matrix;
type MatrixMul = unsafe extern "C" fn(*mut Matrix, *mut Matrix, *mut c_char) -> *mut Matrix;
type MatrixDestroy = unsafe extern "C" fn(*mut Matrix);

lazy_static::lazy_static! {
    pub static ref LIB_MATRIX: Arc<Mutex<LibMatrix>> = Arc::new(Mutex::new(unsafe { LibMatrix::new() }));
}

pub fn get_lib_matrix() -> MutexGuard<'static, LibMatrix> {
    LIB_MATRIX.lock().unwrap()
}

pub struct LibMatrix {
    library: libloading::Library,
}

impl LibMatrix {
    unsafe fn new() -> Self {
        let library_name = std::ffi::OsStr::new("../../libmatrix_c/build/libmatrix_c_dynamic.so");
        let library = libloading::Library::new(library_name).unwrap();
        Self { library }
    }

    pub fn matrix_create(&self, rows: i32, cols: i32, name: *mut c_char) -> *mut Matrix {
        unsafe {
            let func: libloading::Symbol<MatrixCreate> = self.library.get(b"matrix_create").unwrap();
            func(rows, cols, name)
        }
    }

    pub fn matrix_mul(&self, a: *mut Matrix, b: *mut Matrix, new_matrix_name: *mut c_char) -> *mut Matrix {
        unsafe {
            let func: libloading::Symbol<MatrixMul> = self.library.get(b"matrix_mul").unwrap();
            func(a, b, new_matrix_name)
        }
    }

    pub fn matrix_destroy(&self, matrix: *mut Matrix) {
        unsafe {
            let func: libloading::Symbol<MatrixDestroy> = self.library.get(b"matrix_destroy").unwrap();
            func(matrix)
        }
    }
}
