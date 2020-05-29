/****************************************************************************************
*  Dictionary.c
*  File for Dictionary ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA5
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Dictionary.h"

//strcmp(a,b) = ASCII(a) + ASCII(b)
    //if a<b => a - b = (-)
    //if a>b => a - b = (+)
    //if a=b => a - b = 0


typedef struct NodeObj{
    KEY_TYPE keyData;
    VAL_TYPE valData;
    struct NodeObj* parent;
    struct NodeObj* left;
    struct NodeObj* right;
}NodeObj;

typedef struct NodeObj* Node;

typedef struct DictionaryObj{
    Node root;
    Node nil;
    Node cursor;
    long length;
    int unique;
}DictionaryObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode (KEY_TYPE inKey, VAL_TYPE inVal){
    Node temp = malloc(sizeof(NodeObj));
    temp->keyData = inKey;
    temp->valData = inVal;
    temp->parent = NULL;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
void freeNode (Node* to_del){
    if (to_del != NULL && *to_del != NULL){
        free(*to_del);
        *to_del = NULL;
    }
}

// newDictionary()
    // Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
    // will accept duplicate keys, i.e. distinct pairs with identical keys. If 
    // unique==true (1 or any non-zero value), then duplicate keys will not be 
    // accepted. In this case, the operation insert(D, k) will enforce the 
    // precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
    Dictionary temp = malloc(sizeof(DictionaryObj));
    temp->nil = newNode(KEY_UNDEF, VAL_UNDEF);
    temp->root = temp->nil;
    temp->cursor = temp->nil;
    temp->length = 0;
    temp->unique = unique;
    return temp;
}

// freeDictionary()
    // Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
    if (pD != NULL && *pD != NULL){
        makeEmpty(*pD);
        freeNode(&((*pD)->nil));
        free(*pD);
        *pD = NULL;
    }
}


// Access functions -----------------------------------------------------------

// size()
    // Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling size() on NULL\n");
        exit(1);
    }
    return D->length;
}

// getUnique()
    // Returns true (1) if D requires that all pairs have unique keys. Returns
    // false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling getUnique() on NULL\n");
        exit(1);
    }
    return D->unique;
}

// lookup()
    // If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
    // KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
    // returns VAL_UNDEF.
Node search(Dictionary D, Node x, KEY_TYPE k){
    if (D == NULL){
        printf("Dictionary Error: calling search() on NULL dictionary\n");
        exit(1);
    }
    if (x == NULL){
        printf("Dictionary Error: calling search() on NULL node\n");
        exit(1);
    }

    if (x == D->nil || KEY_CMP(k, x->keyData) == 0){
        return x;
    }
    else if (KEY_CMP(k, x->keyData) < 0){
        return search(D, x->left, k);
    }
    else {
        return search(D, x->right, k);
    }
}
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
    if (D == NULL){
        printf("Dictionary Error: calling lookup() on NULL\n");
        exit(1);
    }
    if (size(D) == 0){
        return VAL_UNDEF;
    }
    Node iter = D->root;
    Node result = search(D, iter, k);
    return result->valData;
}

//helper fcns?
Node minimum(Dictionary D, Node x){
    if (D == NULL){
        printf("Dictionary Error: calling minimum() on NULL dictionary\n");
        exit(1);
    }
    if (x == NULL){
        printf("Dictionary Error: calling minimum() on NULL node\n");
        exit(1);
    }
    while (x->left != D->nil){
        x = x->left;
    }
    return x;
}
Node maximum(Dictionary D, Node x){
    if (D == NULL){
        printf("Dictionary Error: calling maximum() on NULL dictionary\n");
        exit(1);
    }
    if (x == NULL){
        printf("Dictionary Error: calling maximum() on NULL node\n");
        exit(1);
    }
    while (x->right != D->nil){
        x = x->right;
    }
    return x;
}
Node successor(Dictionary D, Node x){
    if (D == NULL){
        printf("Dictionary Error: calling successor() on NULL dictionary\n");
        exit(1);
    }
    if (x == NULL){
        printf("Dictionary Error: calling successor() on NULL node\n");
        exit(1);
    }
    if (x->right != D->nil){
        return minimum(D, x->right);
    }
    Node y = x->parent;
    while (y != D->nil && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}
Node predecessor(Dictionary D, Node x){
    if (D == NULL){
        printf("Dictionary Error: calling predecessor() on NULL dictionary\n");
        exit(1);
    }
    if (x == NULL){
        printf("Dictionary Error: calling predecessor() on NULL node\n");
        exit(1);
    }
    if (x->left != D->nil){
        return maximum(D, x->left);
    }
    Node y = x->parent;
    while (y != D->nil && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}


// Manipulation procedures ----------------------------------------------------

// insert()
    // Insert the pair (k,v) into Dictionary D. 
    // If getUnique(D) is false (0), then there are no preconditions.
    // If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
    // is enforced. 
//EXCLUSIVE use by insert*****
void treeInsert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    Node y = D->nil;
    Node x = D->root;
    Node z = newNode(k, v);
    z->parent = D->nil;
    z->left = D->nil;
    z->right = D->nil;
    while (x != D->nil){
        y = x;
        if (KEY_CMP(k, x->keyData) < 0){
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == D->nil){
        //D is empty
        D->root = z;
        z->parent = D->nil;
    }
    else if (KEY_CMP(k, y->keyData) < 0){
        y->left = z;
    }
    else {
        y->right = z;
    }
}
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
    if (D == NULL){
        printf("Dictionary Error: calling insert() on NULL\n");
        exit(1);
    }
    switch (getUnique(D)){
    case 1:
        if (lookup(D, k) != VAL_UNDEF){
            return;
        }
        treeInsert(D, k, v);
        D->length++;
        break;
    case 0:
        treeInsert(D, k, v);
        D->length++;
        break;
    
    default:
        break;
    }
}

// delete()
    // Remove the pair whose key is k from Dictionary D.
    // Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
//helper for delete()
void transplant(Dictionary D, Node u, Node v){
    if (u->parent == D->nil){
        D->root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != D->nil){
        v->parent = u->parent;
    }
}
void delete(Dictionary D, KEY_TYPE k){
    if (D == NULL){
        printf("Dictionary Error: calling delete() on NULL\n");
        exit(1);
    }
    if (lookup(D, k) == VAL_UNDEF){
        return;
    }
    Node target = search(D, D->root, k);
    if (target->left == D->nil){
        transplant(D, target, target->right);
    }
    else if (target->right == D->nil){
        transplant(D, target, target->left);
    }
    else {
        Node y = minimum(D, target->right);
        if (y->parent != target){
            transplant(D, y, y->right);
            y->right = target->right;
            y->right->parent = y;
        }
        transplant(D, target, y);
        y->left = target->left;
        y->left->parent = y;
    }
    D->length--;
    if (D->cursor == target) D->cursor = D->nil;
    freeNode(&target);
}

// makeEmpty()
    // Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling makeEmpty on NULL\n");
        exit(1);
    }
    //must iterate through entire tree and call freeNode()*************
    while (size(D) > 0){
        VAL_TYPE x = beginReverse(D);
        delete(D, currentKey(D));
    }
    D->root = D->nil;
    D->length = 0;
}

// beginForward()
    // If D is non-empty, starts a forward iteration over D at the first key 
    // (as defined by the order operator KEY_CMP()), then returns the first
    // value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling beginForward() on NULL\n");
        exit(1);
    }
    if (size(D) == 0){
        return VAL_UNDEF;
    }
    D->cursor = minimum(D, D->root);
    return D->cursor->valData;
}

// beginReverse()
    // If D is non-empty, starts a reverse iteration over D at the last key 
    // (as defined by the order operator KEY_CMP()), then returns the last
    // value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling beginReverse() on NULL\n");
        exit(1);
    }
    if (size(D) == 0){
        return VAL_UNDEF;
    }
    D->cursor = maximum(D, D->root);
    return D->cursor->valData;
}

// currentKey()
    // If an iteration (forward or reverse) over D has started, returns the 
    // the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling currentKey() on NULL\n");
        exit(1);
    }
    if (D->cursor == NULL || D->cursor == D->nil){
        return KEY_UNDEF;
    }
    return D->cursor->keyData;
}

// currentVal()
    // If an iteration (forward or reverse) over D has started, returns the 
    // value corresponding to the current key. If no iteration is underway, 
    // returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling currentVal on NULL\n");
        exit(1);
    }
    if (D->cursor == NULL || D->cursor == D->nil){
        return VAL_UNDEF;
    }
    return D->cursor->valData;
}

// next()
    // If an iteration (forward or reverse) over D has started, and has not
    // reached the last pair, moves to the next key in D (as defined by the 
    // order operator KEY_CMP()), and returns the value corresponding to the 
    // new key. If an iteration has started, and has reached the last pair,
    // ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
    // returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling next() on NULL\n");
        exit(1);
    }
    if (D->cursor == NULL || D->cursor == D->nil){
        return VAL_UNDEF;
    }
    D->cursor = successor(D, D->cursor);
    return D->cursor->valData;
}


// prev()
    // If an iteration (forward or reverse) over D has started, and has not
    // reached the first pair, moves to the previous key in D (as defined by the 
    // order operator KEY_CMP()), and returns the value corresponding to the 
    // new key. If an iteration has started, and has reached the first pair,
    // ends the iteration and returns VAL_UNDEF. If no iteration is underway, 
    // returns VAL_UNDEF. 
VAL_TYPE prev(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling prev() on NULL\n");
        exit(1);
    }
    if (D->cursor == NULL || D->cursor == D->nil){
        return VAL_UNDEF;
    }
    D->cursor = predecessor(D, D->cursor);
    return D->cursor->valData;
}


// Other operations -----------------------------------------------------------

// printDictionary()
    // Prints a text representation of D to the file pointed to by out. Each key-
    // value pair is printed on a single line, with the two items separated by a
    // single space.  The pairs are printed in the order defined by the operator
    // KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling printDictionary() on NULL\n");
        exit(1);
    }
    for (VAL_TYPE x = beginForward(D); currentVal(D) != VAL_UNDEF; x = next(D)){
        fprintf(out, ""KEY_FORMAT"\n", currentKey(D));
    }
}
