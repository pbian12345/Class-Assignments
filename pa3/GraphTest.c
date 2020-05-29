/****************************************************************************************
*  GraphTest.c
*  Testing file using Graph ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA3
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define PASS 1
#define FAIL 0

int testCTOR();
int testAddEdge();
int testAddArc();
int testBFS();

int main(int argc, char* argv[]){
    printf("pass = 1, fail = 0\n");
    printf("Graph CTOR test: %d\n", testCTOR());
    printf("Graph addEdge test: %d\n", testAddEdge());
    printf("Graph addArc test: %d\n", testAddArc());
    printf("Graph BFS test: %d\n", testBFS());
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
int testBFS(){
    //test BFS(), getPath()
    Graph test1 = newGraph(4);
    addEdge(test1, 1, 2);
    addEdge(test1, 1, 3);
    addEdge(test1, 2, 1);
    addEdge(test1, 2, 4);
    addEdge(test1, 3, 1);
    addEdge(test1, 3, 4);
    addEdge(test1, 4, 2);
    addEdge(test1, 4, 3);
    BFS(test1, 1);
    printf("The distance from %d to %d is %d\n", 1, 2, test1->distance[2]);
    List path = newList();
    getPath(path, test1, 4);
    printf("A shortest %d-%d path is: ", 1, 4);
    printList(stdout, path);
    freeGraph(&test1);
    freeList(&path);
    return PASS;
}