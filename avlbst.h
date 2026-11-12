#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key, Value>* current);
    void rotateRight(AVLNode<Key, Value>* current);
    void insertFix(AVLNode<Key, Value>* current);
    void removeFix(AVLNode<Key, Value>* current, int difference);

};

template<class Key, class Value>
// Rotate the subtree rooted at current to the left.  Update the balance values of the nodes that are rotated.
void AVLTree<Key, Value>::rotateLeft(
    AVLNode<Key, Value>* current)
{
    AVLNode<Key, Value>* rightChild = current->getRight();
    AVLNode<Key, Value>* parent = current->getParent();

    // Move the right child's left subtree to current's right.
    current->setRight(rightChild->getLeft());

    if (rightChild->getLeft() != nullptr) {
        rightChild->getLeft()->setParent(current);
    }

    // Connect the right child to current's original parent.
    rightChild->setParent(parent);

    if (parent == nullptr) {
        this->root_ = rightChild;
    }
    else if (parent->getLeft() == current) {
        parent->setLeft(rightChild);
    }
    else {
        parent->setRight(rightChild);
    }

    // Place current below its former right child.
    rightChild->setLeft(current);
    current->setParent(rightChild);
}

template<class Key, class Value>
// Rotate the subtree rooted at current to the right.  Update the balance values of the nodes that are rotated.
void AVLTree<Key, Value>::rotateRight(
    AVLNode<Key, Value>* current)
{
    AVLNode<Key, Value>* leftChild = current->getLeft();
    AVLNode<Key, Value>* parent = current->getParent();

    // Move the left child's right subtree to current's left.
    current->setLeft(leftChild->getRight());

    if (leftChild->getRight() != nullptr) {
        leftChild->getRight()->setParent(current);
    }

    // Connect the left child to current's original parent.
    leftChild->setParent(parent);

    if (parent == nullptr) {
        this->root_ = leftChild;
    }
    else if (parent->getLeft() == current) {
        parent->setLeft(leftChild);
    }
    else {
        parent->setRight(leftChild);
    }

    // Place current below its former left child.
    leftChild->setRight(current);
    current->setParent(leftChild);
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // If the tree is empty, create a new root node with the given key-value pair.
    if (this->root_ == nullptr) {
        this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
        return;
    }
    // Start at the root and traverse the tree to find the correct insertion point.
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);

    while (current != nullptr) {
        // Move to the left child.
        if (new_item.first < current->getKey()) {
            // If the left child is null, insert the new node here.
            if (current->getLeft() == nullptr) {
                // Create a new node and set it as the left child of the current node.
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setLeft(newNode);
                insertFix(newNode);
                return;
            }

            current = current->getLeft();
        }
        // Move to the right child.
        else if (new_item.first > current->getKey()) {
            // If the right child is null, insert the new node here.
            if (current->getRight() == nullptr) {
                // Create a new node and set it as the right child of the current node.
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setRight(newNode);
                insertFix(newNode);
                return;
            }
            // Move to the right child.
            current = current->getRight();
        }
        // If the key already exists, overwrite the value and return.
        else {
            current->setValue(new_item.second);
            return;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(
    AVLNode<Key, Value>* current)
{
    AVLNode<Key, Value>* parent = current->getParent();

    while (parent != nullptr) {
        // The subtree containing current grew taller.
        if (current == parent->getLeft()) {
            parent->updateBalance(-1);
        }
        // The subtree containing current grew taller.
        else {
            parent->updateBalance(1);
        }

        // The parent's height did not increase. We are done.
        if (parent->getBalance() == 0) {
            return;
        }
        // The parent's height increased. We need to check if it is now unbalanced.
        if (parent->getBalance() == -2) {
            AVLNode<Key, Value>* left = parent->getLeft();
            // Left subtree is taller than right subtree by 2, so we need to rotate.
            if (left->getBalance() == -1) {
                // Left-left case.
                rotateRight(parent);
                parent->setBalance(0);
                left->setBalance(0);
            }
            else {
                // Left-right case.
                AVLNode<Key, Value>* middle = left->getRight();
                int middleBalance = middle->getBalance();
                // Perform the rotations.
                rotateLeft(left);
                rotateRight(parent);
                // Update the balances.
                if (middleBalance == -1) {
                    parent->setBalance(1);
                    left->setBalance(0);
                }
                // Middle balance is 0, so both children are now balanced.
                else if (middleBalance == 0) {
                    parent->setBalance(0);
                    left->setBalance(0);
                }
                // Middle balance is 1, so the left child is now taller.
                else {
                    parent->setBalance(0);
                    left->setBalance(-1);
                }

                middle->setBalance(0);
            }

            return;
        }
        else if (parent->getBalance() == 2) {
            AVLNode<Key, Value>* right = parent->getRight();

            if (right->getBalance() == 1) {
                // Right-right case.
                rotateLeft(parent);
                parent->setBalance(0);
                right->setBalance(0);
            }
            else {
                // Right-left case.
                AVLNode<Key, Value>* middle = right->getLeft();
                int middleBalance = middle->getBalance();
                // Perform the rotations.
                rotateRight(right);
                rotateLeft(parent);
                // Update the balances.
                if (middleBalance == -1) {
                    parent->setBalance(0);
                    right->setBalance(1);
                }
                // Middle balance is 0, so both children are now balanced.
                else if (middleBalance == 0) {
                    parent->setBalance(0);
                    right->setBalance(0);
                }
                // Middle balance is 1, so the right child is now taller.
                else {
                    parent->setBalance(-1);
                    right->setBalance(0);
                }
                // The middle node is now balanced.
                middle->setBalance(0);
            }

            return;
        }

        // Balance is -1 or 1, so the height increased.
        // Continue checking the next ancestor.
        current = parent;
        parent = current->getParent();
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    // If the key is not found, do nothing.
    if (current == nullptr) {
        return;
    }
    // With two children, swap with the predecessor.
    if (current->getLeft() != nullptr && current->getRight() != nullptr) {
        // The predecessor is guaranteed to have at most one child.
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(current));
        // Swap the nodes and update the current pointer to point to the node that was swapped.
        nodeSwap(current, pred);
    }

    // Current now has at most one child.
    AVLNode<Key, Value>* child = nullptr;
    // If the left child exists, it becomes the child of current's parent.
    if (current->getLeft() != nullptr) {
        child = current->getLeft();
    }
    // Otherwise, the right child (which may be nullptr) becomes the child of current's parent.
    else {
        child = current->getRight();
    }

    AVLNode<Key, Value>* parent = current->getParent();
    int difference = 0;
    // Connect the child to the parent of current.
    if (child != nullptr) {
        child->setParent(parent);
    }
    // Current is the root of the tree.
    if (parent == nullptr) {
        this->root_ = child;
    }
    // Current is the left child of its parent.
    else if (parent->getLeft() == current) {
        parent->setLeft(child);

        // Left subtree became shorter.
        difference = 1;
    }
    else {
        parent->setRight(child);

        // Right subtree became shorter.
        difference = -1;
    }

    delete current;
    // The height of the parent subtree decreased, so we need to fix it.
    if (parent != nullptr) {
        removeFix(parent, difference);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* current, int difference)
{
    // The difference indicates which subtree became shorter: 1 for left, -1 for right.
    while (current != nullptr) {
        // Save the next ancestor before any rotations.
        AVLNode<Key, Value>* parent = current->getParent();
        int nextDifference = 0;
        // Determine the next difference based on the current node's position relative to its parent.
        if (parent != nullptr) {
            // If current is the left child, the next difference is 1; otherwise, it's -1.
            if (current == parent->getLeft()) {
                nextDifference = 1;
            }
            // If current is the right child, the next difference is -1.
            else {
                nextDifference = -1;
            }
        }
        // Update the balance of the current node based on which subtree became shorter.
        current->updateBalance(difference);
        // If the balance is now -1 or 1, the height of the subtree did not change, so we can stop.
        if (current->getBalance() == -1 || current->getBalance() == 1) {
            // The subtree's height stayed the same.
            return;
        }
        // If the balance is now 0, the height of the subtree decreased, so we need to continue up the tree.
        else if (current->getBalance() == -2) {
            AVLNode<Key, Value>* left = current->getLeft();
            // Left subtree is taller than right subtree by 2, so we need to rotate.
            if (left->getBalance() == 0) {
                rotateRight(current);
                current->setBalance(-1);
                left->setBalance(1);

                // This rotation did not reduce the subtree's height.
                return;
            }
            // Left-left case.
            else if (left->getBalance() == -1) {
                rotateRight(current);
                current->setBalance(0);
                left->setBalance(0);
            }
            // Left-right case.
            else {
                // Left-right case.
                AVLNode<Key, Value>* middle = left->getRight();
                int middleBalance = middle->getBalance();
                // Perform the rotations.
                rotateLeft(left);
                rotateRight(current);
                // Update the balances based on the middle node's balance.
                if (middleBalance == -1) {
                    current->setBalance(1);
                    left->setBalance(0);
                }
                // Middle balance is 0, so both children are now balanced.
                else if (middleBalance == 0) {
                    current->setBalance(0);
                    left->setBalance(0);
                }
                // Middle balance is 1, so the left child is now taller.
                else {
                    current->setBalance(0);
                    left->setBalance(-1);
                }
                // The middle node is now balanced.
                middle->setBalance(0);
            }
        }
        // If the balance is now 2, the right subtree is taller than the left subtree by 2, so we need to rotate.
        else if (current->getBalance() == 2) {
            AVLNode<Key, Value>* right = current->getRight();
            // Right subtree is taller than left subtree by 2, so we need to rotate.
            if (right->getBalance() == 0) {
                rotateLeft(current);
                current->setBalance(1);
                right->setBalance(-1);

                // This rotation did not reduce the subtree's height.
                return;
            }
            // Right-right case.
            else if (right->getBalance() == 1) {
                rotateLeft(current);
                current->setBalance(0);
                right->setBalance(0);
            }
            // Right-left case.
            else {
                // Right-left case.
                AVLNode<Key, Value>* middle = right->getLeft();
                int middleBalance = middle->getBalance();
                // Perform the rotations.
                rotateRight(right);
                rotateLeft(current);
                // Update the balances based on the middle node's balance.
                if (middleBalance == -1) {
                    current->setBalance(0);
                    right->setBalance(1);
                }
                // Middle balance is 0, so both children are now balanced.
                else if (middleBalance == 0) {
                    current->setBalance(0);
                    right->setBalance(0);
                }
                // Middle balance is 1, so the right child is now taller.
                else {
                    current->setBalance(-1);
                    right->setBalance(0);
                }
                // The middle node is now balanced.
                middle->setBalance(0);
            }
        }

        // The subtree became shorter. Check its original parent.
        current = parent;
        difference = nextDifference;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
