 #include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<sstream>
#include <time.h>

using namespace std;

class HashNode
{
	private:
		string key;
		string value;
		string keyCity; 
		string valueName; 
	public:
		HashNode(string key, string value);
		string getKey();
		string getValue();
		string getKeyCity();
		string getValueName(); 
		void blankOutEntry();
};

class HashMap
{
	public:
		HashNode **nodeArray;		// Array of Pointers to Hash Nodes
		int size;					//Current Size of HashMap
		int capacity;				// Total Capacity of HashMap
		HashMap(int capacity);
		int hashCode(const string key);
		void insert(const string key, const string value);
		//how to implement remove function 
		void remove(const string key);
		string search(const string key);
		void dump();
		void allinCity(string key);
		int getSize();
		~HashMap();
};

class CityHashNode
{
public:
    string keyCity;
	string cityMapValue;
	CityHashNode* next;
    CityHashNode(string keyCity, string cityMapValue);
    string getValue();
	string getKey();
};
 
class CityHashMap {
private:
    CityHashNode** hashtable;
    int size;
public:
    CityHashMap(int size);
    int CityHashCode(string keyCity);
    void allinCity(string keyCity);
    void Insert(string keyCity, string cityMapValue);
    ~CityHashMap();
};
