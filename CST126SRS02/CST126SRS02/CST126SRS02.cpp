// CST126SRS02.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void reverseNames(int &numNames, char ** &names, char ** &temp)
{
	//get names from user, put names in ragged array
	names = new char * [numNames] {};
	const int maxLength = 257; //256 + null char
	int i = 0;
	while (i < numNames) {
		//add name to ragged array
		if (cin.peek() == '\n' && i != 0) break; //make sure there are names
		if (!cin.good()) break; //end of file or errors 

		names[i] = new char[maxLength];
		cin >> setw(maxLength) >> names[i];

		//test if length is max
		if (strlen(names[i]) + 1 == maxLength)
		{	//move point to next name if current name is super long
			while (true) {
				char next = cin.get();
				if (!isspace(next) && cin.good()) continue;
				else break;
			}
		}

		i++;
		if (i == numNames) {
			//need a bigger array, reallocation
			numNames *= 2;

			temp = new char *[numNames] {};
			for (int j = 0; j < numNames / 2; j++)
			{
				temp[j] = names[j];
			}

			delete[] names;
			names = temp;
		}
	}

	//output names in reverse order
	for (int i = numNames - 1; i >= 0; i--) {
		if (names[i] != nullptr) cout << names[i] << " ";
		delete[] names[i];
	}
	delete[] names;
	cout << endl;

	if (cin.good()) { //not end of file
					  //recursion
		numNames = 1;
		reverseNames(numNames, names, temp);
	}
}

int main()
{
	int numNames = 1;
	char ** names;
	char ** temp;

	//recursive function, runs until user ends file
	reverseNames(numNames, names, temp);

	return 0;
}
