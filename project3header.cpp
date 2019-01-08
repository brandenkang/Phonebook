#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<time.h>
#include "project3header.h"

using namespace std;

HashNode::HashNode(string key, string value)
{
	this->key = key;
	this->value = value;
};
string HashNode::getKey()
{
	return this->key;
};
string HashNode::getValue()
{
	return this->value;
};
string HashNode::getKeyCity() 
{
	return this->keyCity;
};
string HashNode::getValueName()
{
	return this->valueName;
};
void HashNode:: blankOutEntry() 
{
	this->value = "";
	this->key = ""; 
};


HashMap::HashMap(int capacity) //hashmap constructor 
{
	nodeArray = new HashNode*[capacity]; //node array is a pointer of arrays to hashnodes 
	this->capacity = capacity; //capacity 
	this->size = 0; //size is set to 0 
};

int HashMap::hashCode(const string key) 
{
	long sum=0;
	for(int i=0; i<key.length(); i++)
		sum+=pow(2,i)*int(key[i]);
	return sum%(this->capacity);
};

void HashMap::insert(const string key, const string value) 
{
	HashNode *tempNode= new HashNode(key,value); //create a new hashnode 
	int index = hashCode(key); //run the key through the hashcode to retrieve an index 
	while(nodeArray[index]!=NULL) //linear probing to avoid collision 
	{
		index = (index+1) % this->capacity;
	}

	nodeArray[index] = tempNode; //insert tempnode into hashmap 
	this->size++; //increment size 
};

//how to implement remove function 
void HashMap::remove(const string key)
{
	int index = hashCode(key); //run key through hashmap to get the index 
	while (nodeArray[index]!=NULL) { //if we find an element with the key we are looking for 
		if (nodeArray[index]->getKey() == key)  
		{
			nodeArray[index]->blankOutEntry(); //blank out the keys and values of the element 
			cout << key << " has been deleted." << endl; 
			break;
		}
	}
	if (nodeArray[index]==NULL) {cout << "Record Not Found." << endl;} //if there is nothing there return error message
};

string HashMap::search(const string key)
{
	int index = hashCode(key);
	int counter = 0;
	// timing code learned from https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
	clock_t start, end;
    double cpu_time_used;
 	start = clock();
	while(nodeArray[index] != NULL && counter < this->capacity) //if we find an element with the key we are looking for 
	{
		if (nodeArray[index]->getKey() == key)
		{
			end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			printf("Took %f seconds to complete\n", cpu_time_used);
			return string(nodeArray[index]->getValue()); //+"   (comparisions = "+cnt.str()+")";
		}
		//otherwise
		index = (index+1)%this->capacity;
	}
	// if (nodeArray[index] == NULL) {
	// end = clock();
	// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	// printf("Wasted %f seconds on a pointless search\n", cpu_time_used);
	// }
	return "Record Not Found.";
};
void HashMap::dump() {
	vector<string> dumpVector;
	string key;
	string keyFirst;
	string keyLast;
	string keyValueToken;
	for (int i=0; i<capacity; i++) { //read through the hash map 
		if (nodeArray[i]!= NULL) { //if we encounter a non=empty node 
			int count = 0; 
			key = nodeArray[i]->getKey(); //get the key 
			for (int i=0; i<key.length(); i++){ //divide the key into first and last name 
				if(key[i] == ' ') {count ++;}
				if (count == 0) {
					keyFirst = key.substr(0,i+1);
					keyLast = key.substr(i+2,key.length());
				}
			}
			//create a token storing last name first name and all remaining user data
			keyValueToken = keyLast + " " + keyFirst + nodeArray[i]->getValue();
			dumpVector.push_back(keyValueToken); //store it into a vector 
		}
	}
	sort(dumpVector.begin(), dumpVector.end()); //sort vector using std::sort
	ofstream myfile("dumpfile.txt"); //create an output text file 
	for (int i=0; i<dumpVector.size(); i++) {
		cout << dumpVector.at(i) << endl;
		if (myfile.is_open()){
		myfile << dumpVector.at(i) << endl; //print sorted list of customer data 
	}
	}
};


// void HashMap::allinCity(string key) { 
// 	string z = "";
// 	clock_t start, end;
//     double cpu_time_used;
//  	start = clock();
// 	for (int i=0; i<capacity; i++) {
// 		if (nodeArray[i]!=NULL) {
// 			if (nodeArray[i]->getValue().find(key) != std::string::npos) {
// 				z += nodeArray[i]->getKey() + '\n'; 
// 			}
// 			// else {
// 			// 	myCityHashMap.insert(keyCity, key); 
// 			// }
// 		}
// 	}
// 	end = clock();
// 	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
// 	printf("Took %f seconds to complete\n", cpu_time_used);
// 	cout << z << endl;

// 	ofstream myfile("cityFile.txt"); 
// 		if (myfile.is_open()){
// 			myfile << z << endl;
// 		}
// 	// 	// myCityHashMap.insert(keyCity, z);
// 	// return z;
// };

int HashMap::getSize() 
{
	return this->size;
};

HashMap::~HashMap()
{
	delete[] this->nodeArray;
};


CityHashNode::CityHashNode(string keyCity, string cityMapValue) { //CityHashNode class with key, value and pointer to next node
    this->keyCity = keyCity; 
    this->cityMapValue = cityMapValue;
    this->next = NULL;
};
string CityHashNode::getValue()
{
	return this->cityMapValue;
}
string CityHashNode::getKey()
{
	return this->keyCity; 
}

CityHashMap::CityHashMap(int size) {
	this->size = size;
    hashtable = new CityHashNode*[size];
    for (int i = 0; i < size; i++) {
        hashtable[i] = NULL;
    }
}

int CityHashMap::CityHashCode(string keyCity) { 
    long sum=0;
        for(int i=0; i<keyCity.length(); i++)
            sum+=pow(2,i)*int(keyCity[i]);
        return sum%(size);
};

void CityHashMap::allinCity(string keyCity){ //print names of all customers residing in keyCity 
	int hashIndex = CityHashCode(keyCity); //run keyCity through hashcode to retrieve index 
	CityHashNode* cNode = hashtable[hashIndex]; //create a pointer to the hash node at the index of hashmap 
	ofstream myfile("allinCityFile.txt"); //open output file 
	if (myfile.is_open()){
	while (cNode!=NULL){
		if (keyCity == cNode->getKey()) { 
			cout << cNode->getValue() << endl;
			myfile << cNode->getValue() << endl; //print value of node with key keyCity onto file 
		}
		cNode = cNode->next; //move down the chain of nodes to find other values with same key
	}
	}
};


void CityHashMap::Insert(string keyCity, string cityMapValue) {
    int hashIndex = CityHashCode(keyCity);
    CityHashNode* prev = NULL;
    CityHashNode* cNode = hashtable[hashIndex];
    //if there is already a node at the hashIndex, move it to the end of the list which is NULL
    //move prev along to the index one before cNode
    while (cNode != NULL) { 
        prev = cNode;
        cNode = cNode->next;
    }
    //create a new node at the end of the list 
    if (cNode == NULL) { 
        cNode = new CityHashNode(keyCity, cityMapValue);
        //if prev is NULL, it means that there is nothing in the place we want to insert cNode
        //just insert cNode at hashtable[hashIndex]
        if (prev == NULL) {
            hashtable[hashIndex] = cNode;
        }
        else {
        //if there is something at prev, it means that there is already something in the place we want to insert cNode
        //use chaining to place cNode at prev->next 
            prev->next = cNode;
        }
    }
    else {
        cNode->cityMapValue = cityMapValue;
    }
};
CityHashMap::~CityHashMap() {
    for (int i = 0; i < size; ++i) {   
        CityHashNode* cNode = hashtable[i];
        while (cNode != NULL) {
            CityHashNode* prev = cNode;
            cNode = cNode->next;
            delete prev;
        }
    }
    // delete[] hashtable;
};
