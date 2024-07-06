#ifndef MATRIX_H
# define MATRIX_H

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

#endif
