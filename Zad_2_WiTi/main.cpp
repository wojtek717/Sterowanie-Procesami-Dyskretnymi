#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "task.h"

// https://github.com/wojtek717/Sterowanie-Procesami-Dyskretnymi

std::vector<Task> readData(std::string fileName){
	std::fstream file;
    std::vector<Task> task_queue;

    int _task_time;
    int _cost;
    int _due_date;
	int numberOfElements;

	std::cout << fileName;

	file.open(fileName, std::ios::in | std::ios::out);

	if (file.good() == true) {
		file >> numberOfElements;

		for (int i = 0; i < numberOfElements; ++i) {
			file >> _task_time;
			file >> _cost;
			file >> _due_date;
			task_queue.push_back(Task(_task_time, _cost, _due_date, i+1));
        }
		file.close();
	}else {
		std::cout << "File didn't open";
	}
    return task_queue;
}

int main(){

	for (auto iteratorPlik = 10; iteratorPlik <= 20; ++iteratorPlik){
		
	std::stringstream ss; 
	ss << "data" << iteratorPlik << ".txt";
	std::string name = ss.str();

    std::vector<Task> main_queue = readData(name);
	std::vector<Task> final_queue = DP_sequencing_problem(main_queue);
	printPermutation(final_queue);
	std::cout << std::endl << getWitiSum(final_queue) << std::endl << std::endl;

	}

    return 0;
}
