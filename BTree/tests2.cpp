#include <iostream>
#include <fstream>
#include <string.h>
#include "Parameter.hpp"
#include "BTree.hpp"
#include "Container.hpp"

std::string RandomString();
int *RandomArray(int *len);

int main(void) {
	Container Con; /*
	Con.InsertInt("ggwergewgge", 3241);
	return 0;
}
*/
	int some_value;
	int error = 0;
	std::string some_string;
	std::string some_value2;

	for(int i = 0; i < 1000; i++) {
		some_string = RandomString();
		some_value = random() % 50 + 1;

		Con.InsertInt(some_string, some_value);
		if(random() % 3 == 0) {
			Con.GetInt(some_string, error);
			Con.DeleteKey(some_string);
			Con.DeleteKey(RandomString());
		}
	}

        for(int i = 0; i < 1000; i++) {
                some_string = RandomString();
                some_value2 = RandomString();

                Con.InsertString(some_string, some_value2);
                if(random() % 3 == 0) {
			Con.GetString(some_string, error);
                        Con.DeleteKey(some_string);
                        Con.DeleteKey(RandomString());
                }
        }
        
        int *some_array;
	int len;

        for(int i = 0; i < 100; i++) {
	        some_string = RandomString();
		some_array = RandomArray(&len);

		Con.InsertIntArray(some_string, some_array, len);
		delete [] some_array;
		if(random() % 3 == 0) {
			Con.GetIntArray(some_string, &len, error);
			Con.DeleteKey(some_string);
			Con.DeleteKey(RandomString());
		}
        }

        Container Con2;
	Con2.ReadFrom("inp.txt");

	return 0;
}

std::string RandomString() {
	int length = random() % 30;
        char value = 65;
	std::string key;
        key.resize(length);

	for(int i = 0; i < length; i++) {
 	        value = 65 + (random() % 26);
                key[i] = value;
	}

	return key;
}
          
int *RandomArray(int *len) {
	int length = random() % 30 + 1;
        int value = 0;
        int *key = new int[length];
        *len = length;

	for(int i = 0; i < *len; i++) {
		value = random() % 100 + 1;
                key[i] = value;
	}

	return key;
}
