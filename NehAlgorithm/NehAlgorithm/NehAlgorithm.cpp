// Sterowanie procesami dyskretnymi
// dr in¿. Mariusz Makuchowski
// Rok akademicki 2019/2029
// Wojciech Konury 241488
// Maciej Szczurek 241179

#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <fstream>

#include "Algorithm.h"

int CMaxs[501][21];
long double programCalcTime = 0;

bool saveResultToFile(std::string resultFileName, int dataID, int bestCMax, long double time) {
	std::ofstream resultFile;

	resultFile.open(resultFileName, std::ios::app);

	if (!resultFile.good()) {
		std::cout << "CAN NOT SAVE RESULTS TO FILE" << std::endl;
		return false;
	}
	else {
		resultFile << dataID << "\t" << bestCMax << "\t" << time << std::endl;
	}

	resultFile.close();
	return true;
}

int Cmax(Task tasks[], int ammountOfTasks, int ammountOfMachines) {
	int cmaxSum;

	for (int i = 0; i < ammountOfTasks; ++i) {
		CMaxs[i][0] = 0;
	}

	for (int i = 0; i < ammountOfMachines; ++i) {
		CMaxs[0][i] = 0;
	}

	for (int i = 1; i <= ammountOfTasks; ++i) {
		for (int j = 1; j <= ammountOfMachines; ++j) {
			cmaxSum = tasks[i - 1].GetJobTime(j - 1);
			CMaxs[i][j] = std::max(CMaxs[i - 1][j], CMaxs[i][j - 1]) + cmaxSum;
		}
	}

	return CMaxs[ammountOfTasks][ammountOfMachines];
}

int NEH(Task tasks[], int ammountOfTasks, int ammountOfMachines, int index) {
	int best;
	int currentCMax;
	int minCMax;
	int swapNumber;
	int bSwapNumber;

	clock_t timerStart = clock();

	for (int taskIterator = 0, s = 2; taskIterator < ammountOfTasks - 1; ++taskIterator, ++s) {
		currentCMax = Cmax(tasks, s, ammountOfMachines);
		minCMax = currentCMax;

		swapNumber = 0;
		bSwapNumber = 0;

		for (int i = (s - 1); i >= 1; --i) {
			swapNumber++;

			std::swap(tasks[i], tasks[i - 1]);
			currentCMax = Cmax(tasks, s, ammountOfMachines);

			if (currentCMax <= minCMax) {
				minCMax = currentCMax;
				bSwapNumber = swapNumber;
			}
		}

		int iterator = swapNumber;
		int index = 0;
		while (iterator > bSwapNumber)
		{
			std::swap(tasks[index], tasks[index + 1]);

			--iterator;
			++index;
		}
	}
	best = Cmax(tasks, ammountOfTasks, ammountOfMachines);

	clock_t timerStop = clock();
	long double nehCalcTime = long double(timerStop - timerStart) / CLOCKS_PER_SEC;

	std::cout << "Data ID: " << index << " CMax = " << best << " Calculation time: " << nehCalcTime << " s" << std::endl;
	saveResultToFile("nehResultFile.DAT", index, best, nehCalcTime);

	return best;
}

int main()
{
	int tasksAmmount = 0;
	int machinesAmmount = 0;
	int dataAmmount = 0;

	Task tasks[500];

	std::string dataIdentificator;

	std::fstream file;
	std::string fileName = "Data.DAT";

	clock_t timerStart = clock();

	file.open(fileName, std::fstream::in);

	if (!file.good()) {
		std::cout << "FILE ERROR" << std::endl;
		return -1;
	}

	file >> dataAmmount;
	for (int dataIterator = 0; dataIterator <= dataAmmount; ++dataIterator) {

		int neh;
		int cmax = 0;
		int indexWithEquealTimeA = 0;
		int indexWithEquealTimeB = 0;
		int jobTime;

		file >> dataIdentificator;
		file >> tasksAmmount;
		file >> machinesAmmount;

		for (int i = 0; i < tasksAmmount; ++i) {
			Task currentJob(i);

			for (int jobIndex = 0; jobIndex < machinesAmmount; ++jobIndex) {
				file >> jobTime;
				currentJob.AddJobTime(jobIndex, jobTime);
			}
			currentJob.CalculateSumTime(machinesAmmount);

			tasks[i] = currentJob;
		}

		std::sort(tasks, tasks + tasksAmmount, [](Task& first, Task& second) {
			return first.GetSumTime() > second.GetSumTime(); 
		});

		for (int i = 0; i < tasksAmmount; ++i) {
			if (tasks[i].GetSumTime() == tasks[i + 1].GetSumTime()) {
				indexWithEquealTimeA = i;

				while (tasks[i].GetSumTime() == tasks[i + 1].GetSumTime()) {
					i++;
				}
				indexWithEquealTimeB = i;
			}

			std::sort(tasks + indexWithEquealTimeA, tasks + indexWithEquealTimeB + 1, [](Task& first, Task& second) {
				return first.GetIndex() < second.GetIndex();
			});
		}
		cmax = Cmax(tasks, tasksAmmount, machinesAmmount);
		neh = NEH(tasks, tasksAmmount, machinesAmmount, dataIterator);
	}

	clock_t timerStop = clock();

	programCalcTime = long double(timerStop - timerStart) / CLOCKS_PER_SEC;

	std::cout << "Calculation time for " << dataAmmount << " instances: " << programCalcTime << " s" << std::endl; 

	file.close();

	return 0;
}
