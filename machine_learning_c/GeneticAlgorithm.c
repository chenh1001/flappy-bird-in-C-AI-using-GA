#include "GeneticAlgorithm.h"
#include <stdio.h>

int gens = 0;
int numOfBirds = 50;

void calcFitness(Bird** birds)//cals the fitness value of all birds
{
	double sum = 0;
	for (int i = 0; i < numOfBirds; i++)
	{
		sum += birds[i]->score; //+ birds[i]->score / 100 * 1000; // add score for each 100 score passed
	}

	for (int i = 0; i < numOfBirds; i++)
	{
		birds[i]->fittnes = birds[i]->score / sum;//(birds[i]->score + birds[i]->score / 100 * 1000) / sum;
	}
}

Bird* pickOne(Bird** birds)//pick a bird to continue his gens, more chances if fittnes is high
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

Bird** nextGen(Bird** birds)//returns the new gen birds by fittness
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
		freeMatrix(birds[i]->brain.weigthsHO);
		freeMatrix(birds[i]->brain.biasH);
		freeMatrix(birds[i]->brain.biasO);
		freeMatrix(birds[i]->brain.weigthsIH);

 		free(birds[i]);
	}
	free(birds);
	birds = newBirds;
	newBirds = NULL;
	return birds;
}