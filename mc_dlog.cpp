#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include "HashTable.h"

using namespace std;
ulint g, a, n, r, y; //g, a, n are user input (base, exponent, mod), r is random number, y is key


ulint squareMultiply(ulint base, ulint exponent, ulint mod){
	ulint x,e,n,result;
	x = base;
	e = exponent;
	n = mod;
	result = 1;
	while (e > 0)
    {
		if (e % 2 == 1){
			result = (result * x) % n;
		}
    		e = e >> 1;
			x = (x * x) % n;

}

    return result;
}
ulint powerOf(ulint base, ulint exponent){
	ulint result = base;
	while (exponent > 1){
		result = result * base;
		exponent--;
	}
	if (exponent == 0){
		result = 1;
	}
	return result;
}
ulint orderofG(){ //performs first step of algorithm, returns order of g
	HashTable ord;
	bool foundDuplicate = false;

	for (int j = 0; j < sqrt(n); j++){
		srand (time(NULL));
		r = rand() % n-1;
		y = squareMultiply(g, r, n);
		//ulint index = ord.hash_function(y);
		if (ord.checkExists(y)){
			foundDuplicate = true;
			if (r - (ord.getValue(y)) > 0){
				return (r - (ord.getValue(y)));
			}
			else if ((ord.getValue(y)) - r > 0){
				return ((ord.getValue(y)) - r);
			}
		}
		else{
				ord.insert(y, r);
			}
	}
	if (foundDuplicate == false){
		return n-1;
	}

	return 0;
}

long discreteLog(){
	HashTable A, B;
	//ulint index;
	for (int i = 0; i < sqrt(n); i++){
		srand (time(NULL));
		r = rand() % n-1;
		y = squareMultiply(g, r, n);
		y = (a*y);
		//index = B.hash_function(y);
		if (B.checkExists(y)){
			return (B.getValue(y)) -r;
		}
		else{
			A.insert(y,r);
		}
		srand (time(NULL));
		r = rand() % n-1;
		y = powerOf(g,r);
		//index = A.hash_function(y);
		if (A.checkExists(y)){
			return r - (A.getValue(y));
		}
		else{
			B.insert(y,r);
		}
	}
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
	long orderofg = orderofG();
	cout << "Order of g = " << orderofg << endl;

	long result = discreteLog();
	result = result % orderofg;

	if (result < 0){
		result = result + orderofg;
	}

	cout << "Final result = " << result << endl;
	
	return 0;
}
