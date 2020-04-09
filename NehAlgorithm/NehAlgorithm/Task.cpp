#include "Task.h"

Task::Task(int index)
{
	this->index = index;
	this->sumTime = 0;
}

Task::Task()
{
	this->index = 0;
	this->sumTime = 0;
}

void Task::AddJobTime(int jobIndex, int time)
{
	this->jobsTimes[jobIndex] = time;
}

int Task::CalculateSumTime(int amountOfMachines)
{
	for (int i = 0; i < amountOfMachines; ++i) {
		this->sumTime += jobsTimes[i];
	}
	return this->sumTime;
}

int Task::GetSumTime()
{
	return this->sumTime;
}

int Task::GetIndex()
{
	return this->index;
}

int Task::GetJobTime(int index)
{
	if (index < 500) {
		return this->jobsTimes[index];
	}
	else{
		return -1;
	}
}
