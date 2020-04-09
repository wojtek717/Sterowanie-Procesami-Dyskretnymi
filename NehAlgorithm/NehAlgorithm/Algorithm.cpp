#include "Algorithm.h"

int Cmax(Task tasks[], int ammountOfTasks, int ammountOfMachines)
{
	clock_t beginCMax_time = clock();

	int currentSumTimeCMax{};


	for (int i = 0; i < jobsNumber; i++) {
		CMaxArray[i][0] = 0;
	}

	for (int i = 0; i < machinesNumber; i++) {
		CMaxArray[0][i] = 0;
	}


	for (int i = 1; i <= jobsNumber; i++) {
		for (int j = 1; j <= machinesNumber; j++) {
			currentSumTimeCMax = jobs[i - 1].oneJobTime[j - 1];

			CMaxArray[i][j] = std::max(CMaxArray[i - 1][j], CMaxArray[i][j - 1]) + currentSumTimeCMax;
		}
	}


	clock_t endCMax_time = clock();
	double CMax_time = double(endCMax_time - beginCMax_time) / CLOCKS_PER_SEC;
	fullCMAXtime += CMax_time;

	int CMaxResult = CMaxArray[jobsNumber][machinesNumber];


	return CMaxArray[jobsNumber][machinesNumber];
}
