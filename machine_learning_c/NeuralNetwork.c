#include "NeuralNetwork.h"

NeuralNetwork newNeuralNetwork(int inputsLength, int hiddenLength, int outputsLength)
{
	NeuralNetwork nn;
	nn.inputsLength = inputsLength;
	nn.hiddenLength = hiddenLength;
	nn.outputsLength = outputsLength;

	nn.weigthsIH = newMatrix(nn.hiddenLength, nn.inputsLength);
	nn.weigthsHO = newMatrix(nn.outputsLength, nn.hiddenLength);
	matrixRandomize(nn.weigthsIH);
	matrixRandomize(nn.weigthsHO);

	nn.biasH = newMatrix(nn.hiddenLength, 1);
	nn.biasO = newMatrix(nn.outputsLength, 1);
	matrixRandomize(nn.biasH);
	matrixRandomize(nn.biasO);
	return nn;
}

NeuralNetwork copyNeuralNetwork(NeuralNetwork nn)
{
	NeuralNetwork temp;
	temp.inputsLength = nn.inputsLength;
	temp.hiddenLength = nn.hiddenLength;
	temp.outputsLength = nn.outputsLength;

	temp.weigthsIH = copyMatrix(nn.weigthsIH);
	temp.weigthsHO = copyMatrix(nn.weigthsHO);

	temp.biasH = copyMatrix(nn.biasH);
	temp.biasO = copyMatrix(nn.biasO);
	return temp;
}

void freeMatrix(Matrix m)
{
	for (int i = 0; i<m.rows; i++)
	{
		free(m.data[i]);
	}
	free(m.data);
	m.data = NULL;
}

Matrix NNfeedingForward(double* inputsArr,int inputSize, NeuralNetwork nn)
{
	Matrix inputs = newMatrix(inputSize, 1);
	double temp = 0;
	for (int i = 0; i < inputs.rows; i++)
	{
		temp = inputsArr[i];
		inputs.data[i][0] = temp;
	}
	//printf(inputs.data[1]);
	//matrixPrint(inputs);
	Matrix hidden = matrixMultiply(nn.weigthsIH,inputs );
	matrixAddMatrix(hidden, nn.biasH);
	matrixSigmoid(hidden);

	//Getting outputs from level 1

	Matrix outputs = matrixMultiply(nn.weigthsHO, hidden);
	matrixAddMatrix(outputs, nn.biasO);
	matrixSigmoid(outputs);
	Matrix transposed = transpose(outputs);

	freeMatrix(inputs);
	freeMatrix(hidden);
	freeMatrix(outputs);

	return transposed;
}

void NNMutate(double mutateRate, NeuralNetwork nn)
{
	matrixMutate(mutateRate,nn.weigthsIH);
	matrixMutate(mutateRate, nn.weigthsHO);

	matrixMutate(mutateRate, nn.biasH);
	matrixMutate(mutateRate, nn.biasO);
}



