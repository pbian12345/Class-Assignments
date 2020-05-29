/****************************************************************************************
*  FindPath.c
*  Client file using Graph ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA3
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


int main(int argc, char* argv[]){
    FILE *in, *out;
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

    int size = 0;
    fscanf(in, "%d", &size);
    Graph A = newGraph(size);
    // printf("Order of A: %d\n", getOrder(A));

    int vert1 = -1;
    int vert2 = -1;
    fscanf(in, "%d %d", &vert1, &vert2);
    while (vert1 != 0 && vert2 != 0){
        addEdge(A, vert1, vert2);
        fscanf(in, "%d %d", &vert1, &vert2);
    }
    printGraph(out, A);
    fprintf(out, "\n");

    vert1 = -1;
    vert2 = -1;
    fscanf(in, "%d %d", &vert1, &vert2);
    while (vert1 != 0 && vert2 != 0){
        //now need to do BFS and path getting stuff
        BFS(A, vert1);
        List Path = newList();
        getPath(Path, A, vert2);
        if (back(Path) == NIL){
            fprintf(out, "The distance from %d to %d is infinity\n", vert1, vert2);
            fprintf(out, "No %d-%d path exists\n", vert1, vert2);
        }
        else {
            fprintf(out, "The distance from %d to %d is %d\n", vert1, vert2, getDist(A, vert2));
            fprintf(out, "A shortest %d-%d path is: ", vert1, vert2);
            printList(out, Path);
        }
        fprintf(out, "\n");
        fscanf(in, "%d %d", &vert1, &vert2);
        freeList(&Path);
    }

    freeGraph(&A);

    /* close files */
    fclose(in);
    fclose(out);

    return 0;
}
