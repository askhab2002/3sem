#pragma once

#include <iostream>
#include "Exception.h"

template <class T, class V>
class BTree;

template <class T, class V>
struct BTreeNode {

	friend class BTree<T, V>;

	T *keys_;
	V *values_;
	int order1_;
	int size_;
	BTreeNode **child_;
	//	BTreeNode *parent_;
	bool end_;

	BTreeNode (int order, bool end_index) {
		keys_ = new T[2 * order - 1];
		values_ = new V[2 * order - 1];
//		for(int i = 0; i < 2 * order - 1; i++) {
//                        keys_[i] = 0;
//		}

		child_ = new BTreeNode *[2 * order];
//		for(int i = 0; i < 2 * order; i++) {
//                        child_[i] = nullptr;
//		}

		order1_ = order;
		end_ = end_index;
		size_ = 0;
		//		parent_ = nullptr;
	}	
	~BTreeNode () {
		delete [] keys_;
		delete [] values_;

		for(int i = 0; i < size_ + 1; i++) {
			
			child_[i] = nullptr;
		}
		

		delete [] child_;
		size_ = 0;
		order1_ = 0;
		end_ = false;
	}

	void Delete();
	void Insert(const T key, const V &value);
	void SplitChild(int number_of_child, BTreeNode *child);
	BTreeNode *NodeSearch(const T &key);
	void Print();

	int GreaterKey(T &key);
	void RemoveKey(T &key);
	void EndRemove(int number);
	void ComplexRemove(int number);
	void Union(int number);
	T Supremum(int number);
	T Infinum(int number);
	void AddKey(int number);
	void Previous(int number);
	void Next(int number);	
};

template <class T, class V>
class BTree {
	private:
		int order_;
		BTreeNode<T, V> *root_;
	public:
		BTree(int order) {
			order_ = order;
			root_ = nullptr;
		}
		~BTree();

		BTreeNode<T, V> *NodeSearch(const T &key);
		V *ValueSearch(const T &key) {
			BTreeNode<T, V> *Node = NodeSearch(key);
			if(Node == nullptr) {
				return nullptr;
			}

                        int k = 0;
			for(; Node->keys_[k] != key; k++) {}
			return &Node->values_[k];
		}

		void InsertKey(const T key, const V &value);
		void PrintAllKeys();
		void Remove(T key) {
			if(root_ == nullptr) {

				return;
			}

			root_->RemoveKey(key);

			if(root_->size_ == 0) {
				BTreeNode<T, V> *node = root_;
				if(root_->end_) {
					root_ = nullptr;
				}
				else {
					root_ = root_->child_[0];
				}

				delete node;
			}
		}
/*
		BTree &operator=(const BTree &Tree) {
			if(this == &Tree) {
				return *this;
			}

			
			if(root_ != nullptr) {
                                root_->Delete();
                        }

			root_ = Tree.root_;
                        order_ = Tree.order_;
			return *this;
	        }   */
};

template <class T, class V>
BTreeNode<T, V> *BTreeNode<T, V>::NodeSearch(const T &key) {
	int i = 0;
//	std::cout << " ============================2" << std::endl;
//	std::cout << " ============================2" << " size_ = " << size_ << std::endl;
        
	//      std::cout << " ============================2" << std::endl;
	while(i < size_ && keys_[i] < key) {
//		std::cout << " ============================4" << std::endl;
                i++;
	}

//        std::cout << " ============================3" << std::endl;
	if(i < size_ && keys_[i] == key) {
		return this; 
	}

	if(end_ == true) {
		return nullptr;
	}

//	child_[i]->NodeSearch(key);
//        std::cout << " ============================2" << std::endl;
	return child_[i]->NodeSearch(key);
}

template <class T, class V>
BTreeNode<T, V> *BTree<T, V>::NodeSearch(const T &key) {
	if(root_ == nullptr) {
		return nullptr;
	}
 //       std::cout << " ============================" << std::endl;
	return root_->NodeSearch(key);
}

template <class T, class V>
void BTreeNode<T, V>::SplitChild(int number_of_child, BTreeNode *child) {
//        BTreeNode right = BTreeNode(child->order1_, child->end_);
//	BTreeNode *right_node = &right;
	BTreeNode *right_node = new BTreeNode(child->order1_, child->end_);
	right_node->size_ = order1_ - 1;

	for(int i = 0; i < order1_ - 1; i++) {          //Передаём вторую половину ключей новому правому потомку
		right_node->keys_[i] = child->keys_[i + order1_];
		right_node->values_[i] = child->values_[i + order1_];
	}

	if(child->end_ == false) {
		for(int i = 0; i < order1_; i++) {      //Передаём вторую половину адресов потомков правому потомку
			right_node->child_[i] = child->child_[i + order1_];
		}
	}

	for(int i = size_; i > number_of_child; i--) { //Сдвигаем указатели на потомков для освобождения места для нового
		child_[i + 1] = child_[i];
	}

	child->size_ = order1_ - 1;                     

	child_[number_of_child + 1] = right_node;      //Сцепляем нового потомка с родителем

	for(int i = size_ - 1; i > number_of_child - 1; i--) { //Сдвигаем ключи на единицу вперёд в родительском узле
		keys_[i + 1] = keys_[i];
		values_[i + 1] = values_[i];
	}

	keys_[number_of_child] = child->keys_[order1_ - 1];//Передаём серединное значение ключа в родительский узел
        values_[number_of_child] = child->values_[order1_ - 1];	
	size_++;                                          //Увеличиваем на единицу число ключей в родительском узле
}	 


template <class T, class V>
void BTree<T, V>::InsertKey(const T key, const V &value) {
	if(root_ == nullptr) {
		root_ = new BTreeNode<T, V>(order_, true);
		root_->keys_[0] = key;
		root_->size_ = 1;
		//		root_->parent_ = nullptr;
		return;
	}

	if(root_->size_ == 2 * order_ - 1) {
		BTreeNode<T, V> *new_root = new BTreeNode<T, V>(order_, false);
		new_root->child_[0] = root_;

		new_root->SplitChild(0, root_);
		int i = 0;

		if(new_root->keys_[0] < key) {
			i++;
		}
		new_root->child_[i]->Insert(key, value);

		root_ = new_root;
		return;
	}

	root_->Insert(key, value);
}

template <class T, class V>
void BTreeNode<T, V>::Insert(const T key, const V &value) {
	if(end_ == true) {
		int i = size_ - 1;

		for(; (i > -1) && (keys_[i] > key); i--) {
			keys_[i + 1] = keys_[i];
			values_[i + 1] = values_[i];
		}

		keys_[i + 1] = key;
		values_[i + 1] = value;
		size_++;
		return;
	}

	int i = size_ - 1;

	for(; (i > -1) && (keys_[i] > key); i--) {};

	if(child_[i + 1]->size_ == 2 * order1_ - 1) {
		SplitChild(i + 1, child_[i + 1]);

		if(keys_[i + 1] < key) {
			i++;
		}
	}

	child_[i + 1]->Insert(key, value);
}

template <class T, class V>
void BTreeNode<T, V>::Print() {
	for(int i = 0; i < size_ + 1; i++) {
		if(end_ == false) {
			child_[i]->Print();
		}
		if(i < size_) {
			std::cout << "    " << keys_[i] << std::endl;
		}
	}
}

template <class T, class V>
void BTree<T, V>::PrintAllKeys() {
	if(root_ != nullptr) {
		root_->Print();
	}
}

template <class T, class V>
void BTreeNode<T, V>::Delete() {
/*	if(this == nullptr) {
		return;
	} */
	for(int i = 0; i < size_ + 1; i++) {
		if(end_ == false) {
			child_[i]->Delete();
		}
	}
	delete this;
}

template <class T, class V>
BTree<T, V>::~BTree() {
	if(root_ != nullptr) {
		root_->Delete();
	}
}

template <class T, class V>
int BTreeNode<T, V>::GreaterKey(T &key) {
	int number = 0;
	for(; (number < size_) && (key > keys_[number]); number++) ;
 /*       while(number < size_ && keys_[number] < key) {
		
		//std::cout << " number = " << number << "  key = " << keys_[number] << " size_ = " << size_ << std::endl;
		//if(number == 0) { Print();}
		number++;
	} */
	//std::cout << "-----------------------" << std::endl;
	return number;
}

template <class T, class V>
void BTreeNode<T, V>::RemoveKey(T &key) {
	//std::cout << "-----------------------==" << std::endl;
	int number = GreaterKey(key);
        //std::cout << "-----------------------======" << std::endl;
	if((number < size_) && (keys_[number] == key)) {
		if(end_) {
			EndRemove(number);
			
		}
                else {
		        ComplexRemove(number);
		}
	}
        
	else { //std::cout << "-----------------------" << std::endl; 
		if(end_) {
			//std::cout << "     Ключ отсутсвует в дереве." << std::endl;
			return;
		}

		bool end_index;
		if(number == size_) {
			end_index = true;
		}
		else { end_index = false; }
                //std::cout << "============== " << std::endl;
		if(child_[number]->size_ < order1_) {
			//std::cout << "-----------------------3 size_ = " << size_ << " number = " << number << std::endl;
			AddKey(number);
		}
                //std::cout << "-----------------------4" << std::endl;
		if(number > size_ && end_index) {
			//std::cout << "-----------------------5 size_ = " << size_ << "number = " << number << std::endl;
			child_[number - 1]->RemoveKey(key);
			//std::cout << "-----------------------2" << std::endl;
		}
		else {  //std::cout << "-----------------------1" << std::endl;
			child_[number]->RemoveKey(key);
		}
	}
	return;
}

template <class T, class V>
void BTreeNode<T, V>::EndRemove(int number) {
	for(int i = number; i < size_ - 1; i++) {
		keys_[i] = keys_[i + 1];
		values_[i] = values_[i + 1];
	}

	size_--;
}

template <class T, class V>
void BTreeNode<T, V>::ComplexRemove(int number) {
	T key = keys_[number];

	if(order1_ <= child_[number]->size_) {
		T sup = Supremum(number);
		keys_[number] = sup;
		child_[number]->RemoveKey(sup);
		return;
	}

	if(order1_ <= child_[number + 1]->size_) {
		T inf = Infinum(number);
		keys_[number] = inf;
		child_[number]->RemoveKey(inf);
		return;
	}
        
//	std::cout << "-----------------------3  " << std::endl;
	Union(number);
	child_[number]->RemoveKey(key);
}

template <class T, class V>
T BTreeNode<T, V>::Supremum(int number) {
	BTreeNode *node = child_[number];

	for(; !node->end_; node = node->child_[node->size_]) ;

	return node->keys_[node->size_ - 1];
}

template <class T, class V>
T BTreeNode<T, V>::Infinum(int number) {
	BTreeNode *node = child_[number + 1];

	for(; !node->end_; node = node->child_[0]);

	return node->keys_[0];
}

template <class T, class V>
void BTreeNode<T, V>::Union(int number) {
	BTreeNode *brother1 = child_[number];
	BTreeNode *brother2 = child_[number + 1];

	brother1->keys_[order1_ - 1] = keys_[number];
	brother1->values_[order1_ - 1] = values_[number];

	for(int i = 0; i < brother2->size_; i++) {
		brother1->keys_[i + order1_] = brother2->keys_[i];
	        brother1->values_[i + order1_] = brother2->values_[i];	
	}

	if(!brother1->end_) {
		for(int i = 0; i <= brother2->size_; i++) {
			brother1->child_[i + order1_] = brother2->child_[i];
		}
	}

	for(int i = number + 1; i < size_; i++) {
		keys_[i - 1] = keys_[i];
		values_[i - 1] = values_[i];
	}

	for(int i = number + 2; i <= size_; i++) {
		child_[i - 1] = child_[i];
	}

	size_--;
	brother1->size_ += brother2->size_ + 1;

	delete brother2;
}

template <class T, class V>
void BTreeNode<T, V>::AddKey(int number)
{
	if (number != 0 && child_[number - 1]->size_ >= order1_) {
		Previous(number);
		
	}
	else {
		if (number != size_ && child_[number + 1]->size_ >= order1_) {
			Next(number);
			
		}
		else {
			if (number != size_) { //std::cout << "-----------------------1" << std::endl;
				Union(number);
				
			}
			else {  //std::cout << "-----------------------2" << std::endl;
				Union(number - 1);
			}
		}
	}

}

template <class T, class V>
void BTreeNode<T, V>::Previous(int number)
{

	BTreeNode *brother1 = child_[number];
	BTreeNode *brother2 = child_[number - 1];

	for (int i = brother1->size_ - 1; i >= 0; i--) {
		brother1->keys_[i + 1] = brother1->keys_[i];
		brother1->values_[i + 1] = brother1->values_[i];
	}

	if (!brother1->end_) {
		for(int i = brother1->size_; i >= 0; i--)
			brother1->child_[i + 1] = brother1->child_[i];
	}


	brother1->keys_[0] = keys_[number - 1];
	brother1->values_[0] = values_[number - 1];


	if(!brother1->end_) {
		brother1->child_[0] = brother2->child_[brother2->size_];
	}

	keys_[number - 1] = brother2->keys_[brother2->size_ - 1];
	values_[number - 1] = brother2->values_[brother2->size_ - 1];

	brother1->size_ += 1;
	brother2->size_ -= 1;
}

template <class T, class V>
void BTreeNode<T, V>::Next(int number)
{

	BTreeNode *brother1 = child_[number];
	BTreeNode *brother2 = child_[number+1];


	brother1->keys_[brother1->size_] = keys_[number];
        brother1->values_[brother1->size_] = values_[number];


	if (!brother1->end_) {
		brother1->child_[brother1->size_ + 1] = brother2->child_[0];
	}

	keys_[number] = brother2->keys_[0];
        values_[number] = brother2->values_[0];

	for (int i = 1; i < brother2->size_; i++) {
		brother2->keys_[i - 1] = brother2->keys_[i];
		brother2->values_[i - 1] = brother2->values_[i];
	}

	if (!brother2->end_) {
		for(int i = 1; i <= brother2->size_; i++) {
			brother2->child_[i - 1] = brother2->child_[i];
		}
	}

	brother1->size_ += 1;
	brother2->size_ -= 1;

}





