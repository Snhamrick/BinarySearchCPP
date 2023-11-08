//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Seth Hamrick
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    Node* removeNode(Node* node, string bidId);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr; 
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    delete root->left;
    delete root->right;
    


    
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    inOrder(root);                                  //pass root through inOrder function
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);                                //pass root through postOrder function
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    postOrder(root);                                 //pass root through preOrder function
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {                          //if root is equal to null (tree is empty) 
        root = new Node(bid);                           //root is equal to new Node with Bid to be inserted
        root->left = nullptr;                           //roots left and right are nullptrs (only one item in tree)
        root->right == nullptr;
    }
    else {                                          //else tree is not empty
        addNode(root, bid);                             //call function to addNode
    }
}

/**
 * Remove a bid
 */

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    Node* parent = nullptr;                                         //pointer for parent node
    Node* suc = nullptr;                                            //pointer for successor node
    while (node != nullptr) {                                       //while node is not null
        if (node->bid.bidId == bidId) {                                 //if node's bidId matches bidId
            if (node->left == nullptr && node->right == nullptr) {          //if node to be removed has no children
                if (parent == nullptr) {                                        //if parent is null (node is root)
                    root == nullptr;                                                //remove root
                }       
                else if (parent->left == node) {                                //else if node is child on left
                    parent->left = nullptr;                                         //remove node
                }
                else {                                                          //else node is child on right
                    parent->right = nullptr;                                        //remove node
                }
            }
            else if (node->right == nullptr) {                              //else if node to be removed only has child on left
                if (parent == nullptr) {                                        //if parent is null (node is root)
                    root = node->left;                                              //root becomes left child
                }
                else if (parent->left == node) {                                //else if node is child on left
                    parent->left = node->left;                                      //parent's left now becomes node's left
                }
                else {                                                          //else node is child on right
                    parent->right = node->left;                                     //parent's right becomes child's left
                }
            }
            else if (node->left == nullptr) {                               //else if node to be removed only has child on right
                if (parent == nullptr) {                                        //if parent is null (node is root)
                    root = node->right;                                             //root becomes right child
                }
                else if (parent->left == node) {                                //else if node is child on left
                    parent->left = node->right;                                     //parents left now becomes child's right
                }
                else {                                                          //else node is child on right
                    parent->right = node->right;                                    //parents right becomes child's right
                }
            }
            else {                                                          //else node has two children must find successor
                suc = node->right;                                              //set successor equal to node's right child to search right subtree
                while (suc->left != nullptr) {                                  //while successors left is not null
                    suc = suc->left;                                                // successor moves to left (traverse to left most node of right subtree)
                }
                Bid sucBid = suc->bid;                                          //Create copy of successors data
                removeNode(suc, suc->bid.bidId);                                //remove successor
                node->bid = sucBid;                                             //asign node with successors data
            }
            return node;                                                    //return node
        }
        else if (node->bid.bidId < bidId) {                             //else if node's bidId is less than bidId
            parent = node;                                                  //parent becomes node
            node = node->right;                                             //node moves to the right
        }
        else {                                                          //else node's bidId is greater than bidId
            parent = node;                                                  //parent becomes node
            node = node->left;                                              //node moves to left
        }
    }
    return node;                                                   //return node





}

void BinarySearchTree::Remove(string bidId) {
    removeNode(root, bidId);                        //pass root and biId through removeNode function
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    Bid empty;                                   //create empty node
    Node* current = root;                                       //create node pointer named current set equal to root
    while (current != nullptr) {                                //while current is not null
        if (current->bid.bidId == bidId) {                      //if current's bidId is the search bidId 
            return current->bid;                                    //return current bid
        }
        else if (current->bid.bidId < bidId) {                  //else if current bidId is less than search bidId
            current = current->right;                               //move to the right in the tree
        }
        else {                                                  //else current bidId is greater than search bidId
            current = current->left;                                //move to the left in the tree
        }
    }
    return empty;                                          //if a nullptr is reached then the bid is not to be found return empty bid
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (bid.bidId < node->bid.bidId) {                          //if bidId is less than node's bidId
        if (node->left == nullptr) {                                //if node's left child is null
            node->left = new Node(bid);                                 //node's left child is equal to new Node with bid
        }
        else {                                                  //else node's left child is occupied
            addNode(node->left, bid);                               //recursively add bid to node's left child
        }
    }
    else {                                                      //else bidId is greater than node's bidId
        if (node->right == nullptr) {                               //if node's right child is null
            node->right = new Node(bid);                                //node;s right child is equal to new Node with bid
        }
        else {                                                  //else node's right child is occupied
            addNode(node->right, bid);                              //recursively add bid to node's left child
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {                                //if node is not equal to null
        inOrder(node->left);                              //recurse down left
        /*OUTPUT node data*/
        cout << node->bid.bidId << " " << node->bid.title << " " << node->bid.amount << " " << node->bid.fund << endl;
        inOrder(node->right);                             //recurse down right
    }
}
void BinarySearchTree::postOrder(Node* node) {
    if (node != nullptr) {                                 //if node is not equal to null
        postOrder(node->left);                             //recurse down left
        postOrder(node->right);                            //recurse down right
        /*OUTPUT node data*/
        cout << node->bid.bidId << " " << node->bid.title << " " << node->bid.amount << " " << node->bid.fund << endl;
      }


}

void BinarySearchTree::preOrder(Node* node) {
    if (node != nullptr) {                                 //if node is not equal to null
        /*OUTPUT node data*/
        cout << node->bid.bidId << " " << node->bid.title << " " << node->bid.amount << " " << node->bid.fund << endl;
        preOrder(node->left);                              //recurse down left
        preOrder(node->right);                              //recurse down right
    } 
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98385";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
