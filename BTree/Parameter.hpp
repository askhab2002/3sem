#pragma once
#include <iostream>
#include <string>

#define IntType 1
#define DoubleType 2
#define IntArrayType 3
#define DoubleArrayType 4
#define StringType 5

class Parameter {
	public:
		int ParInt;
		double ParDouble;
		int *ParIntArray;
		double *ParDoubleArray;
		std::string ParString;

		int Length;
		int TypeIndex;
		
	public:
		Parameter() {
			TypeIndex = IntType;
			ParInt = 0;
		}
		Parameter(int value);
		Parameter(double value);
		Parameter(int *value, int length);
		Parameter(double *value, int length);
		Parameter(std::string value);
		Parameter(const Parameter &Par);
		~Parameter();

		Parameter &operator=(const Parameter& Par);
                
		friend std::ostream & operator<<(std::ostream &stream, const Parameter &par);
};

Parameter::Parameter(int value) {
	TypeIndex = IntType;
	ParInt = value;
}

Parameter::Parameter(double value) {
	TypeIndex = DoubleType;
	ParDouble = value;
}

Parameter::Parameter(int *value, int length) {
	TypeIndex = IntArrayType;
	Length = length;
	ParIntArray = new int[Length];

	for(int i = 0; i < Length; i++) {
		ParIntArray[i] = value[i];
	}
}

Parameter::Parameter(double *value, int length) {
	TypeIndex = DoubleArrayType;
	Length = length;
	ParDoubleArray = new double[Length];

	for(int i = 0; i < Length; i++) {
		ParDoubleArray[i] = value[i];
	}
}

Parameter::Parameter(std::string value) {
	TypeIndex = StringType;
	ParString = value;
}

Parameter::Parameter(const Parameter &Par) {
	if(Par.TypeIndex == IntType) {
		TypeIndex = Par.TypeIndex;
		ParInt = Par.ParInt;
	}
	if(Par.TypeIndex == DoubleType) {
		TypeIndex = Par.TypeIndex;
		ParDouble = Par.ParDouble;
	}
	if(Par.TypeIndex == IntArrayType) {
		TypeIndex = Par.TypeIndex;
		Length = Par.Length;

		ParIntArray = new int[Length];
		for(int i = 0; i < Length; i++) {
			ParIntArray[i] = Par.ParIntArray[i];
		}
	}
	if(Par.TypeIndex == DoubleArrayType) {
		TypeIndex = Par.TypeIndex;
		Length = Par.Length;

		ParDoubleArray = new double[Length];
		for(int i = 0; i < Length; i++) {
			ParDoubleArray[i] = Par.ParDoubleArray[i];
		}
	}
	if(Par.TypeIndex == StringType) {
	       TypeIndex = Par.TypeIndex;
               ParString = Par.ParString;
        }
}	

Parameter::~Parameter() {
	if(TypeIndex == IntArrayType) {
		delete [] ParIntArray;
	}
	if(TypeIndex == DoubleArrayType) {
		delete [] ParDoubleArray;
	}
}

Parameter &Parameter::operator=(const Parameter& Par) {
	if(&Par == this) {
		return *this;
	}

        if(TypeIndex == IntArrayType) {
                delete [] ParIntArray;
        }
        if(TypeIndex == DoubleArrayType) {
                delete [] ParDoubleArray;
        }
    

	if(Par.TypeIndex == IntType) {
	        TypeIndex = IntType;
                ParInt = Par.ParInt;
        }	       
	if(Par.TypeIndex == DoubleType) {
		TypeIndex = DoubleType;
		ParDouble = Par.ParDouble;
	}
	if(Par.TypeIndex == IntArrayType) {
		TypeIndex = IntArrayType;
		Length = Par.Length;
                ParIntArray = new int[Length];

		for(int i = 0; i < Length; i++) {
                        ParIntArray[i] = Par.ParIntArray[i];
		}         
	}
	if(Par.TypeIndex == DoubleArrayType) {
		TypeIndex = DoubleArrayType;
		Length = Par.Length;
		ParDoubleArray = new double[Length];

                for(int i = 0; i < Length; i++) {
                        ParDoubleArray[i] = Par.ParDoubleArray[i];
                }
	}
	if(Par.TypeIndex == StringType) {
		TypeIndex = StringType;
		ParString = Par.ParString;
	}

	return *this;
}

std::ostream &operator<<(std::ostream &stream, const Parameter &par) {
        switch (par.TypeIndex) {
                case IntType:
                        std::cout << par.ParInt;
                        break;
                case DoubleType:
                        std::cout << par.ParDouble;
                        break;
                case DoubleArrayType:
                        std::cout << "[";
                        if (par.Length == 0) { std::cout << "empty array]"; break; }
                        for(int k = 0; k < par.Length - 1; ++k) {
                                std::cout << par.ParDoubleArray[k] << " ";
                        }
                        std::cout << par.ParDoubleArray[par.Length - 1] << "]";
                        break;
                case IntArrayType:
                        std::cout << "[";
                        if (par.Length == 0) { std::cout << "empty array]"; break; }
                        for(int k = 0; k < par.Length - 1; ++k) {
                                std::cout << par.ParIntArray[k] << " ";
                        }
                        std::cout << par.ParIntArray[par.Length - 1] << "]";
                        break;
                case StringType:
                        std::cout << par.ParString;
                        break;
        }
        return stream;
}
