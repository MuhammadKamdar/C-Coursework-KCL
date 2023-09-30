#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists

template<typename S>
class Node{
    public:
    S data;
    Node *next;
    Node *previous;
    Node(S dataItem)
    : data(dataItem) {
        next = nullptr;
        previous = nullptr;
    }

    bool operator==(Node other){
        return (data == other.data);
    }
    bool operator!=(Node other){
        return (data != other.data);
    }
    ~Node(){};

};



template<typename T>
class NodeIterator {
  
private:
    
    Node<T>* current;
    
public:
    

    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {        
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here
    void operator++(){
        current = current->next;
    }

    void operator--(){
        current = current->previous;
    }

    bool operator==(NodeIterator<T> other){
        return (getCurrent() == other.getCurrent());
    }
    
    bool operator!=(NodeIterator<T> other){
        return (getCurrent() != other.getCurrent());
    }
    Node<T>* getCurrent(){
        return current;
    }
};

// do not edit below this line

#endif
