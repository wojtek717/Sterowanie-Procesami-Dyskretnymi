#ifndef _zadanie_h_included_
#define _zadanie_h_included_

#include <vector>
#include <iostream>

struct Task {

    int processing_time;
    int cost;
    int due_date;
    int index;

    Task(){};
    Task(int processing_time, int cost, int due_date, int index){
    this->processing_time = processing_time;
    this->cost = cost;
    this->due_date = due_date;
    this->index = index;
    }
};

void printQueue(std::vector<Task> _queue){

    std::cout << std::endl;
    for(int i = 0; i < _queue.size(); ++i){
        std::cout << _queue[i].index << ": " 
                  << _queue[i].processing_time << " "
                  << _queue[i].cost << " "
                  << _queue[i].due_date << std::endl;
    }
}

void printPermutation(std::vector<Task> _queue){

    std::cout << std::endl;
    for(int i = 0; i < _queue.size(); ++i){
        std::cout << _queue[i].index << " ";
    }
}

int getC(std::vector<Task> _queue){
    int c = 0;

    for(int i = 0; i < _queue.size(); ++i){
        c += _queue[i].processing_time;
    }
    return c;
}

int getPenalty(Task task, int c){
    int tmp = task.cost * (c - task.due_date);

    if(tmp < 0)
        return 0;
    else
        return tmp;     
}

int getWitiSum(std::vector<Task>_queue){
	int tmp_sum = 0;
	int tmp_time = 0;

	for (int i = 0; i < _queue.size(); i++){
		tmp_time += _queue[i].processing_time;
        tmp_sum += getPenalty(_queue[i], tmp_time);
	}
	return tmp_sum;
}

int getLowestPenaltyIndex(const std::vector<Task> &_queue, int c){
    int tmp_min = 1000000;
    int index_min;
    int _K;

    for (int j = 0; j < _queue.size(); j++){
            _K = getPenalty(_queue[j], c);

            if(_K < tmp_min){
				tmp_min = _K;

				index_min = j;
			}
	}
    return index_min;
}

std::vector<Task> DP_sequencing_problem(std::vector<Task> _queue){
	int _K;
    int _C;
	Task _min;
    int index_min;
    std::vector<Task> _final_queue;

    int it =_queue.size();
	for (int i = 0; i < it; i++){
        _C = getC(_queue);
        index_min = getLowestPenaltyIndex(_queue, _C);
        _min = _queue[index_min];
        _final_queue.push_back(_min);
        _queue.erase(_queue.begin()+index_min);
	}
    std::reverse(_final_queue.begin(), _final_queue.end());
    return _final_queue;
}

#endif