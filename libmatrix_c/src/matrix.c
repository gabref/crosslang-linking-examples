#include "../inc/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static double	**allocate_matrix_data(int rows, int cols)
{
	double	**data;

	data = (double **)malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++)
		data[i] = (double *)malloc(cols * sizeof(double));
	return (data);
}

/* allocates memory for a matrix with the given number of rows and columns */
t_matrix	*matrix_create(int rows, int cols, char *name)
{
	t_matrix	*matrix;

	matrix = (t_matrix *)malloc(sizeof(t_matrix));
	matrix->rows = rows;
	matrix->cols = cols;
	matrix->name = strdup(name);
	matrix->data = allocate_matrix_data(rows, cols);
	return (matrix);
}

/* frees the memory allocated for a matrix */
void	matrix_destroy(t_matrix *matrix)
{
	if (!matrix)
		return ;
	for (int i = 0; i < matrix->rows; i++)
		free(matrix->data[i]);
	free(matrix->data);
	free(matrix->name);
	free(matrix);
}

/* adds two matrices */
t_matrix	*matrix_add(t_matrix *a, t_matrix *b, char *new_matrix_name)
{
	t_matrix	*result;

	if (a->rows != b->rows || a->cols != b->cols)
		return (NULL); // Incompatible dimensions
	result = matrix_create(a->rows, a->cols, new_matrix_name);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < a->cols; j++)
			result->data[i][j] = a->data[i][j] + b->data[i][j];
	return (result);
}

/* subtracts two matrices */
t_matrix	*matrix_sub(t_matrix *a, t_matrix *b, char *new_matrix_name)
{
	t_matrix	*result;

	if (a->rows != b->rows || a->cols != b->cols)
		return (NULL); // Incompatible dimensions
	result = matrix_create(a->rows, a->cols, new_matrix_name);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < a->cols; j++)
			result->data[i][j] = a->data[i][j] - b->data[i][j];
	return (result);
}

/* multiplies two matrices */
t_matrix	*matrix_mul(t_matrix *a, t_matrix *b, char *new_matrix_name)
{
	t_matrix	*result;

	if (a->cols != b->rows)
		return (NULL); // Incompatible dimensions
	result = matrix_create(a->rows, b->cols, new_matrix_name);
	for (int i = 0; i < a->rows; i++)
		for (int j = 0; j < b->cols; j++)
		{
			result->data[i][j] = 0;
			for (int k = 0; k < a->cols; k++)
				result->data[i][j] += a->data[i][k] * b->data[k][j];
		}
	return (result);
}

/* transposes a matrix */
t_matrix	*matrix_transpose(t_matrix *matrix, char *new_matrix_name)
{
	t_matrix	*result;

	result = matrix_create(matrix->cols, matrix->rows, new_matrix_name);
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; j < matrix->cols; j++)
			result->data[j][i] = matrix->data[i][j];
	return (result);
}

/* prints the matrix */
void	matrix_print(t_matrix *matrix)
{
	printf(" %s\n", matrix->name);
	for (int i = 0; i < matrix->rows; i++)
	{
		for (int j = 0; j < matrix->cols; j++)
			printf("%8.3f ", matrix->data[i][j]);
		printf("\n");
	}
}
