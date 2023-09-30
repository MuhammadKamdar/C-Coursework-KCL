#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

#include <utility>
#include <initializer_list>
using std::initializer_list;


// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:
template <typename T>
class LinkedList{
    public:
    Node<T> *head;
    Node<T> *tail;
    int count;

    LinkedList(){
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    LinkedList(initializer_list<T> nList){
        head = nullptr;
        tail = nullptr;
        count = 0;
        for (auto & n : nList){
            push_back(n);
        }
    }
    
    ~LinkedList(){
        NodeIterator<T> endIter(end());
        NodeIterator<T> iter(begin());
        while (iter != endIter){
            NodeIterator<T> iter2(iter.getCurrent()->next);
            delete iter.getCurrent();
            cout<<"node deleted\n";
            iter = iter2;
        }
        cout << "List deleted\n";
    }

    NodeIterator<T> insert(NodeIterator<T> iter, T n){
        NodeIterator<T> endIt(end());
        NodeIterator<T> beginIt(begin());
        if (iter == beginIt)
        {
            push_front(n);
            return beginIt;
        }
        if (iter == endIt)
        {
            push_back(n);
            return endIt;
        }
        Node<T> *newNode = new Node<T>(n);
        NodeIterator<T> temp(iter.getCurrent()->previous);
        newNode->next = iter.getCurrent();
        newNode->previous = temp.getCurrent();
        temp.getCurrent()->next = newNode;
        iter.getCurrent()->previous = newNode;
        --iter;
        return iter;

    }
    NodeIterator<T> erase(NodeIterator<T> iter){
        NodeIterator<T> it(iter.getCurrent()->next);
        if (iter != begin()){
            NodeIterator<T> it2(iter.getCurrent()->previous);
            it.getCurrent()->previous = it2.getCurrent();
            it2.getCurrent()->next = it.getCurrent();
        }
        if (iter == begin()){
            head = it.getCurrent();
            it.getCurrent()->previous = nullptr;
        }
        delete iter.getCurrent();
        return it;
    }

    void push_front(T data){
        Node<T> *newNode = new Node<T>(data);
        if (count == 0){
            tail = newNode;
        }
        else {
            newNode->next = head;
            head->previous = newNode;
        }
        head = newNode;
        count++;
    }

    T & front(){
        return head->data;
    }

    void push_back(T data){
        Node<T> *newNode = new Node<T>(data);
        if (count == 0){
            head = newNode;
        }
        else
        {
            newNode->previous = tail;
            tail->next = newNode; 
        }
        tail = newNode;
        count++;
    }

    T & back(){
        return tail->data;
    }

    int size(){
        return count;
    }

    NodeIterator<T> begin() const{
        NodeIterator<T> begin(head);
        return begin;
    }

    NodeIterator<T> end()const{
        NodeIterator<T> end(nullptr);
        return end;
    }
    void reverse(){
        NodeIterator<T> iter(tail);
        NodeIterator<T> endIter(end());
        Node<T> *temp = head;
        head = tail;
        tail = temp;
        while (iter != endIter)
        {
            Node<T> *temp2 = iter.getCurrent()->next;
            iter.getCurrent()->next = iter.getCurrent()->previous;
            iter.getCurrent()->previous = temp2;
            ++iter;
        }
    }

};



// do not edit below this line

#endif
