#include <iostream>
#include "IntegerSet.h"
#include "IntegerSetException.h"

using namespace std;

int main() {
//Блок проверки на возможность крашнуть программу
    
    try {
        int q[5] = {1242424, 547485745, 1, 4, 3};
	int w[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int *e = new int[100];
        for(int i = 0; i < 100; i++) {
            e[i] = i * i + 7 * i;
	}

        IntegerSet Q(100, q, 5);
	IntegerSet W(100, w, 9);
        IntegerSet E(200, e, 100);
        IntegerSet R;

	R = Q + E;
	E + 1;
	W + 4;
        R = W + R;
        R = Q + W;

	R.PrintCardinal();
	R.PrintMembers();
        int a = E.GetCardinal();
        int *t = E.GetMembers();

        	
        
        delete [] e;

        E.SetCardinal(-10);
        
    }

    catch(SetException &Exception) {
        cerr << "  " << Exception.GetErrorMessage() << " Error code - " << Exception.GetErrorCode() << endl;
    }


//Блок проверки корректности операций
    cout << endl;

    IntegerSet A;
  
    int *neophytes =  new int[6];
    int *neophytes2 = new int[5];

    for(int i = 0; i < 6; i++) {
        neophytes[i] = i;
    }

    for(int i = 0; i < 5; i++) {
        neophytes2[i] = i + 6;
    }

    IntegerSet B(100, neophytes, 6);
    IntegerSet C(100, neophytes2, 5);

    A.PrintCardinal();
    A.PrintMembers();

    B.PrintCardinal();
    B.PrintMembers();

    IntegerSet D;
    IntegerSet E;

    D = B + C; // ОбЪединение
    D = D + C; 

    D.PrintCardinal();
    D.PrintMembers();
    
    C + 451532;
    C + 451532;

    C.PrintCardinal();
    C.PrintMembers();

    int *array = C.GetMembers();
    int lenth = C.GetCardinal();
    
    cout << "  Проверка на получение данных из объекта класса:" << endl;

    for(int i = 0; i < lenth; i++) {
        cout << "    " << array[i] ;
    }
    cout << endl;

    delete [] neophytes;
    delete [] neophytes2;
    return 0;

}

