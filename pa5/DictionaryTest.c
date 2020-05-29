/****************************************************************************************
*  DictionaryTest.c
*  Test Client for Dictionary ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA5
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"

int test_ctor();
int test_loop();
int test_insert();
int test_delete();

int main(int argc, char* argv[]){
    //return 1 if tests pass, 0 otherwise
    printf("CTORS: %d\n", test_ctor());
    printf("loop: %d\n", test_loop());
    printf("insert: %d\n", test_insert());
    printf("delete: %d\n", test_delete());
    return 0;
}

int test_ctor(){
    //test CTORS
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);

    if (getUnique(A) != 0) return 0;
    if (getUnique(B) != 1) return 0;
    freeDictionary(&A);
    freeDictionary(&B);
    return 1;
}
int test_loop(){
    //test loop operations
    Dictionary A = newDictionary(0);
    char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
    for(int i = 0; i < 26; i++){
        insert(A, word[i], i);
    }
    if (beginForward(A) != 9) return 0;
    if (currentKey(A) != "a") return 0;
    if (currentVal(A) != 9) return 0;
    if (next(A) != 12) return 0;
    if (beginReverse(A) != 1) return 0;
    if (currentKey(A) != "z") return 0;
    if (currentVal(A) != 1) return 0;
    if (prev(A) != 11) return 0;
    freeDictionary(&A);
    return 1;
}
int test_insert(){
    //test insert()
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
    for(int i = 0; i < 26; i++){
        insert(A, word[i], i);
        insert(B, word[i], i);
    }
    if (beginForward(A) != beginForward(B)) return 0;
    freeDictionary(&A);
    freeDictionary(&B);
    return 1;
}
int test_delete(){
    //test delete()
    Dictionary A = newDictionary(0);
    Dictionary B = newDictionary(1);
    char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
    for(int i = 0; i < 26; i++){
        insert(A, word[i], i);
        insert(B, word[i], i);
    }
    if (beginForward(A) != beginForward(B)) return 0;
    delete(A, "a");
    if (beginForward(A) == beginForward(B)) return 0;
    freeDictionary(&A);
    freeDictionary(&B);
    return 1;
}