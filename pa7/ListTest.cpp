/****************************************************************************************
*  ListTest.cpp
*  Test Client for List ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA7
*****************************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

bool testCTORS();
bool testInsert();
bool testIterate();
bool testDelete();

int main(){
    cout<<"Testing CTORS: "<<testCTORS()<<endl;
    cout<<"Testing Insertions: "<<testInsert()<<endl;
    cout<<"Testing Iterations: "<<testIterate()<<endl;
    cout<<"testing Deletions: "<<testDelete()<<endl;
   return(0);
}


bool testCTORS(){
    //testing CTOR, copyCTOR, isEmpty, size, position
    List A;
    if (A.position()) return false;
    if (A.size()) return false;
    if (!A.isEmpty()) return false;
    List B(A);
    if (&A == &B) return false;
    if (!B.isEmpty()) return false;
    return true;
}
bool testInsert(){
    //testing insertions and equals
    List A, B;
    if (!A.equals(B)) return false;
    for (int i = 0; i < 10; i++){
        A.insertAfter(i);
        B.insertBefore(11 - i);
    }
    if (A.position()) return false;
    if (B.position() != 10) return false;
    if (A.equals(B)) return false;
    return true;
}
bool testIterate(){
    //testing iteration operations
    List A;
    for (int i = 0; i < 10; i++){
        A.insertBefore(i);
    }
    for (A.moveFront(); A.position() < A.size(); A.moveNext()){
    }
    while (A.position() > 0){
        A.movePrev();
    }
    return true;
}
bool testDelete(){
    //testing erase operations
    List A, B;
    for (int i = 0; i < 10; i++){
        A.insertAfter(10 - i);
    }
    for (int i = 10; i > 5; i--){
        B.insertAfter(i);
        A.eraseAfter();
    }
    if (!A.equals(B)) return false;
    return true;
}
