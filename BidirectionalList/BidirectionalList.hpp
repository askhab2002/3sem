#pragma once
#include <iostream>
#include "Exception.h"



template <class T>
class BidirectionalList {
	private:
		struct Node {
			T value_;
			Node *previous_;
			Node *next_;
			Node() {
				next_ = nullptr;
				previous_ = nullptr;
			}
		};

		int size_;
		Node *begin_;
		Node *current_;

	public:
		BidirectionalList();
		BidirectionalList(const BidirectionalList<T> &list1);
		~BidirectionalList();

		bool AddNext(const T &a);
		bool AddPrevious(const T &a);

		bool DeleteCurrent();

		void Begin();
		T GetCurrent() const;
		Node *GetBegin() const;
		int GetSize() const;
		bool Next();
		bool Previous();

		BidirectionalList<T> operator+(const BidirectionalList<T> &list);
		BidirectionalList<T> &operator=(const BidirectionalList<T> &list);

		T ListMin();
		void SortIncreasing(); 

		class Iterator {
			private:
				const BidirectionalList<T> *list_;
				Node *node_;

				friend class BidirectionalList<T>;
				Iterator() {
					list_ = nullptr;
					node_ = nullptr;

				}
			public:
				Iterator(const Iterator &iter) {
					node_ = iter.node_;
					list_ = iter.list_;

				}

				Iterator(Node *node, const BidirectionalList<T> *list) {
					list_ = list;
					node_ = node;

				}

				Iterator(const BidirectionalList<T> *list) {
					list_ = list;
					node_ = list->begin_;

				}

				bool operator==(const Iterator &iter) {
					if(list_ == iter.list_ && node_ == iter.node_) {
						return true;
					}
					return false;
				}

				Iterator &operator=(const Iterator &iter) {
					if(this == &iter) {
						return *this;
					}
					node_ = iter.node_;
					list_ = iter.list_;
					return *this;
				}

				Iterator &operator++() {
					if(node_ == nullptr || list_->size_ == 0) {
						return *this;
					}
					node_ = node_->next_;
					return *this;
				}

				const T &operator*() {
					if(node_ != nullptr && list_->size_ != 0) {
						return node_->value_;
					}

					throw SetException(Something, " Error in block Iterator::operator*!");
				}

				bool IsThere() {
					if(node_ == nullptr || list_->size_ == 0) {
						return false;
					}
					return true;
				}
				/*
				   bool NextIter() {
				   if(node_ == nullptr || list_->size_ == 0) {
				   return false;
				   }

				   node_ = node_->next_;
				   return true;
				   }


				   bool PreviousIter() {
				   if(node_ == nullptr || list_->size_ == 0) {
				   return false;
				   }
				   node_ = node_->previous_;
				   return true;
				   } */
		};
};


template <class T>
BidirectionalList<T>::BidirectionalList() {
	begin_ = nullptr;
	current_ = nullptr;
	size_ = 0;
}

template <class T>
BidirectionalList<T>::BidirectionalList(const BidirectionalList<T> &list1) {
	begin_ = nullptr;
	current_ = nullptr;
	size_ = 0;
	Iterator iter(list1.begin_, &list1);
	for(int i = 0; i < list1.size_; i++) {
		AddNext(*iter);
		++iter;
	}
}

template <class T>
BidirectionalList<T>::~BidirectionalList() {
	Begin();
	while(DeleteCurrent()) {};
}

template <class T>
void BidirectionalList<T>::Begin() {
	current_ = begin_;
}


template <class T>
bool BidirectionalList<T>::Next() {
	if(current_->next_ == nullptr) {
		return false;
	}

	current_ = current_->next_;
	return true;
}

template <class T>
bool BidirectionalList<T>::Previous() {
	if(current_->previous_ == nullptr) {
		return false;
	}
	current_ = current_->previous_;
	return true;
}

template <class T>
T BidirectionalList<T>::GetCurrent() const {
	if(current_ == nullptr) {
		throw SetException(Something, " Error in block GetCurrent!");
	}
	return current_->value_;
}

template <class T>
int BidirectionalList<T>::GetSize() const {
	return size_;
}

template <class T>
bool BidirectionalList<T>::AddNext(const T &a) {
	try {
		BidirectionalList<T>::Node *node = new BidirectionalList<T>::Node;
		node->value_ = a;
		if(begin_ == nullptr) {
			begin_ =  node;
			current_ = node;
			current_->next_ = nullptr;
			current_->previous_ = nullptr;
		}
		else {
			node->next_ = current_->next_;
			node->previous_ = current_;
			if(current_->next_ != nullptr) {
				current_->next_->previous_ = node;
			}
			current_->next_ = node;
			current_ = node;

		}
		size_++;
	} catch(std::bad_alloc) { return false; }
	return true;
}

template <class T>
bool BidirectionalList<T>::AddPrevious(const T &a) {
	BidirectionalList<T>::Node node;
	node.value_ = a;

	if(size_ == 0) {
		begin_ = &node;
		current_ = begin_;
		current_->next_ = nullptr;
		current_->previous_ = nullptr;
		return true;
	}

	current_->previous_ = &node;
	node.next_ = current_;

	if(current_->previous_ == nullptr) {
		current_ = &node;
		current_->previous_ = nullptr;
		return true;
	}

	current_->previous_->next_ = &node;
	node.previous_ = current_->previous_;
	current_ = &node;
	return true;
}

template <class T>
bool BidirectionalList<T>::DeleteCurrent() {
	BidirectionalList<T>::Node *node;
	node = current_;
	if(node == nullptr) {
		return false;
	}


	if(node->next_ == nullptr && node->previous_ == nullptr) {

		begin_ = nullptr;
		current_ = nullptr;
		delete node;
		size_--;
		return true;
	}

	if(node->next_ != nullptr && node->previous_ != nullptr) {
		node->previous_->next_ = node->next_;
		node->next_->previous_ = node->previous_;
		current_ = node->next_;
		delete node;
		size_--;
		return true;
	}

	if(node->next_ == nullptr && node->previous_ != nullptr) {
		node->previous_->next_ = nullptr;
		current_ = node->previous_;
		delete node;
		size_--;
		return true;
	}

	if(node->next_ == nullptr && node->previous_ != nullptr) {
		node->previous_->next_ = nullptr;
		current_ = node->previous_;
		delete node;
		size_--;
		return true;
	}

	node->next_->previous_ = nullptr;
	current_ = node->next_;
	begin_ = current_;
	delete node;
	size_--;
	return true;
}

template <class T>
BidirectionalList<T> &BidirectionalList<T>::operator=(const BidirectionalList<T> &list) {
	Begin();
	while(DeleteCurrent()) {};

	Iterator iter(list.begin_, &list);

	for(int i = 0; i < list.size_; i++) {
		AddNext(*iter);
		++iter;
	}

	return *this;
}

template <class T>
BidirectionalList<T> BidirectionalList<T>::operator+(const BidirectionalList<T> &list) {
	BidirectionalList UnionList;

	if(size_ > 0) {
		Iterator iter1(this->begin_, this);
		for(int i = 0; i < size_; i++) {
			UnionList.AddNext(*iter1);
			++iter1;
		}
	}

	if(list.size_ > 0) {
		Iterator iter2(list.begin_, &list);
		for(int i = 0; i < list.size_; i++) {
			UnionList.AddNext(*iter2);
			++iter2;
		}
	}

	return UnionList;
}

template <class T>
T BidirectionalList<T>::ListMin() {
	Begin();
	T CurrentMin = GetCurrent();
	BidirectionalList<T>::Node *current = current_;
	Next();

	for(int i = 0; i < size_; i++) {
		if(GetCurrent() < CurrentMin) {
			CurrentMin = GetCurrent();
			current = current_;
		}
		Next();
	}

	Begin();

	for(int i = 0; i < size_; i++) {
		if(current_ == current || fabs(current_ - current) < 1e-3) {
			DeleteCurrent();
			break;
		}
		Next();
	}

	return CurrentMin;
}

template <class T>
void BidirectionalList<T>::SortIncreasing() {
	Begin();
	BidirectionalList List;
	T CurrentMin;
	int size = size_;

	for(int i = 0; i < size; i++) {
		CurrentMin = ListMin();
		List.AddNext(CurrentMin);
	}

	*this = List;
}
