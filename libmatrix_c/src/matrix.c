#include "../inc/matrix.h"
#include <stdio.h>
#include <stdlib.h>

static double	**allocate_matrix_data(size_t rows, size_t cols)
{
	double	**data;

	data = (double **)malloc(rows * sizeof(double *));
	for (size_t i = 0; i < rows; i++)
		data[i] = (double *)malloc(cols * sizeof(double));
	return (data);
}

t_matrix	*matrix_create(size_t rows, size_t cols)
{
	t_matrix	*matrix;

	matrix = (t_matrix *)malloc(sizeof(t_matrix));
	matrix->rows = rows;
	matrix->cols = cols;
	matrix->data = allocate_matrix_data(rows, cols);
	return (matrix);
}

void	matrix_destroy(t_matrix *matrix)
{
	if (!matrix)
		return ;
	for (size_t i = 0; i < matrix->rows; i++)
		free(matrix->data[i]);
	free(matrix->data);
	free(matrix);
}

t_matrix	*matrix_add(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;

	if (a->rows != b->rows || a->cols != b->cols)
		return (NULL); // Incompatible dimensions
	result = matrix_create(a->rows, a->cols);
	for (size_t i = 0; i < a->rows; i++)
		for (size_t j = 0; j < a->cols; j++)
			result->data[i][j] = a->data[i][j] + b->data[i][j];
	return (result);
}

t_matrix	*matrix_sub(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;

	if (a->rows != b->rows || a->cols != b->cols)
		return (NULL); // Incompatible dimensions
	result = matrix_create(a->rows, a->cols);
	for (size_t i = 0; i < a->rows; i++)
		for (size_t j = 0; j < a->cols; j++)
			result->data[i][j] = a->data[i][j] - b->data[i][j];
	return (result);
}

t_matrix	*matrix_mul(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;

	if (a->cols != b->rows)
		return (NULL); // Incompatible dimensions
	result = matrix_create(a->rows, b->cols);
	for (size_t i = 0; i < a->rows; i++)
		for (size_t j = 0; j < b->cols; j++)
		{
			result->data[i][j] = 0;
			for (size_t k = 0; k < a->cols; k++)
				result->data[i][j] += a->data[i][k] * b->data[k][j];
		}
	return (result);
}

t_matrix	*matrix_transpose(t_matrix *matrix)
{
	t_matrix	*result;

	result = matrix_create(matrix->cols, matrix->rows);
	for (size_t i = 0; i < matrix->rows; i++)
		for (size_t j = 0; j < matrix->cols; j++)
			result->data[j][i] = matrix->data[i][j];
	return (result);
}

void	matrix_print(t_matrix *matrix)
{
	for (size_t i = 0; i < matrix->rows; i++)
	{
		for (size_t j = 0; j < matrix->cols; j++)
			printf("%8.3f ", matrix->data[i][j]);
		printf("\n");
	}
}
