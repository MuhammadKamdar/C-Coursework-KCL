#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:
template<typename T>
class BinarySearchTree{
    private:
    unique_ptr<TreeNode<T>> root;

    public:

    BinarySearchTree(){
    }
    BinarySearchTree(BinarySearchTree<T>& other){
        copyNode(root.get(), other.root.get());
    }
    
    void copyNode(TreeNode<T>* copy, const TreeNode<T>* orignal) const{
        if (orignal == nullptr){
            copy = nullptr;
        }
        else {
            copy = new TreeNode<T>;
            copy->data = orignal->data;
            copyNode(copy->leftChild.get(), orignal->leftChild.get());
            copyNode(copy->rightChild.get(), orignal->rightChild.get());
            copyNode(copy->parent, orignal->parent);
        }
    }


    void write(ostream& o)const{
            root->write(o);
    }

    TreeNode<T>* insert(T data){
        if (root){
            TreeNode<T> *tree = root.get();
            TreeNode<T> *prevNode;
            while (tree != nullptr){
                if (data < tree->data){
                    prevNode = tree;
                    tree = tree->leftChild.get();
                }
                else if (tree->data < data){
                    prevNode = tree;
                    tree = tree->rightChild.get();
                }
                else {
                    return tree;
                }
            }
            TreeNode<T>* newNode = new TreeNode<T>(data);
            if (newNode->data < prevNode->data){
                prevNode->setLeftChild(newNode);
            }
            else {
                prevNode->setRightChild(newNode);
            }
            if (prevNode != root.get()){
                balance(newNode);
            }
            return newNode;
        }
        else {
            TreeNode<T>* newNode = new TreeNode<T>(data);
            root.reset(newNode);
            return newNode;
        }
    }

    int maxDepth(){
        if (root){
            return root.get()->maxDepth();
        }
        else {
            return 0;
        }
    }

    TreeNode<T>* find(T data){
        TreeNode<T> *tree(root.get());
        while (tree != nullptr){
            if (data < tree->data){
                tree = tree->leftChild.get();
            }
            else if (tree->data < data){
                tree = tree->rightChild.get();
            }
            else {
                return tree;
            }
        }
        return nullptr;
    }

    void balance(TreeNode<T>* insertedNode){
        TreeNode<T>* parent = insertedNode->parent;
        TreeNode<T>* grandParent = parent->parent;
        int balanceFactorG = grandParent->getBalance();
        int balanceFactorP = parent->getBalance();
            //left left case
        if (balanceFactorG == 2 && balanceFactorP == 1){
            insertedNode->parent = rightRotation(insertedNode->parent);
        }
        //right right case
        if (balanceFactorG == -2 && balanceFactorP == -1){
            insertedNode->parent = leftRotation(insertedNode->parent);
        }
        //left right case
        if (balanceFactorG == 2 && balanceFactorP == -1){
            parent->setLeftChild(parent->rightChild.release());
            insertedNode->parent = rightRotation(insertedNode->parent);
        }
        //right left case
        if (balanceFactorG == -2 && balanceFactorP == 1){
            parent->setRightChild(parent->leftChild.release());
            insertedNode->parent = leftRotation(insertedNode->parent);
        }
        
    }


    TreeNode<T>* rightRotation(TreeNode<T>* &current){
        if (current->parent == root.get()){
            auto leftChild = current->parent->leftChild.release();
            auto rooot = root.release();
            auto child = current->leftChild.release();
            if(child->data < leftChild->data){
                root.reset(leftChild);
                current->parent = nullptr;
                if (child->data < rooot->data){
                    root.get()->setRightChild(rooot);
                    root.get()->setLeftChild(child);
                }
                else {
                    root.get()->setRightChild(child);
                    root.get()->setLeftChild(rooot);
                }
            }
            else {
                root.reset(child);
                current = nullptr;
                if (leftChild->data < rooot->data){
                    root.get()->setRightChild(rooot);
                    root.get()->setLeftChild(leftChild);
                }
                else {
                    root.get()->setRightChild(leftChild);
                    root.get()->setLeftChild(rooot);
                }
            }
        }
        else {
            auto gp = current->parent->parent;
            auto releaseGP = current->parent->parent->leftChild.release();
            auto currenttt = current->parent->leftChild.release();
            auto leftSide = current->leftChild.release();
            if (leftSide->data < currenttt->data){
                gp->setLeftChild(currenttt);
                if(leftSide->data < releaseGP->data){
                currenttt->setRightChild(releaseGP);
                currenttt->setLeftChild(leftSide);
                }
                else {
                currenttt->setRightChild(leftSide);
                currenttt->setLeftChild(releaseGP);
                }
            }
            else {
                gp->setLeftChild(leftSide);
                if (currenttt->data < releaseGP->data){
                    leftSide->setRightChild(releaseGP);
                    leftSide->setLeftChild(currenttt);
                }
                else {
                    leftSide->setRightChild(currenttt);
                    leftSide->setLeftChild(releaseGP);
                }
            }
            
        }
        return current;
        
    }
    TreeNode<T>* leftRotation(TreeNode<T>* current){
        if (current->parent == root.get()){
            auto rightChild = current->parent->rightChild.release();
            auto tempRoot = root.release();
            auto child = current->rightChild.release();
            if (rightChild->data < child->data){
                root.reset(rightChild);
                current->parent = nullptr;
                if (child->data < tempRoot->data){
                    root.get()->setRightChild(tempRoot);
                    root.get()->setLeftChild(child);
                }
                else {
                    root.get()->setRightChild(child);
                    root.get()->setLeftChild(tempRoot);
                }
            }
            else {
                root.reset(child);
                current = nullptr;
                if (rightChild->data < tempRoot->data){
                    root.get()->setRightChild(tempRoot);
                    root.get()->setLeftChild(rightChild);
                }
                else {
                    root.get()->setRightChild(rightChild);
                    root.get()->setLeftChild(tempRoot);
                }
            }
        }
        else {
            auto gp = current->parent->parent;
            auto releaseGp = current->parent->parent->rightChild.release();
            auto tempCurrent = current->parent->rightChild.release();
            auto rightSide = current->rightChild.release();
            if (rightSide->data < tempCurrent->data){
                gp->setLeftChild(rightSide);
                if (tempCurrent->data < releaseGp->data){
                    rightSide->setRightChild(releaseGp);
                    rightSide->setLeftChild(tempCurrent);
                }
                else {
                    rightSide->setRightChild(tempCurrent);
                    rightSide->setLeftChild(releaseGp);
                }
            }
            else {
                gp->setLeftChild(tempCurrent);
                if (rightSide->data < releaseGp->data){
                    tempCurrent->setRightChild(releaseGp);
                    tempCurrent->setLeftChild(rightSide);
                }
                else {
                    tempCurrent->setRightChild(rightSide);
                    tempCurrent->setLeftChild(releaseGp);
                }
            }
        }
        return current;
    }

    TreeNodeIterator<T> end() const{
        TreeNodeIterator<T> end(nullptr);
        return end;
    }
    TreeNodeIterator<T> begin() const{
        TreeNode<T>* node = root.get();
        if (root){
        while (node->leftChild){
            node = node->leftChild.get();
        }
        TreeNodeIterator<T> begin(node);
        return begin;
        }
        return nullptr;
    }

    BinarySearchTree<T>& operator=(const BinarySearchTree<T>& that){
        if (this != that){
            TreeNode<T> *node = that.root;
            assignmentInsert(node);
        }
    }
    void assignmentInsert(TreeNode<T>* node){
        if(node != nullptr){
            this->insert(node->data);
            assignmentInsert(node->leftChild.get());
            assignmentInsert(node->rightChild.get());
        }
    }
};

// do not edit below this line

#endif