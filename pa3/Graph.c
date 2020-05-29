/****************************************************************************************
*  Graph.c
*  File for Graph ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA3
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
    List *graph;
    int *color;
    int *parent;
    int *distance;
    int order;                                      //# of vertices
    int size;                                       //# of edges
    int source;
    List bfs;
}GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
    //arrays of size n+1, but only use 1->n (avoid confusion)
    Graph temp = malloc(sizeof(GraphObj));
    temp->graph = malloc((n + 1) * sizeof(List));
    temp->color = calloc(n + 1, sizeof(int));
    temp->parent = calloc(n + 1, sizeof(int));
    temp->distance = calloc(n + 1, sizeof(int));
    temp->order = n;
    // printf("Order of A(inside): %d\n", temp->order);
    temp->size = NIL;
    temp->source = NIL;
    temp->bfs = newList();
    for (int i = 0; i < n + 1; i++){
        temp->graph[i] = newList();
        temp->distance[i] = INF;
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
        free(((*pG)->distance));
        freeList(&((*pG)->bfs));
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
int getSource(Graph G){
    //returns the source vertex most recently used in function BFS(), or NIL if
        //BFS() has not yet been called.
    if (G == NULL){
        printf("Graph Error: calling getSource() on null\n");
        exit(1);
    }
    return G->source;
}
int getParent(Graph G, int u){
    //return the parent of vertex u in the BreadthFirst tree created by BFS(),
        //or NIL if BFS() has not yet been called.
    //precondition 1 <= u <= getOrder(G)
    if (G == NULL){
        printf("Graph Error: calling getParent() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getParent() on invalid u value\n");
        exit(1);
    }
    if (G->source == NIL){
        return NIL;
    }
    if (u == G->source){
        return NIL;
    }
    return G->parent[u];
}
int getDist(Graph G, int u){
    //returns the distance from the most recent BFS source to vertex u, or
        //INF if BFS() has not yet been called.
    //precondition 1 <= u <= getOrder(G)
    if (G == NULL){
        printf("Graph Error: calling getDist() on null\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getDist() on invalid u value\n");
        exit(1);
    }
    if (G->source == NIL){
        return INF;
    }
    return G->distance[u];
}
void getPath(List L, Graph G, int u){
    //appends to the List L the vertices of a shortest path in G from source to u,
        //or appends to L the value NIL if no such path exists.
    //precondition: getSource(G)!=NIL, so BFS() must be called before getPath()
    //precondition 1 <= u <= getOrder(G)
    if (G == NULL || L == NULL){
        printf("Graph Error: calling getPath() on null\n");
        exit(1);
    }
    if (getSource(G) == NIL){
        printf("Graph Error: BFS() must be called before getPath()\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getPath() on invalid u value\n");
        exit(1);
    }

    if (u == G->source){
        append(L, u);
    }
    else if (G->parent[u] == NIL){
        append(L, NIL);
    }
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
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
        G->distance[i] = NIL;
    }
    G->source = NIL;
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
void BFS(Graph G, int s){
    //runs the BFS algorithm on the Graph G with source s, setting the color, distance,
        //parent, and source fields of G accordingly.
    if (G == NULL){
        printf("Graph Error: calling BFS() on null\n");
        exit(1);
    }
    if (s < 1 || s > getOrder(G)){
        printf("Graph Error: calling BFS() on invalid s value\n");
        exit(1);
    }
    G->source = s;
    for (int i = 1; i <= getOrder(G); ++i){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    append(G->bfs, s);
    while (length(G->bfs) != 0){
        moveFront(G->bfs);
        int u = get(G->bfs);
        deleteFront(G->bfs);
        List temp = G->graph[u];
        if (length(G->graph[u]) > 0){
            for (moveFront(temp); index(temp) >= 0; moveNext(temp)){
                if (G->color[get(temp)] == WHITE){
                    G->color[get(temp)] = GRAY;
                    G->distance[get(temp)] = G->distance[u] + 1;
                    G->parent[get(temp)] = u;
                    append(G->bfs, get(temp));
                }
            }
        }
        G->color[u] = BLACK;
    }
}

/*
BFS(G,s){
    for each vertex u = G.V - {s}
        u.color = WHITE
        u.d = INF
        u.pi = NIL
    s.color = GRAY
    s.d = 0
    s.pi = NIL
    Q = zero
    ENQUEUE(Q,s)
    while Q != zero
        u = DEQUEUE(Q)
        for each v = G.Adj[u]
            if v.color == WHITE
                v.color = GRAY
                v.d = u.d + 1
                v.pi = u
                ENQUEUE(Q,v)
        u.color = BLACK
}
*/

/*** Other operations ***/
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