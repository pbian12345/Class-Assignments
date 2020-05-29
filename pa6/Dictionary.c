/****************************************************************************************
*  Dictionary.c
*  File for Dictionary ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA6
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Dictionary.h"

//strcmp(a,b) = ASCII(a) + ASCII(b)
    //if a<b => a - b = (-)
    //if a>b => a - b = (+)
    //if a=b => a - b = 0
    
enum nodeColor {
  RED,
  BLACK
};

typedef struct NodeObj{
    KEY_TYPE keyData;
    VAL_TYPE valData;
    int color;
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
    temp->color = RED;
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
    temp->nil->color = -1;
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
void rotateLeft(Dictionary D, Node x){
    //set y
    Node y = x->right;

    //turn y's left subtree into x's right subtree
    x->right = y->left;
    if (y->left != D->nil){
        y->left->parent = x;
    }

    //link x's parent to y
    y->parent = x->parent;
    if (x->parent == D->nil){
        D->root = y;
    }
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    //put x on y's left
    y->left = x;
    x->parent = y;
}
void rotateRight(Dictionary D, Node x){
    //set y
    Node y = x->left;

    //turn y's right subtree into x's left subtree
    x->left = y->right;
    if (y->right != D->nil){
        y->right->parent = x;
    }

    //link x's parent to y
    y->parent = x->parent;
    if (x->parent == D->nil){
        D->root = y;
    }
    else if (x == x->parent->right){
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    //put x on y's right
    y->right = x;
    x->parent = y;
}
void insertFixUp(Dictionary D, Node x){
    if (x->parent == D->root || x == D->root){
        return;
    }
    while (x->parent->color == RED){
        if (x->parent == x->parent->parent->left){
            Node y = x->parent->parent->right;
            //case 1
            if (y->color == RED){
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //case 2
                if (x == x->parent->right){
                    x = x->parent;
                    rotateLeft(D, x);
                }
                //case 3
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(D, x->parent->parent);
            }
        }
        else {
            Node y = x->parent->parent->left;
            //case 4
            if (y->color == RED){
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //case 5
                if (x == x->parent->left){
                    x = x->parent;
                    rotateRight(D, x);
                }
                //case 6
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(D, x->parent->parent);
            }
        }
    }
    D->root->color = BLACK;
}
void deleteFixUp(Dictionary D, Node x){
    while (x != D->root && x->color == BLACK){
        if (x == x->parent->left){
            Node y = x->parent->right;
            //case 1
            if (y->color){
                y->color = BLACK;
                x->parent->color = RED;
                rotateLeft(D, x->parent);
                y = x->parent->right;
            }
            //case 2
            if (y->left->color == BLACK && y->right->color == BLACK){
                y->color = RED;
                x = x->parent;
            }
            else {
                //case 3
                if (y->right->color == BLACK){
                    y->left->color = BLACK;
                    y->color = RED;
                    rotateRight(D, y);
                    y = x->parent->right;
                }
                //case 4
                y->color = x->parent->color;
                x->parent->color = BLACK;
                y->right->color = BLACK;
                rotateLeft(D, x->parent);
                x = D->root;
            }
        }
        else {
            Node y = x->parent->left;
            //case 5
            if (y->color == RED){
                y->color = BLACK;
                x->parent->color = RED;
                rotateRight(D, x->parent);
                y = x->parent->left;
            }
            //case 6
            if (y->right->color == BLACK && y->left->color == BLACK){
                y->color = RED;
                x = x->parent;
            }
            else {
                //case 7
                if (y->left->color == BLACK){
                    y->right->color = BLACK;
                    y->color = RED;
                    rotateLeft(D, y);
                    y = x->parent->left;
                }
                //case 8
                y->color = x->parent->color;
                x->parent->color = BLACK;
                y->left->color = BLACK;
                rotateRight(D, x->parent);
                x = D->root;
            }
        }
    }
    x->color = BLACK;
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
        D->root->color = BLACK;
    }
    else if (KEY_CMP(k, y->keyData) < 0){
        y->left = z;
    }
    else {
        y->right = z;
    }
    insertFixUp(D, z);
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
    Node y = target;
    Node x = NULL;
    int yOGColor = y->color;

    if (target->left == D->nil){
        x = target->right;
        transplant(D, target, target->right);
    }
    else if (target->right == D->nil){
        x = target->left;
        transplant(D, target, target->left);
    }
    else {
        y = minimum(D, target->right);
        yOGColor = y->color;
        x = y->right;
        if (y->parent == target){
            x->parent = y;
        }
        else {
            transplant(D, y, y->right);
            y->right = target->right;
            y->right->parent = y;
        }
        transplant(D, target, y);
        y->left = target->left;
        y->left->parent = y;
        y->color = target->color;
    }
    if (yOGColor == BLACK){
        deleteFixUp(D, x);
    }

    D->length--;
    if (D->cursor == target) D->cursor = D->nil;
    freeNode(&target);
}

// makeEmpty()
    // Reset Dictionary D to the empty state, containing no pairs.
void deletePostOrder(Dictionary D, Node x){
    if (x == D->nil) return;
    deletePostOrder(D, x->left);
    deletePostOrder(D, x->right);
    freeNode(&x);
}
void makeEmpty(Dictionary D){
    if (D == NULL){
        printf("Dictionary Error: calling makeEmpty on NULL\n");
        exit(1);
    }
    deletePostOrder(D, D->root);
    D->cursor = D->root = D->nil;
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
// Prints the keys (only) of D in an order determined by the parameter ord.
// If ord is "pre", "in" or "post", executes the corresponding tree traversal
// on the underlying RBT, printing keys only (no values).  If ord is some
// other string, prints nothing.

// Algorithm Preorder(tree)
//    1. Visit the root.
//    2. Traverse the left subtree, i.e., call Preorder(left-subtree)
//    3. Traverse the right subtree, i.e., call Preorder(right-subtree) 
void preOrder(FILE* out, Dictionary D, Node x){
    if (x == D->nil) return;
    fprintf(out, ""KEY_FORMAT"\n", x->keyData);
    preOrder(out, D, x->left);
    preOrder(out, D, x->right);
}
// Algorithm Inorder(tree)
//    1. Traverse the left subtree, i.e., call Inorder(left-subtree)
//    2. Visit the root.
//    3. Traverse the right subtree, i.e., call Inorder(right-subtree)
void inOrder(FILE* out, Dictionary D, Node x){
    if (x == D->nil) return;
    inOrder(out, D, x->left);
    fprintf(out, ""KEY_FORMAT"\n", x->keyData);
    inOrder(out, D, x->right);
}
// Algorithm Postorder(tree)
//    1. Traverse the left subtree, i.e., call Postorder(left-subtree)
//    2. Traverse the right subtree, i.e., call Postorder(right-subtree)
//    3. Visit the root.
void postOrder(FILE* out, Dictionary D, Node x){
    if (x == D->nil) return;
    postOrder(out, D, x->left);
    postOrder(out, D, x->right);
    fprintf(out, ""KEY_FORMAT"\n", x->keyData);
}
void printDictionary(FILE* out, Dictionary D, const char* ord){
    if (D == NULL){
        printf("Dictionary Error: calling printDictionary() on NULL\n");
        exit(1);
    }
    if (size(D) == 0){
        return;
    }

    if (KEY_CMP(ord, "pre") == 0){
        preOrder(out, D, D->root);
    }
    else if (KEY_CMP(ord, "in") == 0){
        inOrder(out, D, D->root);
    }
    else if (KEY_CMP(ord, "post") == 0){
        postOrder(out, D, D->root);
    } 
}
