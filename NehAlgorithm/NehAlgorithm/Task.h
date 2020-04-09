#pragma once
class Task
{
private:
	int sumTime;
	int jobsTimes[500]; //Use arrays instead of vector because SPEEEEEEED
	int index;

public:
	Task(int index);
	Task();

	void AddJobTime(int jobIndex, int time);
	int CalculateSumTime(int amountOfMachines);

	int GetSumTime();
	int GetIndex();
	int GetJobTime(int index);
};

