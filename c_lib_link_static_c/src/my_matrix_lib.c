#include "../../libmatrix_c/inc/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

t_matrix	*wrapper_matrix_create(int rows, int cols, char *name)
{
	t_matrix	*matrix;

	matrix = matrix_create(rows, cols, name);
	if (matrix == NULL)
	{
		printf("Error: matrix_create() failed\n");
		exit(1);
	}
	return (matrix);
}

t_matrix	*wrapper_matrix_mul(t_matrix *a, t_matrix *b, char *new_matrix_name)
{
	t_matrix	*matrix;

	matrix = matrix_mul(a, b, new_matrix_name);
	if (matrix == NULL)
	{
		printf("Error: matrix_mul() failed\n");
		exit(1);
	}
	return (matrix);
}

// Function to initialize a matrix with specific values
void	initialize_matrix(t_matrix *matrix, double start_value)
{
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; j < matrix->cols; j++)
			matrix->data[i][j] = start_value++;
}

// Function to populate a matrix with random values between 0 and 1
void	populate_matrix_random(t_matrix *matrix)
{
	srand(time(NULL)); // Seed for random number generation
	for (int i = 0; i < matrix->rows; i++)
		for (int j = 0; j < matrix->cols; j++)
			matrix->data[i][j] = (double)rand() / RAND_MAX;
}

void	pretty_print_matrix(const t_matrix *matrix)
{
	printf("%s\n", matrix->name);
	printf("┌");
	for (int j = 0; j < matrix->cols - 1; j++)
		printf("          ");
	printf("         ┐\n");
	for (int i = 0; i < matrix->rows; i++)
	{
		printf("│");
		for (int j = 0; j < matrix->cols; j++)
			printf("%8.3f ", matrix->data[i][j]);
		printf("  │\n");
		if (i < matrix->rows - 1)
		{
			printf("│");
			for (int j = 0; j < matrix->cols - 1; j++)
				printf("          ");
			printf("         │\n");
		}
	}
	printf("└");
	for (int j = 0; j < matrix->cols - 1; j++)
		printf("          ");
	printf("         ┘\n");
}
