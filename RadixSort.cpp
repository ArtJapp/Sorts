#include <iostream>
#include <cmath>
#include <fstream>
#include "time.h"
using namespace std;

void byConsole();																// inputing data by console
void byFile();																	// inputing data by file
void byRandom();																// feeding the set by random nums
void anyWay(int size, int* array);												// preprocessing after getting the data

int sdvig = 0; //сортировка идет по положительным числам. если нужно сортировать отрицательные
               //числа, находим самое мин из них, записываем модуль числа и затем прибавляем это к
               //каждому элементу. сортируем и из каждого элемента вычитаем это число.

int digit(int number, int index, int k)                                                //возвращает и-тый разряд числа
{
    int dig = 0;
    for (int i = 0; i < index; i++)
    {
        dig = number % k;
        number /= k;
    }
    return dig;
}

int lengthy(int* massive, int length, int k)											//находит самое длинное число и возвращает количество разрядов
{
    int max = massive[0];
    for (int i = 1; i < length; i++)
    {
        if (max < massive[i])
        {
            max = massive[i];
        }
    }
    int len = 0;

    while (max > 0)
    {
        len++;
        max /= k;
    }
    return len;
}

void prepare(int*& massive, int length)
{
    int min = 0;
    for (int i = 0; i < length; i++)
    {
        if (massive[i] < min)
        {
            min = massive[i];
        }
    }
    sdvig = -min;
    if (sdvig)
    {
        for (int i = 0; i < length; i++)
        {
            massive[i] += sdvig;
        }
    }
}
void unprepare(int*& massive, int length)
{
    if (sdvig)
    {
        for (int i = 0; i < length; i++)
        {
            massive[i] -= sdvig;
        }
    }
}
void sorting(int*& array, int length);

bool tests(int* array, int size);

void swap(int& number1, int& number2)
{
    int t = number1;
    number1 = number2;
    number2 = t;
}
void printMass(int* mass, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << mass[i] << " ";
    }
}

int main()
{
    cout << "Heapsort";

    while (true)
    {
        cout << "\nWhich way of inputing data do you prefer?"
             << "\n\tf - from file"
             << "\n\tc - from console"
             << "\n\tr - by randomizer"
             << "\n\te - no thank's, I've been looking and now I get away"
             << "\n>  ";
        char decision;
        cin >> decision;

        if (decision == 'c' || decision == 'C' || decision == '2')
        {
            byConsole();
            cout << endl << "-------------------------------" << endl;
        }
        else if (decision == 'r' || decision == 'R' || decision == '3')
        {
            byRandom();
            cout << endl << "-------------------------------" << endl;
        }
        else if (decision == 'f' || decision == 'F' || decision == '1')
        {
            byFile();
            cout << endl << "-------------------------------" << endl;
        }
        else if (decision == 'e' || decision == 'E' || decision == '4' || decision == '0')
        {
            cout << "Have a nice day :3\n";
            return 0;
        }
        else
        {
            cout << "\nSorry, we didn't get. Try again";
            continue;
        }
    }

    return 0;																	// such a lonely return...
}

// An effort of making UI (huh)
void byRandom()
{
    srand(time(0));

    cout << "\nSo, you prefer to input data by RANDOMIZER"
         << "\nInput size of array: "
         << "\n>  ";
    int size;
    cin >> size;																// let we consider the user is adequate guy(huh no)
    if (size < 1)
    {
        cout << "Stop kidding!!!";
        return;
    }

    int* array = new int[size];
    for (int i = 0; i < size; ++i)
    {
        array[i] = rand() % 1000 - 498; 										// mm just because I want it
    }
    anyWay(size, array);
    delete[] array;
}

void byConsole()
{
    cout << "\nSo, you prefer to input data from CONSOLE"
         << "\nInput size of array: "
         << "\n>  ";
    int size;
    cin >> size;																// let us consider the user is adequate guy(huh no)
    if (size < 1)
    {
        cout << "Stop kidding!!!";
        return;
    }

    int* array = new int[size];
    cout << "\nNow input the elements: "
         << "\n>  ";
    for (int i = 0; i < size; ++i)
    {
        cin >> array[i];
    }
    anyWay(size, array);
    delete[] array;
}

void byFile()
{
    cout << "\nSo, you prefer to input data from the FILE"
         << "\nWe hope you inputed your data to 'input.txt'"
         << "\nChoose the right way:"
         << "\n\t1. The size of array is IN file"
         << "\n\t2. You prefer to input the size by console"
         << "\n>  ";
    char c;
    cin >> c;
    int size = 0;
    ifstream fin("input.txt");

    if (c == '1')
    {
        fin >> size;
    }
    else if (c == '2')
    {
        cout << "Input the size of array: "
             << "\n>  ";
        cin >> size;
    }
    if (size <= 0)
    {
        cout << "Stop kidding!\n";
        return;
    }
    int* array = new int[size];
    for (int i = 0; i < size; i++)
    {
        fin >> array[i];
    }
    anyWay(size, array);
    delete[] array;
}

void anyWay(int size, int* array)
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

    sorting(array, size);

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
    if (tested)
    {
        cout << "TESTS said that array is sorted\n";
    }
    else
    {
        cout << "TESTS said that array is NOT(whoat?!?) sorted. Shame on me((\n";
    }
}

bool tests(int* array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
// Algorythm of sorting


void sorting(int*& mass, int n)
{
    int m, base;
    base = 2;

    int* karmashkis = new int[base];
    int* temp = new int[n];
    m = lengthy(mass, n, base);

    prepare(*&mass, n);
    for (int i = 1; i <= m; i++)
    {

        for (int j = 0; j < base; j++)
        {
            karmashkis[j] = 0;
        }

        for (int j = 0; j < n; j++)
        {
            int d = digit(mass[j], i, base);
            karmashkis[d]++;
        }
        int count = 0;

        for (int j = 0; j < base; j++)
        {
            int tmp = karmashkis[j];
            karmashkis[j] = count;
            count += tmp;
        }
        for (int j = 0; j < n; j++)
        {
            int d = digit(mass[j], i, base);
            temp[karmashkis[d]] = mass[j];
            karmashkis[d]++;
        }

        for (int j = 0; j < count; j++)
        {
            mass[j] = temp[j];
        }
    }
    unprepare(*&mass, n);
}