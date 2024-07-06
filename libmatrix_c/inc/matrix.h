#ifndef MATRIX_H
# define MATRIX_H

# include <stddef.h>

typedef struct s_matrix
{
	size_t	rows;
	size_t	cols;
	double	**data;
}			t_matrix;

/* allocates memory for a matrix with the given number of rows and columns */
t_matrix	*matrix_create(size_t rows, size_t cols);
/* adds two matrices */
t_matrix	*matrix_add(t_matrix *a, t_matrix *b);
/* subtracts two matrices */
t_matrix	*matrix_sub(t_matrix *a, t_matrix *b);
/* multiplies two matrices */
t_matrix	*matrix_mul(t_matrix *a, t_matrix *b);
/* transposes a matrix */
t_matrix	*matrix_transpose(t_matrix *matrix);
/* frees the memory allocated for a matrix */
void		matrix_destroy(t_matrix *matrix);
/* prints the matrix */
void		matrix_print(t_matrix *matrix);

#endif
