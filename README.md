# AVL-BST-Optimized
An optimized implementation of AVL BST in C++

## Introduction 
In traditional implementations of an AVL BST,
the height and balance of each Node is calculated
whenever a new Node is added to the Tree. This project
aims at optimizing that approach.

## Node
A Node contains : 

| Fields | Description |
|--------|-------------|
| Node *left | Pointer to the left child |
| int leftHeight | Height of the left subtree |
| int value | Value of the Node |
| int rightHeight | Height of the right subtree |
| int balance | Balance of the Node |
| Node *right | Pointer to the right child |

## Addition of a Node 
Each time a new Node is added in the Tree,
the heights and balance of the current Node
are updated.

```c++
// If the left child exists
if (currentNode->left)
{
    // Increment the greater of left child's heights by 1 and assign to 
    // current Node's leftHeight
    currentNode->leftHeight = (currentNode->left->leftHeight > currentNode->left->rightHeight) ? currentNode->left->leftHeight + 1 : currentNode->left->rightHeight + 1;
}

// If the right child exists
if (currentNode->right)
{
    // Increment the greater of right child's heights by 1 and assign to
    // current Node's rightHeight
    currentNode->rightHeight = (currentNode->right->leftHeight > currentNode->right->rightHeight) ? currentNode->right->leftHeight + 1 : currentNode->right->rightHeight + 1;
}

// Update the current Node's balance
currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;
```

## Balancing of the Tree
If the balance of the current Node is -2 or +2,
rebalance the Tree.

```c++
// If the currentNode's balance is -2 or +2
if (+2 == currentNode->balance || -2 == currentNode->balance)
{
    // Return the Node returned by rebalancing the Tree
    return rebalance(currentNode);
}
```

## Removal of a Node
Each time a Node is deleted from the Tree,
the heights and balance of its parent Node
are updated and rebalancing is performed (if needed).

```c++
// If the Left Child has been deleted and returned nullptr
if (!currentNode->left)
{
    // Set the currentNode's leftHeight to 0
    currentNode->leftHeight = 0;
}

// If the Right Child has been deleted and returned nullptr
if (!currentNode->right)
{
    // Set the currentNode's rightHeight to 0
    currentNode->rightHeight = 0;
}

// If both the children exist, simply update the current Node's
// heights
if (currentNode->left && currentNode->right)
{
    // Increment the greater of left child's heights by 1 and assign 
    // to current Node's leftHeight
    currentNode->leftheight = (currentNode->left->leftHeight > currentNode->left->rightHeight) ? currentNode->left->leftHeight + 1 : currentNode->left->rightheight + 1;

    // Increment the greater of right child's heights by 1 and assign 
    // to current Node's rightHeight
    currentNode->rightHeight = (currentNode->right->leftHeight > currentNode->right->rightHeight) ? currentNode->right->leftHeight + 1 : currentNode->right->rightHeight + 1;
}

// Update the current Node's balance
currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;
```

## Left Rotation (Right Rotation will follow same steps)
Heights and balance of the current Node and 
it's child are updated during the rotation.

```c++
// Function to perform Left Rotation
Node *rotateLeft(Node *currentNode)
{
    // Current Node's child
    Node *child = currentNode->right;

    // Pass the child's left to current Node's right
    currentNode->right = child->left;

    // Right Height of the current Node is now same
    // as the child's left
    currentNode->rightHeight = child->leftHeight;

    // Update the currentNode's balance
    currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;

    // Make the currentNode as child's left child
    child->left = currentNode;

    // Increment the greater of current Node's heights by 1 and assign
    // to child's leftHeight
    child->leftHeight = (currentNode->leftHeight > currentNode->rightHeight) ? currentNode->leftHeight + 1 : currentNode->rightHeight + 1;

    // Update the child's balance
    child->balance = child->rightHeight - child->leftHeight;

    // Return child
    return child;
}
```

## Remarks 
Any input or improvement to the above code is deeply appreciated.
