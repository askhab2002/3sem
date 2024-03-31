#include <iostream>
#include "Restaurant.h"
#include "Exception.h"

using namespace std;

Restaurant::Restaurant() {
	num_ = 0;
	table_ = NULL;
}

Restaurant::Restaurant(int num) {

	if(num <= 0) {
		throw SetException(Something, " Вы ввели некорректное значения для числа столиков!");
	}

	num_ = num;
	table_ = new seat_array_[num_];

	for(int i = 0; i < num_; i++) {
		table_[i].last_time_ = 0;
		table_[i].num_of_pairs_ = 0;
		table_[i].array_ = new seat_[8];
		table_[i].time_array_ = new int[24];
		for(int j = 0; j < 24; j++) {
			table_[i].time_array_[j] = -1;
		}
	}

}

Restaurant::Restaurant(const Restaurant &Res) {
	if(&Res == NULL) {
		throw SetException(Something, " Вы не ввели класс, который использовался бы в конструкторе копирования!");
	}

	num_ = Res.num_;
	table_ = new seat_array_[num_];

	for(int i = 0; i < num_; i++) {
		table_[i].last_time_ = Res.table_[i].last_time_;
		table_[i].num_of_pairs_ = Res.table_[i].num_of_pairs_;
		table_[i].array_ = new seat_[8];

		for(int j = 0; j < table_[i].num_of_pairs_; j++) {
			table_[i].array_[j].cellphone_ = Res.table_[i].array_[j].cellphone_;
			table_[i].array_[j].booking_time_ = Res.table_[i].array_[j].booking_time_;
		}

		table_[i].time_array_ = new int[24];

		for(int j = 0; j < 24; j++) {
			table_[i].time_array_[j] = Res.table_[i].time_array_[j];    
		}
	}	   
}

Restaurant::~Restaurant() {
	for(int i = 0; i < num_; i++) {
		delete [] table_[i].array_;
		delete [] table_[i].time_array_;

	}

	delete [] table_;
}


int Restaurant::SearchTime(int *free_seat, int time) { // Находит место с самым ранним бронированием
	int num_table = 0;
	int free_time = 0;

	if(free_seat == NULL || time < 0 || time > 21) {
		throw SetException(Something, " Вы ввели некорректное значение времени в функцию SearchTime!");   
	}
        
	if(num_ == 0) {
                throw SetException(Something, " Вы использовали метод поиска времени для пустой объекта!");
	}

	for(int i = 0; i < num_; i++) {
		for(int j = 0; j < 3; j++) {
			if(table_[i].time_array_[j + time] != -1) {
				//			cout << time << " " << table_[i].time_array_[j + time] << endl;
				break;
			}
			if(j == 2) {
				*free_seat = i;
				free_time = time;
				table_[i].time_array_[0 + time] = 0;
				table_[i].time_array_[1 + time] = 0;
				table_[i].time_array_[2 + time] = 0;
				return free_time;
			}
		}
	}

	for(int i = 0; i < num_; i++) {
		for(int j = 0; j < 21; j++) {
			for(int k = 0; k < 3; k++) {
				if(table_[i].time_array_[j + k] != -1) {
					break; 
				}
				if(k == 2) {
					*free_seat = i;
					free_time = j;
					table_[i].time_array_[j + 0] = 0;
					table_[i].time_array_[j + 1] = 0;
					table_[i].time_array_[j + 2] = 0;
					cout << " Бронь поставлена на - " << free_time << ", вместо - " << time << endl;
					return free_time;  
				} 
			}
		}
	} 

	return -1;	    
}

void Restaurant::Add(int time, int cellphone) {

	if(time < 0 || time > 21) {
		throw SetException(Something, " Вы ввели некорректное время в функцию Add!");
	}
        
	if(num_ == 0) {
                throw SetException(Something, " Вы использовали метод добавления клиента для пустого объекта!");
        }

	int free_seat = 0;
	int free_time = SearchTime(&free_seat, time);

	if(free_time != -1) {

		table_[free_seat].last_time_ += time;
		table_[free_seat].num_of_pairs_ ++;
		table_[free_seat].array_[table_[free_seat].num_of_pairs_ - 1].cellphone_ = cellphone;
		table_[free_seat].array_[table_[free_seat].num_of_pairs_ - 1].booking_time_ = free_time;
	}
	else { cout << " Извините, весь ресторан переполнен!" << endl; }

}

int Restaurant::IsThere(int cellphone) {
        if(num_ == 0) {
                throw SetException(Something, " Вы использовали метод поиска клиента для пустого объекта!");
        }
        
	for(int i = 0; i < num_; i++) {
		for(int j = 0; j < table_[i].num_of_pairs_; i++) {
			if(cellphone == table_[i].array_[j].cellphone_) {
				return table_[i].array_[j].booking_time_;
			}
		}
	}

	return -1;
}

void Restaurant::AllBookingPrint() {
        if(num_ == 0) {
                throw SetException(Something, " Вы использовали метод печати на экран для пустого объекта!");
        }

	for(int i = 0; i < num_; i++) {
		cout << " Список заказов на " << i + 1<< " столик." << " Число заказов - ";
		cout << table_[i].num_of_pairs_ << ". А именно:" << endl;
		for(int j = 0; j < table_[i].num_of_pairs_; j++) {
			cout << "    Время бронирования - " << table_[i].array_[j].booking_time_;
			cout << ". Телефон - " << table_[i].array_[j].cellphone_ << "." << endl;
		}
	}
}

void Restaurant::operator=(const Restaurant &Res) {
	if(&Res == NULL) {
		throw SetException(Something, " Вы не ввели класс в правую часть равенства!");
	}

	if(num_ != 0) {
		for(int i = 0; i < num_; i++) {
			delete [] table_[i].array_;
			delete [] table_[i].time_array_;

		}

		delete [] table_;
	} 

	num_ = Res.num_;
	table_ = new seat_array_[num_];

	for(int i = 0; i < num_; i++) {
		table_[i].last_time_ = Res.table_[i].last_time_;
		table_[i].num_of_pairs_ = Res.table_[i].num_of_pairs_;
		table_[i].array_ = new seat_[8];

		for(int j = 0; j < table_[i].num_of_pairs_; j++) {
			table_[i].array_[j].cellphone_ = Res.table_[i].array_[j].cellphone_;
			table_[i].array_[j].booking_time_ = Res.table_[i].array_[j].booking_time_;
		}

		table_[i].time_array_ = new int[24];

		for(int j = 0; j < 24; j++) {
			table_[i].time_array_[j] = Res.table_[i].time_array_[j];
		}
	}
}    
