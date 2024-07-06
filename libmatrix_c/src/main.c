#include "../inc/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to initialize a matrix with specific values
void	initialize_matrix(t_matrix *matrix, double start_value)
{
	for (size_t i = 0; i < matrix->rows; i++)
		for (size_t j = 0; j < matrix->cols; j++)
			matrix->data[i][j] = start_value++;
}

// Function to populate a matrix with random values between 0 and 1
void	populate_matrix_random(t_matrix *matrix)
{
	srand(time(NULL)); // Seed for random number generation
	for (size_t i = 0; i < matrix->rows; i++)
		for (size_t j = 0; j < matrix->cols; j++)
			matrix->data[i][j] = (double)rand() / RAND_MAX;
}

void	pretty_print_matrix(const t_matrix *matrix)
{
	printf("┌");
	for (size_t j = 0; j < matrix->cols - 1; j++)
		printf("          ");
	printf("         ┐\n");
	for (size_t i = 0; i < matrix->rows; i++)
	{
		printf("│");
		for (size_t j = 0; j < matrix->cols; j++)
			printf("%8.3f ", matrix->data[i][j]);
		printf(" │\n");
		if (i < matrix->rows - 1)
		{
			printf("│");
			for (size_t j = 0; j < matrix->cols - 1; j++)
				printf("          ");
			printf("         │\n");
		}
	}
	printf("└");
	for (size_t j = 0; j < matrix->cols - 1; j++)
		printf("          ");
	printf("         ┘\n");
}

int	main(void)
{
	t_matrix	*A;
	t_matrix	*B;
	t_matrix	*C;
	t_matrix	*D;
	t_matrix	*E;
	t_matrix	*F;

	// Create two 2x2 matrices
	A = matrix_create(2, 2);
	B = matrix_create(2, 2);
	// Initialize matrices with specific values
	initialize_matrix(A, 1.0);
	initialize_matrix(B, 100.0);
	// Print initialized matrices
	printf("\nInitialized t_matrix A:\n\n");
	matrix_print(A);
	printf("\nInitialized t_matrix B:\n\n");
	matrix_print(B);
	C = matrix_add(A, B);
	printf("A + B:\n");
	matrix_print(C);
	D = matrix_sub(A, B);
	printf("A - B:\n");
	matrix_print(D);
	E = matrix_mul(A, B);
	printf("A * B:\n");
	matrix_print(E);
	F = matrix_transpose(A);
	printf("Transpose of A:\n");
	pretty_print_matrix(F);
	printf("\n-------------\n");
	// Populate matrices with random values
	populate_matrix_random(A);
	populate_matrix_random(B);
	// Print matrices with random values
	printf("\nMatrix A with random values:\n\n");
	matrix_print(A);
	printf("\nMatrix B with random values:\n\n");
	matrix_print(B);
	// Free matrices
	matrix_destroy(A);
	matrix_destroy(B);
	matrix_destroy(C);
	matrix_destroy(D);
	matrix_destroy(E);
	matrix_destroy(F);
	return (0);
}
