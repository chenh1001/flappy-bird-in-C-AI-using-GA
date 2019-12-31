#include "GeneticAlgorithm.h"
#include <stdio.h>

int gens = 0;
int numOfBirds = 50;

void calcFitness(Bird** birds)
{
	double sum = 0;
	for (int i = 0; i < numOfBirds; i++)
	{
		sum += birds[i]->score + birds[i]->score / 100 * 1000;
	}

	for (int i = 0; i < numOfBirds; i++)
	{
		birds[i]->fittnes = (birds[i]->score + birds[i]->score / 100 * 1000) / sum;
	}
}

Bird* pickOne(Bird** birds)
{
	while (true)
	{
		int randomNum = (int)(randBetweenZeroAndOne() * numOfBirds);
		if (randomNum >= numOfBirds)
			randomNum = numOfBirds - 1;
		Bird* randomBird = birds[randomNum];
		double rand = randBetweenZeroAndOne();
		if (rand <= randomBird->fittnes)
		{
			return randomBird;
		}
	}
}

Bird** nextGen(Bird** birds)
{
	calcFitness(birds);
	gens++;

	Bird **newBirds = (struct Bird**)malloc(sizeof(Bird) * numOfBirds);
	printf("new gen");
	Bird* temp;

	for (int i = 0; i<numOfBirds; i++)
	{
		newBirds[i] = (Bird*)malloc(sizeof(Bird));
	}

	for (int i = 0; i < numOfBirds; i++)
	{
		temp = pickOne(birds);
		resetBirdNoBrain(newBirds[i]);
		newBirds[i]->brain = copyNeuralNetwork(temp->brain);
		NNMutate(0.1, newBirds[i]->brain);
	}

	//free stuff
	for (int i = 0; i < numOfBirds; i++)
	{
		for (int i = 0; i<birds[i]->brain.weigthsHO.rows; i++)
		{
			free(birds[i]->brain.weigthsHO.data[i]);
		}
		free(birds[i]->brain.weigthsHO.data);
		for (int i = 0; i<birds[i]->brain.biasH.rows; i++)
		{
			free(birds[i]->brain.biasH.data[i]);
		}
		free(birds[i]->brain.biasH.data);
		for (int i = 0; i<birds[i]->brain.biasO.rows; i++)
		{
			free(newBirds[i]->brain.biasO.data[i]);
		}
		free(birds[i]->brain.biasO.data);
		for (int i = 0; i<birds[i]->brain.weigthsIH.rows; i++)
		{
			free(birds[i]->brain.weigthsIH.data[i]);
		}
		free(birds[i]->brain.weigthsIH.data);
 		free(birds[i]);
	}
	free(birds);
	birds = newBirds;
	newBirds = NULL;
	return birds;
}