#include "GeneticAlgorithm.h"
#include <stdio.h>

int gens = 0;
int numOfBirds = 1000;

void calcFitness(Bird** birds)
{
	double sum = 0;
	for (int i = 0; i<numOfBirds; i++)
	{
		sum += birds[i]->score + birds[i]->score / 100 * 1000;
	}
	
	for (int i = 0; i<numOfBirds; i++)
	{
		if (sum == 0)
			birds[i]->fittnes = 99999;
		else 
			birds[i]->fittnes = (birds[i]->score + birds[i]->score/100 * 1000) / sum;
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

void nextGen(Bird** birds)
{
	calcFitness(birds);
	gens++;

	Bird **newBirds = (struct Bird**)malloc(sizeof(Bird*) * numOfBirds);
	printf("new gen");
	Bird* temp;
	for (int i = 0; i<numOfBirds; i++)
	{
		temp = newBird(pickOne(birds));
		newBirds[i] = temp;
		NNMutate(0.1, newBirds[i]->brain);
	}
	for (int i = 0; i<numOfBirds; i++)
	{
		*birds[i] = *newBirds[i];
	}

	//free stuff
	for (int i = 0; i < numOfBirds; i++)
	{
		/*for (int i = 0; i<newBirds[i]->brain.weigthsHO.rows; i++)
		{
			free(newBirds[i]->brain.weigthsHO.data[i]);
		}
		free(newBirds[i]->brain.weigthsHO.data);
		for (int i = 0; i<newBirds[i]->brain.biasH.rows; i++)
		{
			free(newBirds[i]->brain.biasH.data[i]);
		}
		free(newBirds[i]->brain.biasH.data);
		for (int i = 0; i<newBirds[i]->brain.biasO.rows; i++)
		{
			free(newBirds[i]->brain.biasO.data[i]);
		}
		free(newBirds[i]->brain.biasO.data);
		for (int i = 0; i<newBirds[i]->brain.weigthsIH.rows; i++)
		{
			free(newBirds[i]->brain.weigthsIH.data[i]);
		}
		free(newBirds[i]->brain.weigthsIH.data);*/
		free(newBirds[i]);
	}
	free(newBirds);
 }