/****************************************************************************************
*  GraphTest.c
*  Testing file using Graph ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA4
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define PASS 1
#define FAIL 0

int testCTOR();
int testAddEdge();
int testAddArc();
int testDFS();
int testCopy();
int testTranspose();

int main(int argc, char* argv[]){
    printf("pass = 1, fail = 0\n");
    printf("JK the pass/fail only means it didn't crash. Check output to see if works as intented.\n\n");
    printf("Graph CTOR test: %d\n", testCTOR());
    printf("Graph addEdge test: %d\n", testAddEdge());
    printf("Graph addArc test: %d\n", testAddArc());
    printf("Graph DFS test: %d\n", testDFS());
    printf("Graph copyGraph test: %d\n", testCopy());
    printf("Graph transpose test: %d\n", testTranspose());
    return 0;
}

int testCTOR(){
    //testing CTOR, printGraph()
    Graph test1 = NULL;
    test1 = newGraph(5);
    if (test1 == NULL){
        return FAIL;
    }
    freeGraph(&test1);
    return PASS;
}
int testAddEdge(){
    //testing addEdge(), printGraph()
    Graph test1 = newGraph(4);
    addEdge(test1, 1, 2);
    addEdge(test1, 1, 3);
    addEdge(test1, 2, 1);
    addEdge(test1, 2, 4);
    addEdge(test1, 3, 1);
    addEdge(test1, 3, 4);
    addEdge(test1, 4, 2);
    addEdge(test1, 4, 3);
    printGraph(stdout, test1);
    printf("Should look like the following:\n");
    printf("1: 2 3\n2: 1 4\n3: 1 4\n4: 2 3\n");
    freeGraph(&test1);
    return PASS;
}
int testAddArc(){
    //testing addArc()
    Graph test1 = newGraph(4);
    addArc(test1, 1, 2);
    addArc(test1, 2, 3);
    addArc(test1, 3, 4);
    addArc(test1, 4, 1);
    printGraph(stdout, test1);
    printf("Should look like the following:\n");
    printf("1: 2\n2: 3\n3: 4\n4: 1\n");
    freeGraph(&test1);
    return PASS;
}
int testDFS(){
    //test DFS(), getPath()
    Graph test1 = newGraph(4);
    addEdge(test1, 1, 2);
    addEdge(test1, 1, 3);
    addEdge(test1, 2, 1);
    addEdge(test1, 2, 4);
    addEdge(test1, 3, 1);
    addEdge(test1, 3, 4);
    addEdge(test1, 4, 2);
    addEdge(test1, 4, 3);
    List helper = newList();
    DFS(test1, helper);
    freeGraph(&test1);
    return PASS;
}
int testCopy(){
    Graph test1 = newGraph(4);
    addArc(test1, 1, 2);
    addArc(test1, 2, 3);
    addArc(test1, 3, 4);
    addArc(test1, 4, 1);
    Graph testC = copyGraph(test1);
    printGraph(stdout, testC);
    printf("Should look like the following:\n");
    printf("1: 2\n2: 3\n3: 4\n4: 1\n");
    freeGraph(&test1);
    freeGraph(&testC);
    return PASS;
}
int testTranspose(){
    Graph test1 = newGraph(4);
    addArc(test1, 1, 2);
    addArc(test1, 2, 3);
    addArc(test1, 3, 4);
    addArc(test1, 4, 1);
    Graph testT = transpose(test1);
    printGraph(stdout, testT);
    printf("Should look like the following:\n");
    printf("1: 4\n2: 1\n3: 2\n4: 3\n");
    freeGraph(&test1);
    freeGraph(&testT);
    return PASS;
}