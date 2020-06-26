/****************************************************************************************
*  Shuffle.cpp
*  Client for List ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA7
*****************************************************************************************/
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include "List.h"
using namespace std;

#define MAX_LEN 300

void shuffle(List& D);

int main(int argc, char * argv[]){
   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <input deck size>" << endl;
      return 1;
   }
   cout<<"deck size       shuffle count"<<endl;
   cout<<"------------------------------"<<endl;
   //argv[1] = deck size
   //now must call shuffle over and over until we see that it matches original
   int size = stoi(argv[1]);
   List A;
   for (int i = 1; i <= size; i++){
       int shfCount = 0;
       A.moveFront();
       A.insertAfter(i);
       cout<<left<<setw(17)<<i;
       List ogA(A);
       shuffle(A);
       shfCount++;

       while (!ogA.equals(A)){
           shuffle(A);
           shfCount++;
       }
       cout<<shfCount<<endl;
   }

   return 0;
}

void shuffle(List& D){
    if (D.size() < 2) return;
    D.moveFront();
    while (D.position() < D.size()/2){
        D.moveNext();
    }
    List temp = temp.concat(D);
    while (D.position() < D.size()){
        D.eraseAfter();
    }

    D.moveFront();
    temp.moveFront();
    while (temp.position() < temp.size()){
        D.insertBefore(temp.moveNext());
        if (D.position() < D.size()) D.moveNext();
    }
    D.moveFront();
}
