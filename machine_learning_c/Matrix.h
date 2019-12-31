#ifndef matrixHeader
#define matrixHeader
#include <stdio.h>
#include <stdlib.h>


typedef struct Matrixes {
	int rows;
	int cols;
	double **data;
} Matrix;

/*struct Matrixes newMatrix(int rowsGiven, int colsGiven){
	int rows = rowsGiven;
	int cols = colsGiven;
	int **data = malloc(rows*sizeof(data));
	for (int i = 0; i<rows; i++)
	{
		data[i] = malloc(cols * sizeof(data[i]));
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			data[i][j] = 0;
		}
	}
}*/

Matrix newMatrix(int rows, int cols);
double randBetweenZeroAndOne();
void matrixAddtoMatrix(Matrix dest, Matrix m);
void matrixMutate(double Mrate, Matrix m);
void matrixSigmoid(Matrix m);
void matrixDSigmoid(Matrix m);
Matrix copyMatrix(Matrix a);
Matrix dSigmoid(Matrix a);
Matrix transpose(Matrix m);
void matrixAddMatrix(Matrix dest, Matrix m);
Matrix substuct(Matrix a, Matrix b);
void matrixRandomize(Matrix m);
void matrixMultiplyNum(double n, Matrix m);
void matrixMultiplySimple(Matrix dest, Matrix m);
Matrix matrixMultiply(Matrix a, Matrix b);
void matrixPrint(Matrix m);

#endif
