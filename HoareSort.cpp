//  Laba 1. Hoare quicksort
//  Worst-case : O(n^2)
//  Best-case  : O(n*lg(n))

//  In fuctions byConsole(),  byFile(), byRandom() there are only ways of inputing data
//  In fuction anyWay() there is preparing the array(and the user) to start the sorting

#include <iostream>
#include<cmath>
#include<fstream>
#include"time.h"
using namespace std;

void byConsole();                                                               //inputing data by console
void byFile();                                                                  //inputing data by file
void byRandom();                                                                //feeding the set by random nums

void anyWay(int size, int * massive);                                           //the next step, when you inputed data

int maxSr(int * massive, int left, int right);                                  //finding the average element
void sorting(int * massive, int left, int right, int decision);

bool tests(int * massive, int size);

int main()
{
     cout << "Hoare's quicksort";
    
    while(true){
        cout << "\nWhich way of inputing data do you prefer?\n" 
             << "\tf - from file\n" 
             << "\tc - from console\n"
             << "\tr - by randomizer\n"
             << "\te - no thank's, I've been looking and now I get away\n"
             << ">  ";
        char decision;
        cin >> decision;
        
        if (decision == 'c' || decision == 'C' || decision == '2')
        {
            byConsole();
            cout << endl << "-------------------------------" << endl;
        } else 
        if (decision == 'r' || decision == 'R' || decision == '3')
        {
            byRandom();
            cout << endl << "-------------------------------" << endl;
        } else 
        if (decision == 'f' || decision == 'F' || decision == '1')
        {
            byFile();
            cout << endl << "-------------------------------" << endl;
        } else
        if (decision == 'e' || decision == 'E' || decision == '4' || decision == '0')
        {
            cout << "Have a nice day :3\n";
            return 0;
        } else
        {
            cout << "\nSorry, we didn't get. Try again";
            continue;
        }
        
    }
    
    return 0;  //such a lonely return... 
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



void anyWay(int size, int * massive){
    cout << "Which technique of taking the base would you like?\n" 
         << "\t1. By random index - stohastic\n" 
         << "\t2. By average sum of elements (for risky guys) - determinied\n";
         
    char dec;
    cin >> dec;
    
    cout << "\nWould you like to see the massive BEFORE it's sorted? Y/N\n";
    char wannaSee;
    cin >> wannaSee;
    
    if (wannaSee=='Y' || wannaSee=='y'||wannaSee=='1'){
        for (int i=0; i< size; i++){
            cout << massive[i] << ' ';
        }
    cout << endl;
    }
    
    double startc = clock();
    if (dec == '1'){
        sorting(massive, 0, size-1, 1);
    }
    else if (dec =='2'){
        sorting(massive, 0, size-1, 2);
    }
     double endc = clock();
     
    cout << "Would you like to see the sorted massive? Y/N\n";
    cin >> wannaSee;
    if (wannaSee=='Y' || wannaSee=='y'||wannaSee=='1'){
        cout << "Well, now you have this set: ";
        for (int i=0; i<size; i++){
            cout << massive[i] << "  ";
        }
    }
    cout << "\nThe sorting has taken " << (endc-startc)/CLOCKS_PER_SEC << " second\n";
    bool tested = tests( massive,  size);
    if (tested){
        cout << "TESTS said that massive is sorted\n";
    } else {
        cout << "TESTS said that massive is NOT sorted((\n";           
    }
    
    
}

bool tests(int * massive, int size){
    for (int i=0; i<size-1; i++){
        if (massive[i] > massive[i+1]){
            return false;
        }
    }
    return true;
    
}

//------------------------------------------------------------------------------

//Algorythm of sorting
int maxSr(int * massive, int left, int right){
    int max = left;
    
    float sr=0;
    for (int i=left; i<right+1; i++){
        sr+=massive[i];
    }
    sr/= (right-left);
    for (int i=left+1; i<=right; i++){
        if (abs(sr-massive[max]) > abs(sr-massive[i])){
            max = i;
        }
    }
    return max;
}

void sorting(int * massive, int left, int right, int decision){
    int le, ri;
	le = left;
	ri = right;
	int opora;
	if (decision==1){
	    opora = massive[rand()%(right-left) +left];
	} else {
	    opora = massive[maxSr(massive, left, right)];
	}
	
	do
	{
		while (massive[le] < opora) 
		{
		    le++;
		}

		while (massive[ri] > opora) 
		{
		    ri--;
		}

		if (le <= ri)
		{
		    int temp = massive[le];
			massive[le] = massive[ri];
			massive[ri] = temp;

			le++;
			ri--;
		} 
		
	} while (le <= ri);
	
		if (le < right) sorting(massive, le, right, decision);
		if (ri > left)  sorting(massive, left, ri, decision);

}

