/*
Name: Srinivas Vardhan Dintakurthi
Class Name: CS-1337 Computer Programming-1
Date:10/09/2022
Description: This program will read a file containing city 
information. After reading the file the program will display a menu. Using the menu, the user can select to
display the cities with ID within a range or by group, choose two cities and compute the linear (Euclidean) distance between
the two chosen cities, and an option to exit the program.  
*/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
#include<string>
using namespace std;

//Declaring global variables to store city id's
int a, b;
int* ptr = &a, * btr = &b;

//Structure to store different information related to city
struct city {

	int id;

	char group;

	double x_cor, y_cor;

	string cityName;

};

//Function prototypes for each task being performed
void menu(city [],int);
void range(city[],int);
int city1(city [],int), city2(int*,city [],int);
void group(city[],int);
void compdis(int*, int*,city[],int);

int main() {

	
	//Opening File and reading data
	ifstream input;
	input.open("cityInfo.txt");

	if (!input) {
		cout << "Error opening file";
	}

	//Array of structure 
	city record[1000];
	int i;
	for (i = 0; !input.eof(); i++) {
		input >> record[i].id >> record[i].group >> record[i].x_cor
			>> record[i].y_cor;
		getline(input, record[i].cityName);

	}
	
	//Initializing id's of both the cities to 0 and check if updated or not by comparision
	int id1 = 0, id2 = 0;

	//Calling menu function which displays all the options
	menu(record,i);

	input.close();

	return 0;
}

 void menu(city p[],int j) {
	
	char ch;

	cout <<"\na.Display cities by ID range\n"
		<< "b.Display cities by group\n"
		<< "c.Enter City 1\n"
		<< "d.Enter City 2\n"
		<< "e.Compute Distance\n"
		<< "f.Exit\n";
	cin >> ch;

	switch (ch) {

	case 'a': {
		range(p,j);
		menu(p,j);
	}
			break;

	case 'b': {
		group(p,j);
		menu(p,j);

	}
			break;

	case'c': {
		a=city1(p,j);
		menu(p,j);
	}
		   break;

	case'd': {
		b=city2(ptr,p,j);
		menu(p,j);
	}
		   break;

	case'e': {
		compdis(ptr,btr,p,1000);
		menu(p,j);
	}
		   break;

	case'f':exit;
		break;
		
	default: {cout << "option is invalid";
	}

	}
	
}

 //The range fuction takes city id's from user and outputs cities in that range

 void range(city p[], int j) {

	 int min_id, max_id, flag_min = 1,flag_max=1;

	 do {
		 do {
			 cout << "Enter min id\n";
			 cin >> min_id;

			 for (int i = 0; i < j; i++) {
				 if (min_id == p[i].id) {
					 flag_min = 0;
				 }
			 }

			 if (flag_min != 0) {

				 cout << "Invalid min_id\n";
			 }

		}while (flag_min!=0);

		do {
			cout << "Enter max id\n";
			cin >> max_id;

			for (int i = 0; i < j; i++) {
				if (max_id == p[i].id) {
					flag_max = 0;
				}
				
			}

			if (flag_max != 0) {
				cout << "Invalid max_id\n";
			}

		} while (flag_max!=0);

		if (min_id > max_id) {
			cout << "\nMin id is greater than Max id\n";
		}

	 } while (!(min_id < max_id && min_id >= 0 && max_id >= 0));

	 



	 for (int i = 0; i < j; i++) {

		 if (p[i].id >= min_id && p[i].id <= max_id) {

			 cout << left << setw(6) << p[i].id << setw(8) << p[i].group
				 << setw(10) << fixed << setprecision(2) << p[i].x_cor
				 << p[i].y_cor << setw(30) << p[i].cityName << endl;
		 }
	 }
	 
 }

 // The group asks the user for a group character and display cities in that group
 void group(city p[], int j) {

	 char gr;

	 cout << "\nEnter a character\n";
	 cin >> gr;

	 while (!(gr >= 'A' && gr <= 'Z')) {
		 group(p, j);
	 };

	 for (int i=0;i<j; i++) {
		 if (p[i].group == gr)
			 cout << left << setw(6) << p[i].id << setw(8) << p[i].group
			 << setw(10) << fixed << setprecision(2) << p[i].x_cor
			 << p[i].y_cor << setw(30) << p[i].cityName << endl;
	 }
 }

 // Asks the user for id of 1st city
int city1(city p[],int j) {
	int num1, flag=1;

	cout << "\nEnter a city id\n";
	cin >> num1;

	for (int i = 0; i < j; i++) {

		if (num1==p[i].id) {
			flag = 0;
		}
		
	}

	if (flag != 0) {
		cout << "\nPlease enter city id that exists\n";
	}
	else {
		return num1;
	}
}


//Asks the user for second cities id and checks if it is same as city-1 and if city one was entered
int city2(int *i,city p[],int j) {
	
	int num2 = 0, flag=1;

	do {

		if (*i == 0) {
			cout << "\nPlease enter id for city-1 first\n";
			break;
		}

		do {
			cout << "\nEnter a different city id\n";
			cin >> num2;

			if (*i == num2)
				cout << "\nId's for city-1 and city-2 are same enter another id for city-2";

			for (int k = 0; k < j; k++) {

				if (num2 == p[k].id) {

					flag = 0;
				}
			}

			if (flag != 0) {
				cout << "\nPlease enter city id that exists\n";
				return 0; 
			}
			else {
				return num2;
			}
		} while (flag != 0);

	} while (*i == num2);

	

	
}

//This function takes in the id's of both the cities and calculates the distance between them
void compdis(int *c1, int* c2, city p[], int j) {

	while (*c1 == 0) {
		cout << "\nPlease make sure you enter ID of City-1\n";
		menu(p, j);
	}

	while (*c2 == 0) {
		cout << "\nPlease make sure you enter ID of City-2\n";
		menu(p, j);
	}
	
	int i, h;

	for ( i = 0; i < 1000; i++) {

		if (*c1 == p[i].id) {
			break;
		}
	}

	for ( h = 0; h < 1000; h++) {

		if (*c2 == p[h].id) {
			break;
		}
	}

	double d = sqrt((pow((p[h].x_cor - p[i].x_cor), 2.0) + pow((p[h].y_cor - p[i].y_cor), 2.0)));
	cout << "\nThe distance between selected city-1 and city-2 is ";
	cout << fixed << setprecision(2) << d << endl;

}



