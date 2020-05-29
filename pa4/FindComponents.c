/****************************************************************************************
*  FindComponents.c
*  Client file using Graph ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA4
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


int main(int argc, char* argv[]){
    FILE *in, *out;
    int size = 0;
    int vert1 = -1;
    int vert2 = -1;
    int numSCC = 0;
    // check command line for correct number of arguments
    if( argc != 3 ){
       printf("Usage: %s <input file> <output file>\n", argv[0]);
       exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if( out==NULL ){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }

    fscanf(in, "%d", &size);
    Graph A = newGraph(size);

    fscanf(in, "%d %d", &vert1, &vert2);
    while (vert1 != 0 && vert2 != 0){
        addArc(A, vert1, vert2);
        fscanf(in, "%d %d", &vert1, &vert2);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, A);
    fprintf(out, "\n");

    Graph Atrans = transpose(A);
    List stack = newList();
    for (int i = 1; i <= getOrder(A); ++i){
        append(stack, i);
    }
    //after two calls, the resulting stack has SCCs in order
        //parent[i] == NIL is like a comma or next line
    
    DFS(A, stack);
    DFS(Atrans, stack);
    //get # of components
    for (moveFront(stack); index(stack) >= 0; moveNext(stack)){
        if (!getParent(Atrans, get(stack))){
            numSCC++;
        }
    }
    List* resArray = malloc((numSCC + 1) * sizeof(List));
    for (int i = 0; i < numSCC + 1; ++i){
        resArray[i] = newList();
    }
    
    //extract components into List array[]
    int i = 1;
    for (moveBack(stack); index(stack) >= 0; movePrev(stack)){
        prepend(resArray[i], get(stack));
        if (!getParent(Atrans, get(stack))){
            i++;
        }
    }


    fprintf(out, "G contains %d strongly connected components:\n", numSCC);
    for (int i = 1; i <= numSCC; ++i){
        fprintf(out, "Component %d: ", i);
        printList(out, resArray[i]);
        fprintf(out, "\n");
    }

    for (int i = 0; i < numSCC + 1; ++i){
        freeList(&resArray[i]);
    }
    freeList(&stack);
    freeGraph(&Atrans);
    freeGraph(&A);

    /* close files */
    fclose(in);
    fclose(out);

    return 0;

}