#include "../../libmatrix_c/inc/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
		printf(" │\n");
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

int	main(void)
{
	t_matrix	*A;
	t_matrix	*B;
	t_matrix	*C;

	// Create two 2x2 matrices
	A = matrix_create(2, 2, "A");
	B = matrix_create(2, 2, "B");

	// Initialize matrices with specific values
	initialize_matrix(A, 1.0);
	populate_matrix_random(B);

	// Print initialized matrices
	printf("\nInitialized t_matrix A:\n\n");
	pretty_print_matrix(A);
	printf("\nInitialized t_matrix B:\n\n");
	pretty_print_matrix(B);

	C = matrix_mul(A, B, "A * B");
	pretty_print_matrix(C);

	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);
	return (0);
}
