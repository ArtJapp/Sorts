//  Laba 2. Heapsort
//  Worst-case : O(n*lg(n))
//  Best-case  : O(n)

//  In fuctions byConsole(),  byFile(), byRandom() there are only ways of inputing data
//  In fuction anyWay() there is preparing the array(and the user) to start the sorting

#include <iostream> 
#include <cmath> 
#include <fstream> 
#include "time.h"
using namespace std;

void byConsole();                                                               //inputing data by console
void byFile();                                                                  //inputing data by file
void byRandom();                                                                //feeding the set by random nums
void anyWay(int size, int * array);                                             //

void sift(int * &array, int i, int max);
void build(int * &array, int length);
void sorting(int * &array, int length);

bool tests(int * array, int size);

void swap(int &number1, int &number2) {
	int t = number1;
	number1 = number2;
	number2 = t;
}
void printMass(int * mass, int size) {
    for (int i = 0; i < size; i++) {
        cout << mass[i] << " ";
    }
}

int main() {
	cout << "Heapsort";

	while (true) {
		cout << "\nWhich way of inputing data do you prefer?" 
		     << "\n\tf - from file" 
		     << "\n\tc - from console" 
		     << "\n\tr - by randomizer" 
		     << "\n\te - no thank's, I've been looking and now I get away" 
		     << "\n>  ";
		char decision;
		cin >> decision;

		if (decision == 'c' || decision == 'C' || decision == '2') {
			byConsole();
			cout << endl << "-------------------------------" << endl;
		} else if (decision == 'r' || decision == 'R' || decision == '3') {
			byRandom();
			cout << endl << "-------------------------------" << endl;
		} else if (decision == 'f' || decision == 'F' || decision == '1') {
			byFile();
			cout << endl << "-------------------------------" << endl;
		} else if (decision == 'e' || decision == 'E' || decision == '4' || decision == '0') {
			cout << "Have a nice day :3\n";
			return 0;
		} else {
			cout << "\nSorry, we didn't get. Try again";
			continue;
		}

	}

	return 0;                                                                   //such a lonely return... 
}

// An effort of making UI (huh)

void byRandom(){
     cout << "\nSo, you prefer to input data by RANDOMIZER\n" 
         << "Input size of massive: ";
    int size;
    cin >> size;                                                                //let us consider the user is adequate guy(huh no)
    
    if (size < 1) {                                                             
        cout << "Stop kidding!!!";
        return;
    }
    
    int * massive = new int[size];                                              
    cout << "\nNow input the elements: ";
    for (int i = 0; i < size; ++i){
        massive[i] = rand()%1000 - 498;                                         //mm just because I want it
    }
    anyWay(size, massive);
    delete[] massive;
}

void byConsole(){
    cout << "\nSo, you prefer to input data from CONSOLE" 
         << "\nInput size of massive: ";
    int size;
    cin >> size;                                                                //let us consider the user is adequate guy(huh no)
    
    if (size < 1) {
        cout << "Stop kidding!!!";
        return;
    }
    
    int * massive = new int[size];                                              
    cout << "\nNow input the elements: ";
    for (int i = 0; i < size; ++i){
        cin >> massive[i];
    }
    
    anyWay(size, massive);
    
    delete[] massive;
}

void byFile(){
    cout << "\nSo, you prefer to input data from the FILE"
    << "\nWe will read data from input.txt"
    << "\nChoose the right way:" 
    << " \n\t1. The size of massive is IN file" 
    << " \n\t2. You prefer to input the size by console\n";
    
    char c;
    cin >> c;
    
    int size = 0;
    ifstream fin("input.txt");
    
    if (c == '1')
    {
         fin >> size;
    } else if (c == '2')
    {
        cout << "Input the size of massive: ";
        cin >> size;
    }
    
    int * massive = new int[size];
    for (int i=0; i<size; i++)
    {
        fin >> massive[i];
    }
    
    anyWay(size, massive);
    
    delete[] massive;
}   

void anyWay(int size, int * array) 
{
	cout << "Would you like to see the array BEFORE it's sorted? Y/N"
	     << "\n>  ";
	char wannaSee;
	cin >> wannaSee;
	if (wannaSee == 'Y' || wannaSee == 'y' || wannaSee == '1') 
	{
		printMass(array, size);
		cout << endl;
	}
	double startc = clock();

	sorting(array, size - 1);

	double endc = clock();

	cout << "Would you like to see the sorted array? Y/N"
	     << "\n>  ";
	cin >> wannaSee;
	if (wannaSee == 'Y' || wannaSee == 'y' || wannaSee == '1') 
	{
		cout << "Well, now your array is : ";
		printMass(array, size);
		cout << endl;
	}
	cout << "The sorting has taken " << (endc - startc) / CLOCKS_PER_SEC << " second\n";

	bool tested = tests(array, size);
	if (tested) {
		cout << "TESTS said that array is sorted\n";
	} else {
		cout << "TESTS said that array is NOT(whoat?!?) sorted\n";
	}

}

bool tests(int * array, int size) {
	for (int i = 0; i < size - 1; i++) {
		if (array[i] > array[i + 1]) {
			return false;
		}
	}
	return true;

}

//------------------------------------------------------------------------------
//Algorythm of sorting

//Функция перестройки массива дерева по правилу 
//a[i] >= a[2*i + 1]
//a[i] >= a[2*i + 2]
void sift(int *& array, int i, int max)
{
        int bigindex =i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        if (left < max && array[left] > array[bigindex])
        {
            bigindex = left;
        }
        if (right < max && array[right] > array[bigindex])
        {
            bigindex = right;
        }
        if (bigindex != i)
        {
        	swap(array[i], array[bigindex]);
        	sift(*&array, bigindex, max);
        }
        
}

void build(int * &array, int length)
{
	int index = length/2 - 1;
    
    while( index >= 0 )
    {
    	sift(array, index, length);
    	index--;
    }
}


void sorting(int *& array, int length)
{
    build(*&array, length);
    
    int end = length;
    while(end > 0)
    {
        swap(array[0], array[end]);
        
        sift(*&array, 0, end);
        end--;
    }
}