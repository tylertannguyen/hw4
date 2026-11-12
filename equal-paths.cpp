#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool checkPaths(Node* root, int depth, int& leafDepth)
{
    // Base case: return true if the tree is empty
    if (root == nullptr) {
        return true;
    }
    // A leaf has no children.
    if (root->left == nullptr && root->right == nullptr) {
        // Save the depth of the first leaf.
        if (leafDepth == -1) {
            leafDepth = depth;
        }
        return depth == leafDepth;
    }

    // Both subtrees must have leaves at the expected depth.
    return checkPaths(root->left, depth + 1, leafDepth) && checkPaths(root->right, depth + 1, leafDepth);
}

bool equalPaths(Node * root)
{
    // Add your code below
    // Initialize leafDepth to -1 to show no leaf found yet
    int leafDepth = -1;
    return checkPaths(root, 0, leafDepth);
}

