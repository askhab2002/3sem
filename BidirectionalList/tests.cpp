#include <iostream>
#include <cmath>
#include "Exception.h"
#include "BidirectionalList.hpp"


int main(void) {
	try {	
		BidirectionalList<int> List1;
                BidirectionalList<int> List3;

		for(int i = 120; i > 100; i--) {   
			List1.AddNext(i);
		}
		List1.Begin();
		for(int i = 0; i < 9; i++) {
			List1.Next();
		}
		
		std::cout << List1.GetCurrent() << std::endl;

		for(int i = 0; i < 9; i++) {
			List1.Previous();  
		}    

		std::cout << List1.GetCurrent() << std::endl << std::endl;
		std::cout << "    Проверка на сортировку на целых числах." << std::endl;
		List1.SortIncreasing();

		List1.Begin();
		int size = List1.GetSize();
		for(int i = 0; i < size; i++) {
			std::cout << List1.GetCurrent() << std::endl;
			List1.Next();	
		}

                List1.Begin();    
		List3 = List1;
		
                List1.Begin();
		List3.Begin();
                BidirectionalList<int> List4;
		List4 = List3 + List1;
		std::cout << "    Проверка на сложение." << std::endl;

		size = List4.GetSize();
		List4.Begin();
                for(int i = 0; i < size; i++) {
                        std::cout << List4.GetCurrent() << std::endl;
                        List4.Next();
                }

                List4.SortIncreasing();
		List4.Begin();

		std::cout << "---------Печать--------------" << std::endl;
		
		BidirectionalList<int>::Iterator iter(&List4);
		
	        for(int i = 0; iter.IsThere(); ++iter, i++) {
			std::cout << *iter << std::endl;
	        }	
		std::cout << "-----------------------" << std::endl;

        } catch (SetException & Exception) {
                std::cerr << "  Исключение с целыми числами!" << std::endl;
                std::cerr << "  " << Exception.GetErrorMessage() << " Error code - " << Exception.GetErrorCode() << std::endl;
        }

        try {
		std::cout << "    Те же проверки, только для чисел с плавающей запятой." << std::endl;

		BidirectionalList<double> List2;

		for(int i = 20; i > 0; i--) {
			List2.AddNext(sin(i));
		}
		List2.Begin();
		for(int i = 0; i < 9; i++) {
			List2.Next();
		}
		
		std::cout << List2.GetCurrent() << std::endl;

		for(int i = 0; i < 9; i++) {
			List2.Previous();
		}

		std::cout << List2.GetCurrent() << std::endl << std::endl;
		std::cout << "    Проверка на сортировку на числах с плавающей запятой." << std::endl;
		List2.SortIncreasing();

		List2.Begin();
		int size1 = List2.GetSize();
		for(int i = 0; i < size1; i++) {
			std::cout << List2.GetCurrent() << std::endl;
			List2.Next();
		}

		BidirectionalList<int> List5;
		List5.GetCurrent();

	} catch (SetException & Exception) {
		std::cerr << "  Ошибка в примере с плавающими числами!" << std::endl;
		std::cerr << "  " << Exception.GetErrorMessage() << " Error code - " << Exception.GetErrorCode() << std::endl;
	}

	try {
                BidirectionalList<int> List5;
                List5.GetCurrent();

	} catch (SetException & Exception) {
                std::cerr << "  Исключение словили при использовании GetCurrent()!" << std::endl;
	        std::cerr << "  " << Exception.GetErrorMessage() << " Error code - " << Exception.GetErrorCode() << std::endl;	
	}	
        	
	return 0;
}
