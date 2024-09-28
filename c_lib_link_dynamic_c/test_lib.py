import ctypes

# Load the shared library
lib = ctypes.CDLL('./build/libmy_matrix.so')

# Define the Matrix structure as it is in C
class Matrix(ctypes.Structure):
    _fields_ = [("rows", ctypes.c_int),
                ("cols", ctypes.c_int),
                ("name", ctypes.c_char_p),
                ("data", ctypes.POINTER(ctypes.POINTER(ctypes.c_double)))]

# Define function prototypes to match the C functions
lib.matrix_create.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_char_p]
lib.matrix_create.restype = ctypes.POINTER(Matrix)

lib.matrix_destroy.argtypes = [ctypes.POINTER(Matrix)]
lib.matrix_destroy.restype = None

lib.matrix_mul.argtypes = [ctypes.POINTER(Matrix), ctypes.POINTER(Matrix), ctypes.c_char_p]
lib.matrix_mul.restype = ctypes.POINTER(Matrix)

lib.pretty_print_matrix.argtypes = [ctypes.POINTER(Matrix)]
lib.pretty_print_matrix.restype = None

lib.initialize_matrix.argtypes = [ctypes.POINTER(Matrix), ctypes.c_double]
lib.initialize_matrix.restype = None

lib.populate_matrix_random.argtypes = [ctypes.POINTER(Matrix)]
lib.populate_matrix_random.restype = None

# Helper functions to simplify usage
def create_matrix(rows, cols, name):
    matrix = lib.matrix_create(rows, cols, name.encode('utf-8'))
    return matrix

def destroy_matrix(matrix):
    lib.matrix_destroy(matrix)

def multiply_matrices(a, b, new_name):
    return lib.matrix_mul(a, b, new_name.encode('utf-8'))

def pretty_print(matrix):
    lib.pretty_print_matrix(matrix)

def initialize(matrix, start_value):
    lib.initialize_matrix(matrix, start_value)

def populate_random(matrix):
    lib.populate_matrix_random(matrix)

# Example usage
if __name__ == "__main__":
    rows, cols = 3, 3
    mata = create_matrix(rows, cols, "Matrix A")
    matb = create_matrix(rows, cols, "Matrix B")

    initialize(mata, 3)
    populate_random(matb)

    pretty_print(mata)
    pretty_print(matb)

    result_mul = multiply_matrices(mata, matb, "Matrix A * Matrix B")

    pretty_print(result_mul)

    destroy_matrix(mata)
    destroy_matrix(matb)
    destroy_matrix(result_mul)
