#include <iostream>
#include "Restaurant.h"
#include "Exception.h"

using namespace std;

int main (void) {

	try {
		Restaurant Res(3);
                Restaurant Res1(3);
                Restaurant Res2;

		Res.Add(14, 84957);
		Res.Add(12, 84951);
		Res.Add(13, 84955);
		Res.Add(1, 84954);
		Res.Add(4, 8495);
		Res.Add(8, 534);
		Res.Add(21, 235);
		Res.Add(20, 325);
		Res.Add(1, 345);
		Res.Add(1, 2353);
		Res.Add(2, 775);
		Res.Add(14, 3467);
		Res.Add(14, 3474);
		Res.Add(14, 3476);
		Res.Add(1, 3456);
                
		Res1 = Res;
		Res2 = Res1;
		Res.AllBookingPrint();
		cout << endl;
		Res2.AllBookingPrint();
	}

	catch(SetException &Exception) {
		cout << "Код ошибки - " << Exception.GetErrorCode() << "." << Exception.GetErrorMessage() << endl;
	}

	return 0;
}

