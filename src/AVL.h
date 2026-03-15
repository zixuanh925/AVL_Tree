#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    std::string name;
    std::string ufid;
    Node *left, *right;
    int height;

    Node(std::string n, std::string id)
        : name(n), ufid(id), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    // Helper functions for balancing
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    // Recursive helpers
    Node* insert(Node* node, std::string name, std::string id, bool& success);
    Node* remove(Node* node, std::string id, bool& success);
    Node* getInorderSuccessor(Node* node);

    void getInorder(Node* node, std::vector<Node*>& nodes);
    void getPreorder(Node* node, std::vector<std::string>& names);
    void getPostorder(Node* node, std::vector<std::string>& names);
    void searchName(Node* node, std::string name, std::vector<std::string>& ids);

public:
    AVLTree() : root(nullptr) {}
    void insert(std::string name, std::string id);
    void remove(std::string id);
    void searchID(std::string id);
    void searchName(std::string name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int n);
};

/*
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
*/