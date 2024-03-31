#include <iostream>
#include "IntegerSet.h"
#include "IntegerSetException.h"

IntegerSet::IntegerSet() {
	max_cardinal_ = 0;
	cardinal_ = 0;
	members_ = NULL;
}

IntegerSet::IntegerSet(int amount) {
	SetMaxCardinal(amount);
	SetCardinal(0);
	members_ = new int[max_cardinal_];
}

IntegerSet::IntegerSet(int amount, int *neophytes, int lenth) {
	SetMaxCardinal(amount);
	members_ = new int[max_cardinal_];
	SetCardinal(0);
	SetMembers(neophytes, lenth);
}

IntegerSet::IntegerSet(const IntegerSet &Original) {
	SetMaxCardinal(Original.max_cardinal_);
	SetCardinal(Original.cardinal_);
	SetMembers(Original);
}

IntegerSet::~IntegerSet() {
	delete [] members_;
}

void IntegerSet::SetMaxCardinal(int amount) {
	if(amount >= 0) {
		max_cardinal_ = amount;
	}
	else { 
//		std::cout << " Неподходящее число элементов" << std::endl; 
	        throw SetException(Something, "Entered negative number for maximum set size");
	}
}

void IntegerSet::SetCardinal(int amount) {
	if(amount >= 0) {
		cardinal_ = amount;
	}
	else{ 
//		std::cout << " Неподходящее число элементов" << std::endl; 
	        throw SetException(Something, "Entered negative number for current set size.");
	}
}

void IntegerSet::SetMembers(int * &neophytes, int lenth) {
	if(neophytes == NULL) {
                throw SetException(Something, "Array pointer not entered to add to the set.");
	}

	if(lenth + cardinal_ > max_cardinal_) {
//		std::cout << " Слишком длинный массив" << std::endl;
		throw SetException(Something, "Array size too long to add to the set.");
	}

	for(int i = 0; i < lenth; i++) {
		(*this) + neophytes[i];
	}
}

void IntegerSet::SetMembers(const IntegerSet &Set) {
	members_ = new int[Set.cardinal_];

	for(int i = 0; i < cardinal_; i++) {
		members_[i] = Set.members_[i];
	}   
}

void IntegerSet::PrintCardinal() {
	std::cout << "  Число элементов во множестве - " << cardinal_ << std::endl;
}

void IntegerSet::PrintMembers() {
	std::cout << "  Вывод элементов множества:" << std::endl;

	if(cardinal_ != 0) {
		for(int i = 0; i < cardinal_; i++) {
			std::cout << "    " << members_[i];
		}
		std::cout << std::endl;
	}

	else {
		std::cout << "    Пустое множество." << std::endl;
	}
}

int IntegerSet::GetCardinal() {
	return cardinal_;
}

int *IntegerSet::GetMembers() {
        int *pointer = members_;
	return pointer;
}

void IntegerSet::operator=(const IntegerSet &Set1) {
	if(max_cardinal_ > 0) {
		delete [] members_;
	}

	max_cardinal_ = Set1.max_cardinal_;
	cardinal_ = Set1.cardinal_;
	members_ = new int[max_cardinal_];

	for(int i = 0; i < cardinal_; i++) {
		members_[i] = Set1.members_[i];
	}
}

IntegerSet operator+(const IntegerSet &Set1, const IntegerSet &Set2) {
	IntegerSet Union(Set1.max_cardinal_ + Set2.max_cardinal_);

	for(int i = 0; i < Set1.cardinal_; i++) {
		Union.members_[i] = Set1.members_[i];
	}

	Union.cardinal_ = Set1.cardinal_;

	for(int i = 0; i < Set2.cardinal_; i++) {
		Union + Set2.members_[i];
	}

	return Union;
}

void IntegerSet::operator+(int num) {

	if(max_cardinal_ < cardinal_ + 1) {
//		std::cout << "  Множество уже забито" << std::endl;
		throw SetException(Something, "Adding element to the set forbidden. The set is already full.");
	}

	for(int i = 0; i < cardinal_; i++) {
		if(members_[i] == num) {
			return;
		}
	}

	members_[cardinal_] = num;
	cardinal_++;
}

