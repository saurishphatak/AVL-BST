/*
 * --------------------------------------------------------------------------------
 * File :         AVL_BST_Traditional.cpp
 * Project :      AVL-BST-Optimized
 * Author :       Saurish 
 * 
 * 
 * Description : Traditional AVL-BST implementation. 
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

// Define a Node
struct Node
{
    // Fields
    Node *left;
    int value;
    Node *right;

    // Parameterisesd Constructor
    Node(int valueToAdd)
    {
        left = nullptr;
        value = valueToAdd;
        right = nullptr;
    }
};

// Define a Tree class
class Tree
{
    // Fields
    Node *root;

    /*
     * Operations:
     * 
     * addNode : Add a Node in the Tree
     * getBalance : Calculates the balance of the currentNode
     * getHeight : Calculates the height of the currentNode
     * rotateLeft : Performs Left Rotation
     * rotateRight : Performs Right Rotation
     * rebalance : Balances the Tree
     * removeNode : Removes a Node from the Tree
     * removeAll : Removes all Nodes from the Tree
     * printTree : Prints the Tree
     * printInorder : Prints the values in Ascending Order
     */
    // Function to add a Node in Tree
    Node *addNode(Node *currentNode, int valueToAdd)
    {
        // Check if the given Node is nullptr
        if (!currentNode)
        {
            // Create a newNode
            Node *newNode = new Node(valueToAdd);

            // Check for successful allocation
            if (!newNode)
                return newNode;

            // Return newNode
            return newNode;
        }

        // Check if the given value is greater than currentNode's
        // value
        if (currentNode->value < valueToAdd)
        {
            // Call the addNode function with currentNode->right
            // as the arguement
            currentNode->right = addNode(currentNode->right, valueToAdd);
        }

        // The given value is less than or equal to the currentNode's
        // value
        if (currentNode->value > valueToAdd)
        {
            // Call the addNode function with currentNode->left as the
            // arguemnent
            currentNode->left = addNode(currentNode->left, valueToAdd);
        }

        // Call the rebalance function with currentNode
        // as the arguement and return
        // the address of the Node returned by the
        // rebalance function
        // return rebalance(currentNode);
        return rebalance(currentNode);
    }

    // Function to get the balance of the currentNode
    int getBalance(Node *currentNode)
    {
        // Define leftHeightOfNode and rightHeightofNode
        int leftHeightOfNode = getHeight(currentNode->left);
        int rightHeightOfNode = getHeight(currentNode->right);

        // Define balance
        int balance = rightHeightOfNode - leftHeightOfNode;

        // Return balance
        return balance;
    }

    // Function to get height of the currentNode
    int getHeight(Node *currentNode)
    {
        // Check if the Node is nullptr
        if (!currentNode)
            return 0;

        // Find the Left Height
        int leftHeight = getHeight(currentNode->left);

        // Find the Right Height
        int rightHeight = getHeight(currentNode->right);

        // Increment and return the greater of the 2 heights
        if (leftHeight < rightHeight)
            return ++rightHeight;

        else
            return ++leftHeight;
    }

    // Function to perform Left Rotation
    Node *rotateLeft(Node *currentNode)
    {
        // Define the Child Node
        Node *childNode = currentNode->right;

        // Pass the childNode's left child to the currentNode
        currentNode->right = childNode->left;

        // Now, childNode's left is free
        // Assign it currentNode
        childNode->left = currentNode;

        // Finally return childNode
        return childNode;
    }

    // Function to perform Right Rotation
    Node *rotateRight(Node *currentNode)
    {
        // Define the Child Node
        Node *childNode = currentNode->left;

        // Pass the childNode's Left Child to the currentNode
        currentNode->left = childNode->right;

        // Now that the childNode's left is free
        // Assign it the currentNode
        childNode->right = currentNode;

        // Return the childNode
        return childNode;
    }

    // Function to Rebalance the Tree
    Node *rebalance(Node *currentNode)
    {
        // Find the balance of the currentNode
        int balanceOfTheCurrentNode = getBalance(currentNode);

        // If the balance of the currentNode is not +2 or -2
        // simply return the currentNode
        if (2 != balanceOfTheCurrentNode && -2 != balanceOfTheCurrentNode)
            return currentNode;

        // Check if the balance of the currentNode is +2
        if (2 == balanceOfTheCurrentNode)
        {
            // Find the balance of the child
            int childBalance = getBalance(currentNode->right);

            // Check if the balance of the child is +1
            if (1 == childBalance)
            {
                // Call the rotateLeft function and return
                // the address of the Node returned by the
                // rotateLeft function
                return rotateLeft(currentNode);
            }

            // If the balance of the child is not +1
            else
            {
                // Call the rotateRight function with
                // currentNode->right as the arguement
                // Capture the address of the Node returned
                // in currentNode->right
                currentNode->right = rotateRight(currentNode->right);

                // Now call the rotateLeft function and pass
                // the currentNode as the arguement
                // Return whatever the rotateLeft function
                // returns
                return rotateLeft(currentNode);
            }
        }

        // Check if the balance of the currentNode is -2
        if (-2 == balanceOfTheCurrentNode)
        {
            // Find the balance of the currentNode's Left Child
            int childBalance = getBalance(currentNode->left);

            // Check if the childBalance is -1
            if (-1 == childBalance)
            {
                // Call the rotateRight function with
                // currentNode as the arguement
                // Return the address returned by the
                // rotateRight function
                return rotateRight(currentNode);
            }

            // If the childBalance is not -1
            else
            {
                // Call the rotateLeft function with
                // currentNode->left as the arguement
                // Capture the address returned by the rotateLeft
                // function in currentNode->left
                currentNode->left = rotateLeft(currentNode->left);

                // Now, call the rotateRight function with
                // currentNode as the arguement
                // Return the address returned by the
                // rotateRight function
                return rotateRight(currentNode);
            }
        }
    }

    // Function to remove a Node from the Tree
    Node *removeNode(Node *currentNode, int value)
    {
        // If the currentNode is null
        if (!currentNode)
            return currentNode;

        // If the value is greater than the currentNode's
        // value, go to left subtree
        if (value > currentNode->value)
            currentNode->right = removeNode(currentNode->right, value);

        // If the value is lesser than the currentNode's
        // value, go to the right subtree
        if (value < currentNode->value)
            currentNode->left = removeNode(currentNode->left, value);

        // If the value is found
        if (value == currentNode->value)
        {
            // If the currentNode has NO children
            if (!currentNode->left && !currentNode->right)
            {
                // Delete the currentNode
                delete currentNode;

                // Return nullptr
                return nullptr;
            }

            // If the currentNode has ONLY Left child
            if (currentNode->left && !currentNode->right)
            {
                // Capture the left child
                Node *child = currentNode->left;

                // Delete the currentNode
                delete currentNode;

                // Return child
                return child;
            }

            // If the currentNode has ONLY Right child
            if (!currentNode->left && currentNode->right)
            {
                // Capture the right child
                Node *child = currentNode->right;

                // Delete the currentNode
                delete currentNode;

                // Return the child
                return child;
            }

            // If BOTH children exist
            if (currentNode->left && currentNode->right)
            {
                // Find the predecessor of the currentNode
                Node *predecessor = currentNode->left;

                while (predecessor->right)
                    predecessor = predecessor->right;

                // Copy the predecessor's value to currentNode
                currentNode->value = predecessor->value;

                // Delete the duplicate predecessor value
                currentNode->left = removeNode(currentNode->left, predecessor->value);
            }
        }

        // Rebalance the Tree and return the Node
        // returned by rebalance function
        return rebalance(currentNode);
    }

    // Function to remove all Nodes from the Tree
    Node *removeAll(Node *currentNode)
    {
        // If the currentNode is null
        if (!currentNode)
            return currentNode;

        // Go to the left subtree
        currentNode->left = removeAll(currentNode->left);

        // Go to the right subtree
        currentNode->right = removeAll(currentNode->right);

        // Finally, delete the currentNode
        delete currentNode;

        // Return nullptr
        return nullptr;
    }

    // Function to print the Tree
    void printTree(Node *currentNode)
    {
        // Keep a track of how many levels of the Tree
        // have been traversed
        static int level = -1;

        // Check if the Node is null
        if (!currentNode)
            return;

        // Increment the levels everytime
        // you go down the Tree
        level++;

        // Recursively call the printTree function
        // until the rightMost Node is reached
        printTree(currentNode->right);

        // Since the Tree will be printed sideways
        // print 4 spaces for each level
        for (int i = 0; i < level; i++)
            cout << "\t";

        // Print the currentNode's value
        // along with a newline character
        // which will act as a space between the
        // right and left Nodes
        cout << currentNode->value << endl;

        // Recursively call the printTree function
        // and go to the Left of the currentNode
        printTree(currentNode->left);

        // Decrement the levels everytime
        // you go up the Tree
        level--;
    }

    // Functin to print the Tree in Ascending Order
    void printInorder(Node *currentNode)
    {
        // If currentNode is null
        if (!currentNode)
            return;

        // Go to the currentNode's left
        printInorder(currentNode->left);

        // Print the currentNode's value
        cout << currentNode->value << endl;

        // Go to the currentNode's right
        printInorder(currentNode->right);
    }

public:
    // Default constructor
    Tree()
    {
        // Set the root to nullptr
        root = nullptr;
    }

    // Data Abstractor Wrapper Function for addNode
    void add(int valueToAdd)
    {
        // Call the addNode function
        this->root = addNode(root, valueToAdd);
    }

    // Data Abstractor Wrapper Function for printTree
    void print()
    {
        // Call the printTree function
        printTree(root);
    }

    // Data Abstractor Wrapper Function for removeNode
    void remove(int value)
    {
        // Call the removeNode function
        root = removeNode(root, value);
    }

    // Data Abstractor Wrapper Function for removeAll
    void clear()
    {
        // Call the removeAll function
        root = removeAll(root);
    }

    // Data Abstractor Wrapper Function for printInorder
    void printAscending()
    {
        // Call the printInorder function
        printInorder(root);
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

    srand(time(0));

    // Add some values to the Tree
    int value;
    while (cout << "Enter value (0 to stop) : ",
           cin >> value,
           value)
    {
        ped.add(value);

        // Print the Tree in Visual Form
        ped.print();
    }

    cout << "Enter value to be deleted : ";
    cin >> value;

    // Remove the given value
    ped.remove(value);

    // Print the Tree in Visual Form
    ped.print();

    return 0;
}
