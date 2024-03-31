#include <iostream>
#include "Exception.h"
#include "Clock.h"

using namespace std;

Clocks::Clocks(int amount_of_processes, int num_of_process) {
	if( amount_of_processes < 1 || num_of_process < 1) {
		throw SetException(Something, " Некорректно введенные значения для конструктора!"); 
	}

	amount_of_processes_ = amount_of_processes;
	num_of_process_ = num_of_process;
	vector_ = new int[amount_of_processes_];
	for(int i = 0; i < amount_of_processes_; i++) {
		vector_[i] = 0; 
	}   
}
Clocks::Clocks(const Clocks & Clock1) {
	if(&Clock1 == NULL) {
		throw SetException(Something, " Введен пустой объект класса в конструктор копирования!"); 
	}

	amount_of_processes_ = Clock1.amount_of_processes_;
	num_of_process_ = Clock1.num_of_process_;
	vector_ = new int[amount_of_processes_];

	for(int i = 0; i < amount_of_processes_; i++) {
                vector_[i] = Clock1.vector_[i];  
	}
}	
Clocks::~Clocks() {
	delete [] vector_;
}

void Clocks::ReceiveVector(const  Clocks &Clock1) const {
	if(&Clock1 == NULL) {
		throw SetException(Something, " Введен пустой объект класса в функцию ReceiveVector!");
	}

	vector_[Clock1.num_of_process_ - 1] = Clock1.vector_[Clock1.num_of_process_ - 1];
	AddOne();
}

void Clocks::AddOne() const {
	vector_[num_of_process_ - 1]++;
}

Clocks & Clocks::Send_vector()  {
	AddOne();
	return *this;
}

void Clocks::PrintVector() const {
	cout << " amount_of_processes = " << amount_of_processes_ << " num_of_process = " << num_of_process_ << endl;
	for(int i = 0; i < amount_of_processes_; i++) {
		cout << vector_[i] << endl;
	}

}

Clocks & Clocks::operator=(const Clocks &Clock1) {
	if(&Clock1 == NULL) {
                throw SetException(Something, " Введён пустой объект в функцию оператор равно!");
	}
        if(this == &Clock1) {
                return *this;
	}
         
        amount_of_processes_ = Clock1.amount_of_processes_;
	num_of_process_ = Clock1.num_of_process_;
	int *array = new int[amount_of_processes_];
        delete [] vector_;

	for(int i = 0; i < amount_of_processes_; i++) {
                array[i] = Clock1.vector_[i];
	}
        
	vector_ = array;

	return *this;
}	

int MeasureVectors(const  Clocks &Clock1, const  Clocks &Clock2) {
	if(&Clock1 == NULL || &Clock2 == NULL) {
		throw SetException(Something, " Введен пустой объект класса в функцию MeasureVectors!");
	}

	int result = OneSideMeasure(Clock1, Clock2);
	if(result == YES) {
		return LEFT;
	}
	else { 
		if(result == EQUAL) {
			return EQUAL;
		} 
	}

	result = OneSideMeasure(Clock2, Clock1);
	if(result == YES) {
		return RIGHT;
	}
	else {
		if(result == EQUAL) {
			return EQUAL;
		}
	} 

	return NOPE;
}

int OneSideMeasure(const  Clocks &Clock1, const  Clocks &Clock2) {
	if(&Clock1 == NULL || &Clock2 == NULL) {
		throw SetException(Something, " Введен пустой объект класса в функцию OneSideMeasure!");
	}

	if(Measure(Clock1, Clock2) == YES) {
		for(int i = 0; i < Clock1.amount_of_processes_; i++) {
			if(Clock1.vector_[i] > Clock2.vector_[i]) {
				return YES;
			}
		}

		return EQUAL;
	}

	return NOPE; 
}

int Measure(const  Clocks &Clock1, const  Clocks &Clock2) { // Проверяет, что Clock1 не меньше Clock2
	if(&Clock1 == NULL || &Clock2 == NULL) {
		throw SetException(Something, " Введен пустой объект класса в функцию Measure !");
	}

	for(int i = 0; i < Clock1.amount_of_processes_; i++) {
		if(Clock1.vector_[i] < Clock2.vector_[i]) {
			return NOPE;
		}
	}

	return YES; 
}

