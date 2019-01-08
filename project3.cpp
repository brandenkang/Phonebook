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
int main(void)
{
	string filename;
	cin >> filename;
	cout<<endl;

	ifstream fin; 
	fin.open(filename.c_str());
	if(!fin){
		cout<<"Cannot open the file";
		exit(-1);
	}
	string key, value;
	string line; 
	string init; //user input to initialize program 
	cout << "Should I initialize the program?" << endl; 
	cin >> init; 
	if (init == "init") {
		HashMap myHashMap(5000);
		// CityHashMap myCityHashMap; 
		// myCityHashMap = CityHashMap();
		while(!fin.eof())
		{
			string line; 
			getline(fin, line); 
			string key; //key of first hashmap //first and last name 
			string value; //value of first hashmap //all remaining user data 
			int count = 0; //counter to count number of spaces 
			for (int i=0; i<line.length(); i++) {
				if (line[i] == ' ') {count ++;}
				if (count == 1) { //when we reach the second blank space divide line into two substrings 
					key = line.substr(0,i+1); //first and last name 
					value = line.substr(i+1,line.length()); //remaining data 
				}
			}
			myHashMap.insert(key,value); //insert into first hashmap 
		}
		fin.close();

		cout<<"Hash Map size = "<<myHashMap.getSize()<<endl; //hashmap size after inserting keys and values 

		string choice;
		string customerData;
		string nameFind;
		string nameDelete;
		string key1;
		string value1;
		int count = 0;
		while(true)
		{
			// cout << "What do you want to do?: " << endl;
			cout<<"What do you want to do?: " << endl << "1. Add Customer (add)" << endl << "2. Find Customer (find)" << endl 
			<< "3. Delete Customer (delete)" << endl << "4. Find All Customers in a City (allinCity)" << endl
			<< "5. Load Customer Database (load)" << endl << "6. Save Customer Database to a file (dump)" << endl << "7. Quit" << endl;
			getline(cin,choice);		
			if (choice == "quit") {
				break;
			}
			//add a customer into the fonbook
			else if (choice == "add") {
				cout << "Please input the data of the customer: " << endl;
				getline(cin,customerData); 
				for (int i=0; i<customerData.length(); i++) {
					if (customerData[i] == ' ') {
						count++;
					}
					if (count == 1) { //when we reach the second blank space divide line into two substrings
						key1 = customerData.substr(0,i+1); //first and last name 
						value1 = customerData.substr(i+1,customerData.length()); //remaining user data 
					}
				}
				if (myHashMap.search(key1) == "Record Not Found.") { //if first and last name not in the map already 
					myHashMap.insert(key1,value1); //insert new key and value 
					cout << key1 << " has been added." << endl;
				}
				else {cout << "This person already exists." << endl;} //if person already exists print error message 
			}
			//find a customer in the fonbook
			else if (choice == "find") {
				cout << "Please input the name of the person you want to find: " << endl; 
				getline(cin, nameFind); 
				string sResult = myHashMap.search(nameFind); //look for person in hashmap 
				cout << nameFind << sResult << endl; //print user name and data 
			}
			//delete a customer from the fonbook
			else if (choice == "delete") {
				cout << "Please input the name of the person you want to delete: " << endl;
				getline(cin, nameDelete); 
				myHashMap.remove(nameDelete);
			}
			//dump content of hash map into file 
			//sort the content of the file according to the last name of the customers in alpha-numerically increasing order
			else if (choice == "dump") {
				myHashMap.dump();
			}
			//read into the hash map the content of the file again
			else if (choice == "load") {
				string filename; 
				ifstream fin;
				cout << "Enter the name of the file you want to load (i.e. 'file.txt')" << endl;
				cin >> filename; 
				fin.open(filename); //open user input file 
				while(!fin.eof()){ 
					getline(fin, line);
					int count = 0;
					for (int i = 0; i<line.length(); i++) { //read through every line and retrieve keys and values 
						if (line[i] == ' ') {count ++;}
						if (count == 1) {
							key = line.substr(0,i+1);
							value = line.substr(i+1,line.length());
						}
					}
					myHashMap.insert(key,value); //insert new keys and values from file into hashmap 
				}
				fin.close(); 
				cout << "Hash Map size = " << myHashMap.getSize() << " after loading in the file" << endl;
			}
			else if (choice == "allinCity") {
				CityHashMap myCityHashMap(5000); //create new hashmap of class CityHashMap 
				// myCityHashMap = CityHashMap(5000);
				string cityName; //user input city 
				string keyCity1; 
				string keyCity; //make key of new hashmap the names of ciies 
				string cityMapValue; //make value of new hashmap the names of customers 
				for (int i=0; i<myHashMap.capacity; i++) { //read through old hashmap 
					if (myHashMap.nodeArray[i]!=NULL) {
						int count = 0;
						value = myHashMap.nodeArray[i]->getValue(); //get values of old hashmap
						cityMapValue = myHashMap.nodeArray[i]->getKey(); //set values of new hashmap 
						for (int i=0; i<value.length(); i++) {  //read through all the values of old hashmap 
							if (value[i] == ' ') {count ++;}
							if (count == 3) { //counter to count number of spaces 
								keyCity1 = value.substr(i+1); 
								keyCity = keyCity1.substr(0,keyCity1.find(' ')); //set key of new hashmap to city name 
								myCityHashMap.Insert(keyCity,cityMapValue); //insert key and value into new hashmap 
								break; 
							}
						}
					}
				}
				cout << "Enter the name of the city: " << endl; 
				cin >> cityName; 
				myCityHashMap.allinCity(cityName); 
			}
		}
	}
	exit(0);
}






