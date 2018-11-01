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
  HashTable();       // constructor, initializes table of size 1;
  HashTable(size_t); // constructor, requires size of table as arg
  ~HashTable();      // deconstructor

  size_t size(); // returns size of the hash table (number of buckets)
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
	Table t(11);
	this->num = 0;
	cout << " a hash table of size " << t.size() << endl;

}
HashTable::HashTable(size_t size) {
	cout << "Constructing";
	Table t(size);
	this->num = 0;
	cout << " a hash table of size " << t.size() << endl;
}
HashTable::~HashTable(){
	//Hashtable destroyed
}
size_t HashTable::size()
{

}
size_t HashTable::hash_function(ulint)
{
	size_t placeholder;
	return placeholder;
}
ulint HashTable::getValue(ulint)
{
	ulint placeholder;
	return placeholder;
}
void HashTable::insert(ulint, ulint)
{
	
}
void HashTable::erase(ulint)
{
	
}
void HashTable::rehash(size_t)
{
	
}
#endif
