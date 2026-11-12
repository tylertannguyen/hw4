#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clearHelper(Node<Key, Value>* current);
    int balancedHeight(Node<Key, Value>* current) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = nullptr;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if (current_ == nullptr) {
        return *this;
    }

    if (current_->getRight() != nullptr) {
        // Find the smallest node in the right subtree.
        current_ = current_->getRight();

        while (current_->getLeft() != nullptr) {
            current_ = current_->getLeft();
        }
    }
    else {
        Node<Key, Value>* parent = current_->getParent();

        // Skip ancestors whose right subtree we just finished.
        while (parent != nullptr &&
               current_ == parent->getRight()) {
            current_ = parent;
            parent = parent->getParent();
        }

        current_ = parent;
    }

    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // If the tree is empty, create the root.
    if (root_ == nullptr) {
        root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
        return;
    }
    // Otherwise, traverse the tree to find the correct location for the new node.
    Node<Key, Value>* current = root_;
    // Traverse the tree until we find a null child where we can insert the new node.
    while (current != nullptr) {
        // If the key is less than the current node's key, go left.
        if (keyValuePair.first < current->getKey()) {
            if (current->getLeft() == nullptr) {
                // Create a left child with current as its parent.
                current->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current));
                return;
            }

            current = current->getLeft();
        }
        // If the key is greater than the current node's key, go right.
        else if (keyValuePair.first > current->getKey()) {
            if (current->getRight() == nullptr) {
                // Create a right child with current as its parent.
                current->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current));
                return;
            }
            // Move to the right child.
            current = current->getRight();
        }
        else {
            // The key exists, so replace its value.
            current->setValue(keyValuePair.second);
            return;
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    Node<Key, Value>* current = internalFind(key);

    // Nothing to remove if the key is missing.
    if (current == nullptr) {
        return;
    }

    // With two children, swap with the predecessor first.
    if (current->getLeft() != nullptr &&
        current->getRight() != nullptr) {
        Node<Key, Value>* pred = predecessor(current);
        nodeSwap(current, pred);
    }

    // Current now has at most one child.
    Node<Key, Value>* child = nullptr;
    // Set child to the non-null child of current
    if (current->getLeft() != nullptr) {
        child = current->getLeft();
    }
    // If the left child is null, then the right child may be non-null.
    else {
        child = current->getRight();
    }

    Node<Key, Value>* parent = current->getParent();

    // Connect the child back to its new parent.
    if (child != nullptr) {
        child->setParent(parent);
    }
    // Connect the parent to the child.
    if (parent == nullptr) {
        // We are removing the root.
        root_ = child;
    }
    // If current is the left child of its parent, set the parent's left to child.
    else if (parent->getLeft() == current) {
        parent->setLeft(child);
    }
    // If current is the right child of its parent, set the parent's right to child.
    else {
        parent->setRight(child);
    }

    delete current;
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // If the current node is null, there is no predecessor.
    if (current == nullptr) {
        return nullptr;
    }
    // If the current node has a left child, the predecessor is the largest node in the left subtree.
    if (current->getLeft() != nullptr) {
        // Find the largest node in the left subtree.
        current = current->getLeft();
        // Keep moving right until there is no right child.
        while (current->getRight() != nullptr) {
            current = current->getRight();
        }
        // Return the rightmost node, which is the predecessor.
        return current;
    }
    // If the current node does not have a left child, the predecessor is one of its ancestors.
    else {
        Node<Key, Value>* parent = current->getParent();

        // Keep going up while coming from a left child.
        while (parent != nullptr && current == parent->getLeft()) {
            // Move up the tree.
            current = parent;
            parent = parent->getParent();
        }
        // Return the parent, which is the predecessor (or null if there is none).
        return parent;
    }
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // Use a helper function to recursively delete all nodes in the tree.
    clearHelper(root_);
    root_ = nullptr;
}
// Helper function to recursively delete all nodes in the tree.
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(
    Node<Key, Value>* current)
{
    // Base case: if the current node is null, return.
    if (current == nullptr) {
        return;
    }
    // Recursively clear the left and right subtrees.
    clearHelper(current->getLeft());
    clearHelper(current->getRight());

    delete current;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* current = root_;

    // An empty tree has no smallest node.
    if (current == nullptr) {
        return nullptr;
    }

    // Keep moving left until there is no left child.
    while (current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    // Return the leftmost node, which is the smallest.
    return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* current = root_;
    // Traverse the tree to find the node with the given key.
    while (current != nullptr) {
        // If the key is less than the current node's key, go left.
        if (key < current->getKey()) {
            current = current->getLeft();
        }
        // If the key is greater than the current node's key, go right.
        else if (key > current->getKey()) {
            current = current->getRight();
        }
        // If the key matches the current node's key, return the current node.
        else {
            return current;
        }
    }
    // If we reach a null node, the key is not in the tree.
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return balancedHeight(root_) != -1;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::balancedHeight(
    Node<Key, Value>* current) const
{
    // An empty subtree has height 0.
    if (current == nullptr) {
        return 0;
    }

    int leftHeight = balancedHeight(current->getLeft());
    int rightHeight = balancedHeight(current->getRight());

    // An unbalanced child makes this subtree unbalanced.
    if (leftHeight == -1 || rightHeight == -1) {
        return -1;
    }
    int difference = leftHeight - rightHeight;
    // If the difference in heights is greater than 1, this subtree is unbalanced.
    if (difference > 1 || difference < -1) {
        return -1;
    }

    // This subtree's height is its taller child's height plus 1.
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    // If the right child is taller or they are equal, return rightHeight + 1.
    else {
        return rightHeight + 1;
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    // Save the parent, left, and right pointers of both nodes.
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    // Determine if n1 is a left child of its parent.
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    // Save the parent, left, and right pointers of n2.
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    // Determine if n2 is a left child of its parent.
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;
    // Swap the parent, left, and right pointers of n1 and n2.
    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);
    // Swap the left and right children of n1 and n2.
    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);
    // Swap the right children of n1 and n2.
    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);
    // Handle the case where n1 and n2 are direct parent-child.
    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    // Handle the case where n2 is the right child of n1.
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    // Handle the case where n1 is the left child of n2.
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);
    }
    // Handle the case where n2 is the left child of n1.
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }
    // Update the parent pointers of n1 and n2's parents to point to the new children.
    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    // Update the parent pointers of n1 and n2's children to point to the new parents.
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    // Update the parent pointers of n1 and n2's children to point to the new parents.
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }
    // Update the parent pointers of n2 and n1's parents to point to the new children.
    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    // Update the parent pointers of n2 and n1's children to point to the new parents.
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    // Update the parent pointers of n2 and n1's children to point to the new parents.
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }
    // Finally, update the root pointer if necessary.
    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
