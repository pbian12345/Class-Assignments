/****************************************************************************************
*  List.cpp
*  File for List ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA7
*****************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include "List.h"

using namespace std;

//Private CTOR for Node
List::Node::Node(int x){
    data = x;
    next = nullptr;
    prev = nullptr;
}


// Class Constructors & Destructors ----------------------------------------

List::List(){
    frontDummy = new List::Node(-1);
    backDummy = new List::Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = new List::Node(-1);
    backDummy = new List::Node(-1);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node* temp = L.frontDummy->next;
    for (int i = 0; i < L.num_elements; i++){
        insertBefore(temp->data);
        temp = temp->next;
    }
    num_elements = L.num_elements;
    temp = L.frontDummy->next;
    for (moveFront(), temp = L.frontDummy->next; temp != L.afterCursor; moveNext(), temp = temp->next){}
}

List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
    return size() > 0 ? false : true;
}

// Returns the size of this List.
int List::size(){
    return num_elements;
}

// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
    return pos_cursor;
}


// Manipulation procedures -------------------------------------------------

// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// Moves cursor to position size() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
    if (position() >= size()){
        cout<<"List Error: calling peekNext() on position() < size()"<<endl;
        exit(1);
    }
    return afterCursor->data;
}

// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
    if (position() <= 0){
        cout<<"List Error: calling peekNext() on position() > 0"<<endl;
        exit(1);
    }
    return beforeCursor->data;
}

// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int List::moveNext(){
    if (position() >= size()){
        cout<<"List Error: calling moveNext() on position() >= size()"<<endl;
        exit(1);
    }
    pos_cursor++;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int List::movePrev(){
    if (position() <= 0){
        cout<<"List Error: calling movePrev() on position() <= 0"<<endl;
        exit(1);
    }
    pos_cursor--;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;
}

// Inserts x after cursor.
void List::insertAfter(int x){
    Node* toInsert = new List::Node(x);
    if (isEmpty()){
        frontDummy->next = toInsert;
        backDummy->prev = toInsert;
        toInsert->next = backDummy;
        toInsert->prev = frontDummy;
        afterCursor = toInsert;
    }
    else if (!position()){
        frontDummy->next = toInsert;
        afterCursor->prev = toInsert;
        toInsert->next = afterCursor;
        toInsert->prev = frontDummy;
        afterCursor = toInsert;
    }
    else if (position() == size()){
        backDummy->prev = toInsert;
        beforeCursor->next = toInsert;
        toInsert->prev = beforeCursor;
        toInsert->next = backDummy;
        afterCursor = toInsert;
    }
    else {
        afterCursor->prev = toInsert;
        beforeCursor->next = toInsert;
        toInsert->next = afterCursor;
        toInsert->prev = beforeCursor;
        afterCursor = toInsert;
    }
    num_elements++;
}

// Inserts x before cursor.
void List::insertBefore(int x){
    Node* toInsert = new List::Node(x);
    if (isEmpty()){
        frontDummy->next = toInsert;
        backDummy->prev = toInsert;
        toInsert->next = backDummy;
        toInsert->prev = frontDummy;
        beforeCursor = toInsert;
    }
    else if (!position()){
        frontDummy->next = toInsert;
        afterCursor->prev = toInsert;
        toInsert->next = afterCursor;
        toInsert->prev = frontDummy;
        beforeCursor = toInsert;
    }
    else if (position() == size()){
        backDummy->prev = toInsert;
        beforeCursor->next = toInsert;
        toInsert->prev = beforeCursor;
        toInsert->next = backDummy;
        beforeCursor = toInsert;
    }
    else {
        afterCursor->prev = toInsert;
        beforeCursor->next = toInsert;
        toInsert->next = afterCursor;
        toInsert->prev = beforeCursor;
        beforeCursor = toInsert;
    }
    num_elements++;
    pos_cursor++;
}

// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
    if (position() >= size()){
        cout<<"List Error: eraseAfter() called on position() >= size()"<<endl;
        exit(1);
    }
    if (backDummy == afterCursor) return;
    Node* temp = afterCursor;
    beforeCursor->next = temp->next;
    temp->next->prev = beforeCursor;
    temp->next = nullptr;
    temp->prev = nullptr;
    afterCursor = beforeCursor->next;
    num_elements--;
    delete temp;
}

// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if (position() <= 0){
        cout<<"List Error: calling eraseBefore() on position() <= 0"<<endl;
        exit(1);
    }
    if (frontDummy == beforeCursor) return;
    Node* temp = beforeCursor;
    afterCursor->prev = temp->prev;
    temp->prev->next = afterCursor;
    temp->next = nullptr;
    temp->prev = nullptr;
    beforeCursor = afterCursor->prev;
    pos_cursor--;
    num_elements--;
    delete temp;
}

// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x){
    while (position() < size()){
        if (afterCursor->data == x){
            moveNext();
            return position();
        }
        moveNext();
    }
    pos_cursor = size();
    return -1;
}

// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x){
    while (position() > 0){
        if (beforeCursor->data == x){
            movePrev();
            return position();
        }
        movePrev();
    }
    pos_cursor = 0;
    return -1;
}

// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup(){
    //keep track of original position for the end...
    int ogPos = position();
    vector<int> keepers;

    moveFront();
    while (position() < size()){
        bool hit = false;
        for (unsigned i = 0; i < keepers.size(); i++){
            if (afterCursor->data == keepers[i]){
                eraseAfter();
                if (position() < ogPos) ogPos--;
                hit = true;
                break;
            }
        }
        if (!hit){
            keepers.push_back(afterCursor->data);
            moveNext();
        }
    }
    for (moveFront(); position() < ogPos; moveNext()){}
}

// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    while (size() > 0){
        moveBack();
        eraseBefore();
    }
}

// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List &L){
    List result(*this);
    List temp(L);
    for (; temp.position() < temp.size(); temp.moveNext()){
        result.moveBack();
        result.insertAfter(temp.afterCursor->data);
    }
    result.moveFront();
    return result;
}


// Other Functions ---------------------------------------------------------

// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
string List::to_string(){
    if (isEmpty()){
        return "()";
    }
    int ogPos = position();
    Node* ogBefore = beforeCursor;
    Node* ogAfter = afterCursor;
    string result = "(";
    for (moveFront(); position() < size(); moveNext()){
        result += std::to_string(afterCursor->data);
        if (position() < size() - 1) result += ", ";
    }
    result.append(")");
    pos_cursor = ogPos;
    beforeCursor = ogBefore;
    afterCursor = ogAfter;
    return result;
}

// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R){
    if (this == &R) return true;
    Node* walkerA = frontDummy->next;
    Node* walkerB = R.frontDummy->next;

    while (walkerA != backDummy && walkerB != R.backDummy){
        if (walkerA->data != walkerB->data) return false;
        walkerA = walkerA->next;
        walkerB = walkerB->next;
    }
    if (walkerA != backDummy || walkerB != R.backDummy) return false;
    return true;
}


// Overriden Operators -----------------------------------------------------

// Inserts string representation of L into stream.
ostream& operator<<(ostream& stream, List& L){
    return stream << L.List::to_string();
}

// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(List& A, const List& B){
    return A.List::equals(B);
}

// Overwrites the state of this List with state of L.
List& List::operator=(const List &L){
    if (this != &L){
        List temp(L);

        swap(frontDummy, temp.frontDummy);
        swap(backDummy, temp.backDummy);
        swap(beforeCursor, temp.beforeCursor);
        swap(afterCursor, temp.afterCursor);
        swap(pos_cursor, temp.pos_cursor);
        swap(num_elements, temp.num_elements);
    }
    return *this;
}
