#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
template<typename T>
class TreeNode{
    public:
    T data;
    unique_ptr<TreeNode> leftChild;
    unique_ptr<TreeNode> rightChild;
    TreeNode<T> * parent;
    TreeNode(T newData)
    : data(newData), parent(nullptr){
    }

    void setLeftChild(TreeNode* child){
        leftChild.reset(child);
        child->parent = this;
    }
    void setRightChild(TreeNode* child){
        rightChild.reset(child);
        child->parent = this;
    }
    void write(ostream & o) const{
        if (leftChild){
            leftChild.get()->write(o);
        }
        o << " " << this->data << " ";
        if (rightChild){
            rightChild.get()->write(o);
        }
    }

    int maxDepth(){
        if (leftChild == nullptr && rightChild == nullptr){
            return 1;
        }
        int leftDepth = 0;
        int rightDepth = 0;
        if (leftChild){
            leftDepth = leftChild.get()->maxDepth();
        }
        if (rightChild){
            rightDepth = rightChild.get()->maxDepth();
        }
        int maxDepth = 0;
        if (leftDepth > rightDepth){
            return leftDepth +1;
        }
        else {
            return rightDepth +1;
        };
    }

    int leftDepth(){
        if (leftChild){
            return leftChild.get()->maxDepth();
        }
        return 0;
    }

    int rightDepth(){
        if (rightChild){
            return rightChild.get()->maxDepth();
        }
        return 0;
    }
    int getBalance(){
        return leftDepth() - rightDepth();
    }


};

template<typename T>
class TreeNodeIterator{
    private:
    TreeNode<T>* current;
    public:
    TreeNodeIterator(TreeNode<T>* node)
    : current(node) {

    }
    T & operator*() {
        return current->data;
    }
    TreeNode<T>* getCurrent(){
        return current;
    }
    void operator++(){
        TreeNode<T>* toCompare;
        if (getCurrent()->rightChild != nullptr){
            current = current->rightChild.get();
            while (current->leftChild != nullptr){
                current = current->leftChild.get();
            }
        }
        else
        {
            toCompare = current->parent;
            while (toCompare != nullptr && current == toCompare->rightChild.get()){
                current = toCompare;
                toCompare = toCompare->parent;
            }
            current = toCompare;
        }
        
    }

    bool operator==(TreeNodeIterator<T> other){
        return (getCurrent() == other.getCurrent());
    }
    
    bool operator!=(TreeNodeIterator<T> other){
        return (current != other.current);
    }
    
};
// do not edit below this line

#endif
