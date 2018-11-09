#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include "HashTable.h"

using namespace std;
ulint a, n, y; //g, a, n are user input, r is random number, y is key
long double g, r;

ulint orderofG(){ //performs first step of algorithm, returns order of g
	HashTable ord;
	bool foundDuplicate = false;

	for (int j = 0; j < sqrt(n); j++){
		srand (time(NULL));
		r = rand() % n-1;
		y = pow(g,r);
		y = y % n;
		if (ord.checkExists(y)){
			foundDuplicate = true;
			if ((r - (ord.hash_function(y))) > 0){
				return (r - (ord.hash_function(y)));
			}
			else if ((ord.hash_function(y) - r) > 0){
				return (ord.hash_function(y) - r);
			}
		}
		else{
				ord.insert(y, r);
			}
	}
	if (foundDuplicate == false){
		return n-1;
	}
	//ord.insert(100, 50);
	//ulint test = 100;
	//bool boolTest = ord.checkExists(test);
	//cout << boolTest <<endl;
	return 0;
}
int main(int argc, char const *argv[])
{
	if (argc != 4){
		cout << "Incorrect number of arguments, please enter 3 arguments." << endl;
		return 1;
	}
	stringstream ss;
	for (int i = 1; i < 4; i++){
		ss << argv[i];
		ss << ' ';
	}
	ss >> g >> a >> n;
	ulint orderofg = orderofG();
	cout << "Order of g = " << orderofg << endl;

	//cout << "g = " << g << endl;
	//cout << "a = " << a << endl;
	//cout << "n = " << n << endl;

	
	return 0;
}
