#ifndef nnHeader
#define nnHeader
#include "Matrix.h"

typedef struct NeuralNets {
	int inputsLength;
	int hiddenLength;
	int outputsLength;
	Matrix weigthsIH;
	Matrix weigthsHO;
	Matrix biasH;
	Matrix biasO;

} NeuralNetwork;

NeuralNetwork newNeuralNetwork(int inputsLength, int hiddenLength, int outputsLength);
NeuralNetwork copyNeuralNetwork(NeuralNetwork nn);
double* NNfeedingForward(double* inputsArr, int inputSize, NeuralNetwork nn);
void NNMutate(double mutateRate, NeuralNetwork nn);

#endif
