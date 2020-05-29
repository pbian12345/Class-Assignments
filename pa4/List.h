
#ifndef PA3_LIST_H
#define PA3_LIST_H

#define TYPE int

// Structs --------------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void); // Creates and returns a new empty List.
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets
                         // *pL to NULL.

// Access functions -----------------------------------------------------------
long length(List L); // Returns the number of elements in L.
long index(List L); // Returns index of cursor element if defined, -1 otherwise.
TYPE front(List L); // Returns front element of L. Pre: length()>0
TYPE back(List L); // Returns back element of L. Pre: length()>0
TYPE get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
int equals(List A, List B); // Returns true (1) iff Lists A and B are in same
                            // state, and returns false (0) otherwise.


// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void moveFront(List L); // If L is non-empty, sets cursor under the front element,
                        // otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element,
                       // otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one
                        // step toward the front of L; if cursor is defined and at
                        // front, cursor becomes undefined; if cursor is undefined
                        // do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one
                        // step toward the back of L; if cursor is defined and at
                        // back, cursor becomes undefined; if cursor is undefined
                        // do nothing
void prepend(List L, TYPE data); // Insert new element into L. If L is non-empty,
                                // insertion takes place before front element.
void append(List L, TYPE data); // Insert new element into L. If L is non-empty,
                                // insertion takes place after back element.
void insertBefore(List L, TYPE data); // Insert new element before cursor.
                                    // Pre: length()>0, index()>=0
void insertAfter(List L, TYPE data); // Insert new element before cursor.
                                    // Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.
                    // Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints to the file pointed to by out, a
                                 // string representation of L consisting
                                // of a space separated sequence of integers,
                                // with front on left.// Returns a new List representing the same integer

// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L);

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0
void set(List L, TYPE x);

//reverse()
//little something to reverse order of list
void reverse(List L);



#endif //PA3_LIST_H