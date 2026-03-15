#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Node {
    string name;
    int id;
    int height;
    Node* left;
    Node* right;

    Node(const string& n, const int i) : name(n), id(i), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
    Node* root = nullptr;
    bool lastOpSuccess;

    //helper functions
    static int getHeight(const Node* node);
    static int getBalanceFactor(const Node* node);
    static Node* rotateLeft(Node* node);
    static Node* rotateRight(Node* node);
    static Node* rotateLeftRight(Node* node);
    static Node* rotateRightLeft(Node* node);

    Node* insert(Node* node, string name, int id, bool& success);
    Node* remove(Node* node, int id, bool& success);
    static Node* getInorderSuccessor(Node* node);

    static void searchID(Node* node, int id, bool& found);
    static void searchName(Node* node, string name, vector<int>& results);

    void inorder(Node* node, vector<string>& names);
    void preorder(Node* node, vector<string>& names);
    void postorder(Node* node, vector<string>& names);
    void getInorderNodes(Node* node, vector<Node*>& nodes);

public:
    AVL() : root(nullptr), lastOpSuccess(false) {}
    bool wasLastOpSuccessful() const { return lastOpSuccess; }

    //insert functions
    Node* insert(string name, int id);
    Node* remove(int id);

    //traversal functions
    void printInorder();
    void printPreorder();
    void printPostorder();

    //search functions
    void searchID(int id);
    void searchName(string name);

    //level and Nth removal
    void printLevelCount();
    void removeInorder(int n);

    //getter functions
    vector<string> getInorder();
    vector<string> getPreorder();
};
