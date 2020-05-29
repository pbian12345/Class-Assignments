/****************************************************************************************
*  Graph.c
*  File for Graph ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA4
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
    List *graph;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int order;                                      //# of vertices
    int size;                                       //# of edges
}GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
    //arrays of size n+1, but only use 1->n (avoid confusion)
    Graph temp = malloc(sizeof(GraphObj));
    temp->graph = malloc((n + 1) * sizeof(List));
    temp->color = calloc(n + 1, sizeof(int));
    temp->parent = calloc(n + 1, sizeof(int));
    temp->discover = calloc(n + 1, sizeof(int));
    temp->finish = calloc(n + 1, sizeof(int));
    temp->order = n;
    // printf("Order of A(inside): %d\n", temp->order);
    temp->size = NIL;
    for (int i = 0; i < n + 1; i++){
        temp->graph[i] = newList();
        temp->discover[i] = NIL;
        temp->finish[i] = NIL;
    }
    return temp;
}
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL){
        for (int i = 0; i <= (*pG)->order; ++i){
            freeList(&(*pG)->graph[i]);
        }
        free(((*pG)->graph));
        free(((*pG)->color));
        free(((*pG)->parent));
        free(((*pG)->discover));
        free(((*pG)->finish));
        free(*pG);
        *pG = NULL;
    }
}
/*** Access functions ***/
int getOrder(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getOrder() on null\n");
        exit(1);
    }
    return G->order;
}
int getSize(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getSize() on null\n");
        exit(1);
    }
    return G->size;
}
int getParent(Graph G, int u){
    //precondition 1 <= u <= getOrder(G)
    if (G == NULL){
        printf("Graph Error: calling getParent() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getParent() on invalid u value\n");
        exit(1);
    }
    return G->parent[u];
}
int getDiscover(Graph G, int u){
    /* Pre: 1<=u<=n=getOrder(G) */
    if (G == NULL){
        printf("Graph Error: calling getDiscover() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getDiscover() on invalid u value\n");
        exit(1);
    }
    return G->discover[u];
}
int getFinish(Graph G, int u){
    /* Pre: 1<=u<=n=getOrder(G) */
    if (G == NULL){
        printf("Graph Error: calling getFinish() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getFinish() on invalid u value\n");
        exit(1);
    }
    return G->finish[u];
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
    if (G == NULL){
        printf("Graph Error: calling makeNull() on null\n");
        exit(1);
    }
    for (int i = 0; i <= G->order; ++i){
        clear(G->graph[i]);
        G->color[i] = NIL;
        G->parent[i] = NIL;
        G->discover[i] = NIL;
        G->finish[i] = NIL;
    }
    G->size = NIL;
}
void addEdge(Graph G, int u, int v){
    //inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
        //and v to the adjacency List of u
    //maintain these lists in sorted order by increasing labels***************************
    //precondition: 1 <= u,v <= getOrder(G)
    if (G == NULL){
        printf("Graph Error: calling addEdge() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling addEdge() on invalid u value\n");
        exit(1);
    }
    if (v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addEdge() on invalid v value\n");
        exit(1);
    }

    int newEdge = 0;
    List tempU = G->graph[u];
    if (length(tempU) == 0){
        append(tempU, v);
        if (!newEdge){
            G->size++;
            newEdge = 1;
        }
    }
    else {
        int hasInserted = 0;
        for (moveFront(tempU); index(tempU) >= 0; moveNext(tempU)){
            if (v == get(tempU)){
                moveBack(tempU);
                hasInserted++;
            }
            else if (v < get(tempU)){
                insertBefore(tempU, v);
                moveBack(tempU);
                hasInserted++;
                if (!newEdge){
                    G->size++;
                    newEdge = 1;
                }
            }
        }
        if (!hasInserted){
            append(tempU, v);
            if (!newEdge){
                G->size++;
                newEdge = 1;
            }
        }
    }

    List tempV = G->graph[v];
    if (length(tempV) == 0){
        append(tempV, u);
        if (!newEdge){
            G->size++;
            newEdge = 1;
        }
    }
    else {
        int hasInserted = 0;
        for (moveFront(tempV); index(tempV) >= 0; moveNext(tempV)){
            if (u == get(tempV)){
                moveBack(tempV);
                hasInserted++;
            }
            else if (u < get(tempV)){
                insertBefore(tempV, u);
                moveBack(tempV);
                hasInserted++;
                if (!newEdge){
                    G->size++;
                    newEdge = 1;
                }
            }
        }
        if (!hasInserted){
            append(tempV, u);
            if (!newEdge){
                G->size++;
                newEdge = 1;
            }
        }
    }
}
void addArc(Graph G, int u, int v){
    //inserts a new directed edge from u to v, i.e. v is added to the adjacency List
        //of u (but not u to the adjacency List of v)
    //maintain these lists in sorted order by increasing labels***************************
    //precondition: 1 <= u,v <= getOrder(G)
    if (G == NULL){
        printf("Graph Error: calling addArc() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling addArc() on invalid u value\n");
        exit(1);
    }
    if (v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addArc() on invalid v value\n");
        exit(1);
    }

    List tempU = G->graph[u];
    if (length(tempU) == 0){
        append(tempU, v);
        G->size++;
    }
    else {
        int hasInserted = 0;
        for (moveFront(tempU); index(tempU) >= 0; moveNext(tempU)){
            if (v == get(tempU)){
                moveBack(tempU);
                hasInserted++;
            }
            else if (v < get(tempU)){
                insertBefore(tempU, v);
                G->size++;
                hasInserted++;
            }
        }
        if (!hasInserted){
            append(tempU, v);
            G->size++;
        }
    }
}

void Visit(Graph G, List S, int x, int* time){
    if (G == NULL){
        printf("Graph Error: calling Visit() on null\n");
        exit(1);
    }
    if (x > getOrder(G) || x < 0){
        printf("Graph Error: calling Visit() on invalid x value\n");
        exit(1);
    }
    G->discover[x] = ++(*time);
    G->color[x] = GRAY;
    if (length(G->graph[x]) > 0){
        for (moveFront(G->graph[x]); index(G->graph[x]) >= 0; moveNext(G->graph[x])){
            if (G->color[get(G->graph[x])] == WHITE){
                G->parent[get(G->graph[x])] = x;
                Visit(G, S, get(G->graph[x]), time);
            }
        }
    }
    G->color[x] = BLACK;
    G->finish[x] = ++(*time);
    append(S, x);
}
void DFS(Graph G, List S){
    /* Pre: length(S)==getOrder(G) */
    //treat S as a stack
        //top of stack is head
    if (G == NULL){
        printf("Graph Error: calling DFS() on null\n");
        exit(1);
    }
    if (length(S) != getOrder(G)){
        printf("Graph Error: calling DFS() on List of different order than Graph\n");
        exit(1);
    }
    if (length(S) == 0){
        return;
    }
    for (int i = 1; i <= getOrder(G); ++i){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    //loops through based on contents of stack, S
    for (int j = 1; j <= getOrder(G); ++j){
        moveFront(S);
        int u = get(S);
        deleteFront(S);

        if (G->color[u] == WHITE){
            Visit(G, S, u, &time);
        }
    }
    reverse(S);
}

/*
DFS(𝐺)
1. for all 𝑥 ∈ 𝑉(𝐺)
2.  color[𝑥] = white
3.  𝑝[𝑥] = nil
4. time = 0
5. for all 𝑥 ∈ 𝑉(𝐺)
6.  if color[𝑥] == white
7.      Visit(𝑥)
Visit(𝑥)
1. 𝑑[𝑥] = (+ + time) // discover 𝑥
2. color[𝑥] = gray
3. for all 𝑦 ∈ adj[𝑥]
4.  if color[𝑦] == white
5.      𝑝[𝑦] = 𝑥
6.      Visit(𝑦)
7. color[𝑥] = black
8. 𝑓[𝑥] = (+ + time) // finish �
*/

/*** Other operations ***/
Graph transpose(Graph G){
    if (G == NULL){
        printf("Graph Error: calling transpose() on null\n");
        exit(1);
    }
    Graph temp = newGraph(getOrder(G));
    if (getOrder(G) == 0){
        return temp;
    }
    for (int i = 1; i <= getOrder(G); ++i){
        if (length(G->graph[i]) == 0){
            continue;
        }
        for (moveFront(G->graph[i]); index(G->graph[i]) >= 0; moveNext(G->graph[i])){
            addArc(temp, get(G->graph[i]), i);
        }
    }
    return temp;
}
Graph copyGraph(Graph G){
    if (G == NULL){
        printf("Graph Error: calling copyGraph() on null\n");
        exit(1);
    }
    Graph temp = newGraph(getOrder(G));
    if (getOrder(G) == 0){
        return temp;
    }

    temp->order = getOrder(G);
    temp->size = getSize(G);
    for (int i = 0; i < getOrder(G) + 1; ++i){
        temp->graph[i] = copyList(G->graph[i]);
        temp->color[i] = G->color[i];
        temp->parent[i] = G->parent[i];
        temp->discover[i] = getDiscover(G, i);
        temp->finish[i] = getFinish(G, i);
    }
    return temp;
}
void printGraph(FILE* out, Graph G){
    if (G == NULL){
        printf("Graph Error: calling printGraph() on null\n");
        exit(1);
    }
    for (int i = 1; i <= G->order; ++i){
        fprintf(out, "%d: ", i);
        printList(out, G->graph[i]);
    }
}