#include <iostream>
#include "Clock.h"
#include "Exception.h"

using namespace std;

int main (void) {
	try {
		Clocks A(3, 1);
		Clocks B(3, 2);
		Clocks C(3, 3);

		for(int i = 0; i < 6; i++) {
			A.AddOne();
		}
		for(int i = 0; i < 9; i++) {
			B.AddOne();
		}
		for(int i = 0; i < 12; i++) {
			C.AddOne(); 
		}

		B.ReceiveVector(A);
		C.ReceiveVector(A);
		B.PrintVector();
		C.PrintVector();

		int result = MeasureVectors(B, C);

		if(result == NOPE) {
			cout << "NO VECTOR IS LATER" << endl;
		}

		C.ReceiveVector(B);

		result = MeasureVectors(B, C);

		if(result == RIGHT) {
			cout << "RIGHT VECTOR IS LATER" << endl;
		}
                
		
		Clocks D = C;
		D.PrintVector();
		C = D;
		
	}

	catch (SetException & Exception) {
		cerr << "  " << Exception.GetErrorMessage() << " Error code - " << Exception.GetErrorCode() << endl;
	}

	return 0;
}
