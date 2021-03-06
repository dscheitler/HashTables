#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <list>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY }; // extend if necessary

typedef unsigned long ulint;

class HashTable {
  typedef vector <list<HashNode> > Table;
  Table *table; // size of table is stored in the Table data structure
  size_t num;   // number of entries in the HashTable;

public:
  HashTable();       // constructor, initializes table of size 11;
  HashTable(size_t); // constructor, requires size of table as arg
  ~HashTable();      // deconstructor

  size_t size(); // returns size of the hash table (number of buckets)
  bool checkExists(ulint); //returns true if key already exists within hashtable
  size_t hash_function(ulint);  // the table's hash function
  ulint getValue(ulint);    // find and return data associated with key

  void insert(ulint,ulint); // insert data associated with key into table
  void erase(ulint);        // remove key and associated data from table

  void rehash(size_t); // sets a new size for the hash table, rehashes the hash table 

  // extend if necessary
};

/* Implement the 
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/
HashTable::HashTable() {
	cout << "Constructing";
	try{
		this->table = new Table(11);
	}
	catch(bad_alloc& e){
		cout << "Out of memory, cannot allocate space for table" << endl;
	}
	this->num = 0;
	cout << " a hash table of size " << this->size() << endl;

}
HashTable::HashTable(size_t size) {
	cout << "Constructing";
	try{
		this->table = new Table(size);
	}
	catch(bad_alloc& e){
		cout << "Out of memory, cannot allocate space for table" << endl;
	}
	this->num = 0;
	cout << " a hash table of size " << this->size() << endl;
}
HashTable::~HashTable(){
	//Hashtable destroyed
}
size_t HashTable::size()
{
	return this->table->size();
}
bool HashTable::checkExists(ulint key){
	ulint index = key % this->table->size(); //get index of table
	if (!(this->table->at(index).empty())){ //if not empty
		auto it = this->table->at(index).begin();
		auto itEnd = this->table->at(index).end();
		while (it->getKey() != key && it != itEnd)
		{
			it++;
		}
		if (it->getKey() == key){ //if key is found
			return true;
		}
	}
	return false;
	}
size_t HashTable::hash_function(ulint key)
{
	ulint index = key % this->table->size(); //get index of table
	//if (!(this->table->at(index).empty()){
	//	throw HashTableError(2);
	//}
	return index;
}
ulint HashTable::getValue(ulint key)
{
	ulint index = this->hash_function(key); //get index of table
	ulint val;
	if (!(this->table->at(index).empty())){
		auto it = this->table->at(index).begin();
		auto itEnd = this->table->at(index).end();
		while (it->getKey() != key && it != itEnd)
		{
			it++;
		}
		val = it->getValue(); //val is value connected to key passed as a parameter
	}
	else
	{
		throw HashTableError(1);
	}
	return val;
}
void HashTable::insert(ulint key, ulint value)
{
	ulint index = this->hash_function(key);
	if (!(this->table->at(index).empty())){
		this->table->at(index).emplace_back(key, value); //creates hashnode at back if not empty
	}
	else{
		this->table->at(index).emplace_front(key, value); //creates hashnode at front if empty
	}	
	this->num = num+1;

	if (this->num == this->table->size()/2){ //if num of entries equals half size
		rehash(this->table->size()*2); //increases table size by x2 and redoes the indices
	}
	//causes test3.cpp to work and test2.cpp to break
	//if (this->num == this->table->size())
	//{
	//	this->table->resize(size()+1);
	//}	
}
void HashTable::erase(ulint key)
{
	ulint index = this->hash_function(key);
	//auto it = this->table->at(index).begin();

	if (this->table->at(index).size() > 1){ //remove individual node if list size > 1

		auto it = this->table->at(index).begin();
		while (it->getKey() != key)
		{
			it++;
		}
		this->table->at(index).erase(it);
	}
	else{
		this->table->at(index).clear(); //else remove entire list
	}
	this->num = num-1;
}
void HashTable::rehash(size_t tableSize)
{
	int x = 0;
	vector<HashNode> tempVector; //stores nodes temporarily
	auto it = table->begin();
	auto itEnd = table->end();
	while (it != itEnd)
	{
		if (it->size() == 1)
		{
			tempVector.emplace_back(it->front().getKey(), it->front().getValue());
		}
		else if (it->size() > 1)
		{
			auto itList = this->table->at(x).begin();
			auto itEnd = this->table->at(x).end();
			while (itList != itEnd)
			{
				tempVector.emplace_back(itList->getKey(), itList->getValue());
				itList++;
			}
		}
		else{
			//do nothing
		}
		it++;
		x++;
	}
	this->table = new Table(tableSize); //create new table to replace old one
	cout << "Rehashing table:" << endl;
	for (ulint j = 0; j < tempVector.size(); j++){ //insert all old nodes into new table
		this->insert(tempVector.at(j).getKey(), tempVector.at(j).getValue());
	}
	cout << "Finished rehashing." << endl;
	//this->table->resize(tableSize);
}
#endif
