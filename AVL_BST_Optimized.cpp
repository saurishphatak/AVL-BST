/*
 * --------------------------------------------------------------------------------
 * File :         AVL_BST_Optimized.cpp
 * Project :      AVL-BST-Optimized
 * Author :       Saurish 
 * 
 * 
 * Description : Attempt at Optimizing the AVL-BST. 
 * --------------------------------------------------------------------------------
 * 
 * Revision History : 
 * 2020-April-25	[SP] : Created
 * --------------------------------------------------------------------------------
 * Copyright (c) 2020 Saurish Phatak
 * 
 * License : 
 * 
 *    This code is meant for learning.
 *    Do NOT Copy Paste it as it may not help in understanding the code.
 *    You are required to understand and type it yourself.
 * 
 * DISCLAIMER : 
 *    This code may contain unintentional and intentional bugs.
 *    There are no guarantees of this code working properly.
 * --------------------------------------------------------------------------------
 */

#include <iostream>

using namespace std;

// Define Node
struct Node
{
    /**
     * Fields :
     * 
     * left : points to the left child of the current node
     * leftHeight : stores the left height of the current node
     * value : stores the value of the node
     * rightHeight : stores the right height of the current node
     * balance : stores the balance of the current node
     * right : points to the right child of the current node
     */
    Node *left;
    int leftHeight;
    int value;
    int rightHeight;
    int balance;
    Node *right;

    // Parameterized Constructor
    Node(int value)
    {
        left = nullptr;
        leftHeight = 0;
        this->value = value;
        rightHeight = 0;
        balance = 0;
        right = nullptr;
    }
};

// Define class Tree
class Tree
{
    /**
     * Fields : 
     * 
     * root : points to the root of the Tree
     */
    // Pointer to the root of the Node
    Node *root;

    /**
     * Methods : 
     * 
     * addNode : adds a Node in the Tree using recursion
     * rebalance : rebalances the Tree
     * inorderTraversal : prints the values in Tree in Ascending Order
     * rotateLL : performs left rotation
     * rotateRR : performs right rotation
     * print : prints the Tree in visual Form
     * removeFromTree : removes Node with given value from the Tree
     * removeAll : removes all Nodes from the Tree
     */
    // Function to add a Node in the Tree
    Node *addNode(Node *currentNode, int value)
    {
        // If the currentNode is nullptr
        if (!currentNode)
            return new Node(value);

        // If the value is greater than
        // the currentNode's value
        if (value > currentNode->value)
            currentNode->right = addNode(currentNode->right, value);

        // If the value is less than
        // or equal to the currentNode's value
        else
            currentNode->left = addNode(currentNode->left, value);

        // Update the currentNode's heights
        // If the left child exists
        if (currentNode->left)
            currentNode->leftHeight = (currentNode->left->leftHeight > currentNode->left->rightHeight) ? currentNode->left->leftHeight + 1 : currentNode->left->rightHeight + 1;

        // If the right child exists
        if (currentNode->right)
            currentNode->rightHeight = (currentNode->right->leftHeight > currentNode->right->rightHeight) ? currentNode->right->leftHeight + 1 : currentNode->right->rightHeight + 1;

        // Update the currentNode's balances
        currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;

        // Check if rebalance operation needs to be performed
        if (2 == currentNode->balance || -2 == currentNode->balance)
            return rebalance(currentNode);

        return currentNode;
    }

    // Function to perform Rebalance operation
    Node *rebalance(Node *currentNode)
    {
        // If the currentNode's balance == +2
        if (2 == currentNode->balance)
        {
            // If the currentNode's right child's balance == +1
            if (1 == currentNode->right->balance)
            {
                // Perform LL rotation
                return rotateLeft(currentNode);
            }

            // Else, perform RR rotation first and then
            // LL rotation
            else
            {
                currentNode->right = rotateRight(currentNode->right);
                return rotateLeft(currentNode);
            }
        }

        // If the currentNode's balance == -2
        else
        {
            // If the left child's balance is -1
            if (-1 == currentNode->left->balance)
            {
                // Perform RR rotation
                return rotateRight(currentNode);
            }

            // Else, first perform LL rotation
            // and then LL rotation
            else
            {
                currentNode->left = rotateLeft(currentNode->left);
                return rotateRight(currentNode);
            }
        }
    }

    // Function to print the Tree by Inorder Traversal
    void inorderTraversal(Node *currentNode)
    {
        // If the currentNode is nullptr
        if (!currentNode)
            return;

        inorderTraversal(currentNode->left);
        cout << currentNode->value << endl;
        inorderTraversal(currentNode->right);
    }

    // Function to perform LL Rotation
    Node *rotateLeft(Node *currentNode)
    {
        // Point to the right child of the
        // currentNode
        Node *child = currentNode->right;

        // Pass the child's left to currentNode's
        // right
        currentNode->right = child->left;

        // Update the currentNode's right height and balance
        currentNode->rightHeight = child->leftHeight;
        currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;

        // Make the currentNode as the child's left
        child->left = currentNode;

        // Update the child's left height and balance
        child->leftHeight = (currentNode->leftHeight > currentNode->rightHeight) ? currentNode->leftHeight + 1 : currentNode->rightHeight + 1;
        child->balance = child->rightHeight - child->leftHeight;

        // Finally, return the child
        return child;
    }

    // Function to perform RR Rotation
    Node *rotateRight(Node *currentNode)
    {
        // Point to the currentNode's left child
        Node *child = currentNode->left;

        // Pass the child's right to currentNode's left
        currentNode->left = child->right;

        // Update the currentNode's left height and balance
        currentNode->leftHeight = child->rightHeight;
        currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;

        // Point the child's right to currentNode
        child->right = currentNode;

        // Update the child's right height and balance
        child->rightHeight = (currentNode->leftHeight > currentNode->rightHeight) ? currentNode->leftHeight + 1 : currentNode->rightHeight + 1;
        child->balance = child->rightHeight - child->leftHeight;

        // Finally, return child
        return child;
    }

    // Function to print the Tree
    void print(Node *currentNode)
    {
        // If the currentNode is null
        if (!currentNode)
            return;

        // Define a static level
        static int level = -1;

        // The currentNode is not null
        // Increment the level and go down
        level++;

        // Go to the currentNode's right
        print(currentNode->right);

        // Print spaces to represent the levels
        for (int i = 0; i < level; i++)
            cout << "   ";

        // Print the value of the currentNode
        cout << currentNode->value << endl;

        // Go to the currentNode's left
        print(currentNode->left);

        // Decrement level while going up the Tree
        level--;
    }

    // Function to remove a value from the
    // the Tree
    Node *removeFromTree(Node *currentNode, int value)
    {
        // If the currentNode is null
        if (!currentNode)
            return currentNode;

        // If the value is greater than the currentNode's
        // value
        if (value > currentNode->value)
            currentNode->right = removeFromTree(currentNode->right, value);

        // If the value is less than the currentNode's
        // value
        if (value < currentNode->value)
            currentNode->left = removeFromTree(currentNode->left, value);

        // If the value is found
        if (value == currentNode->value)
        {
            // If this currentNode has no children
            if (!currentNode->left && !currentNode->right)
            {
                delete currentNode;
                return nullptr;
            }

            // If there is ONLY left child
            if (currentNode->left && !currentNode->right)
            {
                Node *child = currentNode->left;
                delete currentNode;
                return child;
            }

            // If there is ONLY right child
            if (!currentNode->left && currentNode->right)
            {
                Node *child = currentNode->right;
                delete currentNode;
                return child;
            }

            // If there are both children
            if (currentNode->left && currentNode->right)
            {
                // Find the predecessor
                Node *predecessor = currentNode->left;

                while (predecessor->right)
                    predecessor = predecessor->right;

                // Copy the predecessor's value to currentNode
                currentNode->value = predecessor->value;

                // Delete the duplicate predecessor value
                currentNode->left = removeFromTree(currentNode->left, predecessor->value);
            }
        }

        // If the left or right child is null
        // Update the respective height to 0
        if (!currentNode->left)
            currentNode->leftHeight = 0;

        if (!currentNode->right)
            currentNode->rightHeight = 0;

        // If both children exist
        if (currentNode->left && currentNode->right)
        {
            // Update the currentNode's height
            currentNode->leftHeight = (currentNode->left->leftHeight > currentNode->left->rightHeight) ? currentNode->left->leftHeight + 1 : currentNode->left->rightHeight + 1;
            currentNode->rightHeight = (currentNode->right->leftHeight > currentNode->right->rightHeight) ? currentNode->right->leftHeight + 1 : currentNode->right->rightHeight + 1;
        }

        // Update the currentNode's balance
        currentNode->balance = currentNode->rightHeight - currentNode->leftHeight;

        // If rebalancing is required
        if (2 == currentNode->balance || -2 == currentNode->balance)
            return rebalance(currentNode);

        // Return currentNode
        return currentNode;
    }

    // Function to remove all the values from the Tree
    Node *removeAll(Node *currentNode)
    {
        // If the currentNode is null
        if (!currentNode)
            return currentNode;

        // If the currentNode is not null
        // Go to the left of the currentNode
        currentNode->left = removeAll(currentNode->left);

        // Go to the right of the currentNode
        currentNode->right = removeAll(currentNode->right);

        // Finally, delete the currentNode
        delete currentNode;

        // Return nullptr
        return nullptr;
    }

public:
    // Parameterized Constructor
    Tree()
    {
        this->root = nullptr;
    }

    /**
     * Methods : 
     * 
     * add : wrapper function for addNode
     * printTree : wrapper function for print
     * remove : wrapper function for removeFromTree
     * clear : wrapper function for removeAll
     */
    // Wrapper Function to add a Node
    // in the Tree
    void add(int value)
    {
        this->root = addNode(root, value);
    }

    // Wrapper Function to print the Tree
    // in Visual Form
    void printTree()
    {
        print(root);
    }

    // Wrapper Function to remove a value
    // from the Tree
    void remove(int value)
    {
        root = removeFromTree(root, value);
    }

    // Wrapper Function to remove all
    // values from the Tree
    void clear()
    {
        root = removeAll(root);
    }

    // Destructor
    ~Tree()
    {
        // Call the removeAll function
        root = removeAll(root);
    }
};

int main()
{
    // Create an object of Tree
    Tree ped;

    int value;
    // Add some values to the Tree
    while (cout << "Enter value to add (0 to stop) : ",
           cin >> value,
           value)
    {
        ped.add(value);

        // Print the tree in Visual Form
        ped.printTree();
    }

    cout << "Enter value to remove :";
    cin >> value;
    ped.remove(value);

    // Print the Tree after removal of value
    ped.printTree();

    return 0;
}