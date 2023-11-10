/***************************************************************
Author:         Justin Allen
Creation Date:  November 2, 2023
Due Date:       November 9, 2023
Course:         CSC136 010
Professor Name: Dr. Carelli
Assignment:     Project #3
Filename:       atest.cpp

Purpose:
The purpose of this program is to create a versatile dynamic 
array structure in C++, capable of accommodating diverse data types 
and resizing dynamically.  It will address a situation wherein the 
array has been allocated with a specific capacity, 
but only a subset of the elements is being used. 
***************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "Array.h"

using namespace std;

template <typename dataType>
void printArray(const Array<dataType> &MyArray);

int main()
{
  /////////////////////////////////////////////////
  // int data type
  // constructor tests
  Array<int> iList1;
  cout << "1) Default Constructor:" << endl;
  // output empty object
  printArray(iList1);

  cout << "2) Array from dataType array:" << endl;
  int iarray[]= { 10, 20, 30, 40, 50 };
  Array<int> iList2(iarray, 5);
  printArray(iList2);

  cout << "3) Array from dataType array (under capacity):" << endl;
  Array<int> iList3(iarray, 3);
  printArray(iList3);

  cout << "4) Copy Constructor:" << endl;
  Array<int> iList4(iList3);
  printArray(iList4);

  // assignment test
  cout << "5) Assignment:" << endl;
  Array<int>iList5= iList3;
  printArray(iList3);

  /////////////////////////////////////////////////
  // float data type
  float farray[]= { 10.1, 20.2, 30.3, 40.4 };
  cout << "6) New float Array:" << endl;
  Array<float> fList1(farray, 4);
  printArray(fList1);

  cout << "7) Change the last value using the subscript operator:" << endl;
  fList1[3]= 45.5;
  printArray(fList1);

  // change a value beyond capacity
  cout << "8) Change a value beyond existing capacity:" << endl;
  fList1[5]= 65.6;
  printArray(fList1);

  // attempt to access a value beyond the capacity on const array
  cout << "9) Attempt to access a value beyond the capacity:" << endl;
  const Array<float> fList2(farray, 3);
  cout << fList2[3] << endl;;
  printArray(fList2);

  /////////////////////////////////////////////////
  //
  // FINAL TESTS !!!!!!!!!!!!!!!!
  //
  /////////////////////////////////////////////////
  cout << "10) Add an item to iList3 with += (under capacity):" << endl;
  // uncomment the next line when the += operator is complete
  iList3+= 35;
  printArray(iList3);

  cout << "11) Add an item to iList3 with += (at capacity):" << endl;
  // uncomment the next line when the += operator is complete
  iList3+= 45;
  printArray(iList3);

  // Add your own dereference test here !!!
  cout << "12: dereference fList1:" << endl;
  cout << *fList1 << endl;
  return(0);
}

template <typename dataType>
void printArray(const Array<dataType> &MyArray) {
  cout << "   Capacity: " << MyArray.getCapacity()
       << ",  Elements in Use: " << MyArray.getNumUsed() << endl;
  cout << "   Contents: " << MyArray << endl;
  cout << endl;
}
