#include <iostream>
#include <string>
#include <fstream>
#include "BTree.hpp"
#include "Parameter.hpp"
#include "Container.hpp"
#define MAX_KEY_SIZE 5

int main(void) {
	BTree<int, int> Tree(3);

	Tree.InsertKey(1, 1);
	Tree.InsertKey(27, 1);
	Tree.InsertKey(9, 1);
	Tree.InsertKey(6, 1);
	Tree.InsertKey(1123, 1);
	Tree.InsertKey(30, 1);
	Tree.InsertKey(67, 2);
	Tree.InsertKey(27, 1);
	
	Tree.PrintAllKeys();
        

	std::cout << "    Печать с удаленными элементами" << std::endl;
	Tree.Remove(1123);
	Tree.Remove(1);
	Tree.Remove(2); //Проверка на некорректный вход

	Tree.PrintAllKeys();

	std::cout << "-----------------------------------" << std::endl;
        
	BTree<int, int> Tree2(3);
	int key = 0;
	for(int i = 0; i < 10000; i++) {
//                std::cout << i << std::endl;
                key = random() % MAX_KEY_SIZE + 1;
 
		Tree2.NodeSearch(key);
		Tree2.ValueSearch(key);
		if((random() % 3) == 0) {
//			std::cout << "   Добавляемый ключ - " << key << std::endl; 
			Tree2.InsertKey(key, 1);
		}
		else {
//			std::cout << "   Удаляемый ключ - " << key << " ==========" << i << std::endl;
			Tree2.Remove(key);
		}
                
	}
       
	for(int i = 0; i < 10000; i++) {
		key = random() % MAX_KEY_SIZE + 1;
		Tree2.NodeSearch(key);
	} 
	
	std::cout << " Значение по ключу - " << 67 << " равно - " << *Tree.ValueSearch(67) << std::endl;


//        Tree2 = Tree;
//	std::cout << " Значение по ключу - " << 67 << " равно - " << *Tree2.ValueSearch(67) << std::endl;
	return 0;
}
