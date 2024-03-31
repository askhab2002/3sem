#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "BTree.hpp"
#include "Parameter.hpp"

#define ERROR -1
#define TRUE 1

struct Container {
	BTree<std::string, Parameter> Tree{3};

	Container() { 
//		BTree<std::string, Parameter> Tree(3);
	}
	Container(const Container &Con) = delete;

	void InsertInt(std::string key, int value) {
		Tree.InsertKey(key, Parameter(value));
	}
	void InsertDouble(std::string key, double value) {
		Tree.InsertKey(key, Parameter(value));
	}
	void InsertIntArray(std::string key, int *value, int length) {
		Tree.InsertKey(key, Parameter(value, length));
	}
	void InsertDoubleArray(std::string key, double *value, int length) {
		Tree.InsertKey(key, Parameter(value, length));
	}
	void InsertString(std::string key, std::string value) {
		Tree.InsertKey(key, Parameter(value));
	}

	void DeleteKey(std::string key) {
		Tree.Remove(key);
	}

	int GetInt(std::string key, int &error) {
		Parameter *value = Tree.ValueSearch(key);

		if (value == nullptr) {
			error = ERROR;
			return 0;
		}

		if (value->TypeIndex != IntType) { 
		        error = ERROR; 
		}
		error = TRUE;
	        return value->ParInt;
	}

	double GetDouble(std::string key, int &error) {
		Parameter *value = Tree.ValueSearch(key);

		if (value == nullptr) {
			error = ERROR;
			return 0;
		}

	        if (value->TypeIndex != DoubleType) { 
			error = ERROR; 
		}
		error = TRUE;
		return value->ParDouble;
	}

	const int *GetIntArray(std::string key, int *length, int &error) {
                Parameter *value = Tree.ValueSearch(key);

                if (value == nullptr) {
                        error = ERROR;
                        return nullptr;
                }

                if (value->TypeIndex != IntArrayType) { 
			error = ERROR; 
		}
                error = TRUE;
                *length = value->Length;
                return value->ParIntArray;
        }

        const double *GetDoubleArray(std::string key, int *length, int &error) {
                Parameter *value = Tree.ValueSearch(key);

                if (value == nullptr) {
                        error = ERROR;
                        return nullptr;
                }

                if (value->TypeIndex != DoubleArrayType) { 
			error = ERROR; 
		}
                error = TRUE;
                *length = value->Length;
                return value->ParDoubleArray;
        }

	std::string GetString(std::string key, int &error) {
                Parameter *value = Tree.ValueSearch(key);

                if (value == nullptr) {
                        error = ERROR;
                        return nullptr;
                }

                if (value->TypeIndex != StringType) { 
			error = ERROR; 
		}
                error = TRUE;
                return value->ParString;
        }

        bool ReadFrom(std::string file_name) {
		std::ifstream inp(file_name);
                if(inp.is_open()) {
                        while (!inp.eof()) {
				std::string word;
				std::string k;
                                inp >> word;
                                inp >> k;
                                if (k == "=i") {
                                        int i; 
					inp >> i; 
                                        InsertInt(word, i); 
                                }
                                if (k == "=d") {
                                        double i; 
					inp >> i; 
                                        InsertDouble(word, i);
                                }
                                if ( k == "=s") {
					std::string i; 
					inp >> i;
                                        InsertString(word, i);
                                }
                                if (k == "=ai") {
                                        int i; 
					inp >> i;
                                        int len = i; 
					int *array = new int[len];
                                        for (int k = 0; k < len; ++k) {
                                                inp >> i;
                                                array[k] = i;
                                        }
                                        InsertIntArray(word, array, len);
                                        delete [] array;
                                }
                                if (k == "=ad") {
                                        int i; 
					inp >> i;
                                        int len = i; 
					double *array = new double[len];
                                        double d;
                                        for (int k = 0; k < len; ++k) {
                                                inp >> d;
                                                array[k] = d;
                                        }
                                        InsertDoubleArray(word, array, len);
                                        delete [] array;
                                }
                        }
                }
                else {
			std::cout << "cant open file\n"; 
                        inp.close(); return 0; 
                }
                inp.close();
                return 1;
        }
};	        


