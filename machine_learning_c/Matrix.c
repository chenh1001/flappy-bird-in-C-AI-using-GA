#include "Matrix.h"

Matrix newMatrix(int rows, int cols)
{
	double **data = malloc(rows * sizeof(double));
	for (int i = 0; i<rows; i++)
	{
		data[i] = malloc(cols * sizeof(double));
	}
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			data[i][j] = 0;
		}
	}
	Matrix temp = { rows,cols,data };
	return temp;
}

double randBetweenZeroAndOne()
{
	return ((double)rand() / (RAND_MAX));
}

void matrixAddtoMatrix(Matrix dest, Matrix m)
{
	for (int i = 0; i<dest.rows; i++)
	{
		for (int j = 0; j<dest.cols; j++)
		{
			dest.data[i][j] += m.data[i][j];
		}
	}
}
void matrixMutate(double Mrate, Matrix m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			if (randBetweenZeroAndOne() < Mrate)
				m.data[i][j] += (randBetweenZeroAndOne()) * 2 - 1;
		}
	}
}

void matrixSigmoid(Matrix m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			m.data[i][j] = (1.0 / (1 + exp(-m.data[i][j])));
		}
	}
}

void matrixDSigmoid(Matrix m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			m.data[i][j] = m.data[i][j] * (1 - m.data[i][j]); //נגזרת של סיגמואיד
		}
	}
}

Matrix copyMatrix(Matrix a)
{
	Matrix retM = newMatrix(a.rows, a.cols);
	for (int i = 0; i < retM.rows; i++)
	{
		for (int j = 0; j < retM.cols; j++)
		{
			retM.data[i][j] = a.data[i][j];
		}
	}
	return retM;
}

Matrix dSigmoid(Matrix a)
{
	Matrix retM = copyMatrix(a);
	for (int i = 0; i < retM.rows; i++)
	{
		for (int j = 0; j < retM.cols; j++)
		{
			retM.data[i][j] = retM.data[i][j] * (1 - retM.data[i][j]); //נגזרת של סיגמואיד
		}
	}
	return retM;
}

Matrix transpose(Matrix m)
{
	Matrix temp = newMatrix(m.cols, m.rows);
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			temp.data[j][i] = m.data[i][j];
		}
	}
	return temp;
}

void matrixAddMatrix(Matrix dest,Matrix m)
{
	for (int i = 0; i < dest.rows; i++)
	{
		for (int j = 0; j < dest.cols; j++)
		{
			dest.data[i][j] += m.data[i][j];
		}
	}
}

Matrix substuct(Matrix a, Matrix b)
{
	Matrix temp = newMatrix(a.rows, a.cols);
	for (int i = 0; i < a.rows; i++)
	{
		for (int j = 0; j < a.cols; j++)
		{
			temp.data[i][j] = a.data[i][j] - b.data[i][j];
		}
	}
	return temp;
}

void matrixRandomize(Matrix m)
{ 
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			double r = randBetweenZeroAndOne();
			m.data[i][j] = (r * 2 - 1);
		}
	}
}


void matrixMultiplyNum(double n, Matrix m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			m.data[i][j] *= n;
		}
	}
}

void matrixMultiplySimle(Matrix dest,Matrix m)
{

	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			dest.data[i][j] = dest.data[i][j] * m.data[i][j];
		}
	}
}
Matrix matrixMultiply(Matrix a, Matrix b)
{
	if (a.cols != b.rows)
		puts("cant multiply matrixes");
	Matrix temp = newMatrix(a.rows, b.cols);
	for (int i = 0; i < temp.rows; i++)
	{
		for(int j = 0; j < temp.cols; j++)
		{
			double sum = 0;
			for (int k = 0; k < a.cols; k++)
			{
				sum += a.data[i][k] * b.data[k][j];
			}
			temp.data[i][j] = sum;
		}
	}
	return temp;
}

void matrixPrint(Matrix m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			printf("%0.4f ",m.data[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

