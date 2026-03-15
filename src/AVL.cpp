#include "AVL.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


int AVLTree::getHeight(Node* node) { return node ? node->height : 0; }

int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* AVLTree::insert(Node* node, std::string name, std::string id, bool& success) {
    if (!node) { success = true; return new Node(name, id); }
    if (id < node->ufid) node->left = insert(node->left, name, id, success);
    else if (id > node->ufid) node->right = insert(node->right, name, id, success);
    else { success = false; return node; }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && id < node->left->ufid) return rotateRight(node);
    if (balance < -1 && id > node->right->ufid) return rotateLeft(node);
    if (balance > 1 && id > node->left->ufid) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && id < node->right->ufid) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* AVLTree::getInorderSuccessor(Node* node) {
    Node* current = node;
    while (current && current->left) current = current->left;
    return current;
}

Node* AVLTree::remove(Node* node, std::string id, bool& success) {
    if (!node) return nullptr;
    if (id < node->ufid) node->left = remove(node->left, id, success);
    else if (id > node->ufid) node->right = remove(node->right, id, success);
    else {
        success = true;
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Node* temp = getInorderSuccessor(node->right);
        node->name = temp->name;
        node->ufid = temp->ufid;
        node->right = remove(node->right, temp->ufid, success);
    }
    return node;
}

// Helper for Traversals
void AVLTree::getInorder(Node* node, std::vector<Node*>& nodes) {
    if (!node) return;
    getInorder(node->left, nodes);
    nodes.push_back(node);
    getInorder(node->right, nodes);
}

void AVLTree::insert(std::string name, std::string id) {
    bool success = false;
    root = insert(root, name, id, success);
    std::cout << (success ? "successful" : "unsuccessful") << std::endl;
}

void AVLTree::remove(std::string id) {
    bool success = false;
    root = remove(root, id, success);
    std::cout << (success ? "successful" : "unsuccessful") << std::endl;
}

void AVLTree::removeInorder(int n) {
    std::vector<Node*> nodes;
    getInorder(root, nodes);
    if (n >= 0 && n < nodes.size()) remove(nodes[n]->ufid);
    else std::cout << "unsuccessful" << std::endl;
}

void AVLTree::printLevelCount() {
    std::cout << getHeight(root) << std::endl;
}

// ... (Implement other traversals and searchName similarly using recursion)
// ... Additional traversal logic (Inorder, Preorder, Postorder) implemented similarly
/*
int AVL::getHeight(const Node* node)
{
    return node ? node->height : 0;
}

int AVL::getBalanceFactor(const Node* node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* AVL::rotateLeft(Node* node)
{
    Node* center = node->right;
    Node* x = center->left;

    center->left = node;
    node->right = x;

    node->height = 1 + (max(getHeight(node->right), getHeight(node->left)));
    center->height = 1 + (max(getHeight(center->left), getHeight(center->right)));
    return center;
}

Node* AVL::rotateRight(Node* node)
{
    Node* center = node->left;
    Node* x = center->right;

    center->right = node;
    node->left = x;

    node->height = 1 + (max(getHeight(node->right), getHeight(node->left)));
    center->height = 1 + (max(getHeight(center->left), getHeight(center->right)));
    return center;
}

Node* AVL::rotateLeftRight(Node* node)
{
    //rotate the left child to the left
    node->left = rotateLeft(node->left);
    //rotate the current node to the right
    return rotateRight(node);
}

Node* AVL::rotateRightLeft(Node* node)
{
    //rotate the right child to the right
    node->right = rotateRight(node->right);
    //rotate the current node to the left
    return rotateLeft(node);
    }

Node* AVL::insert(Node* node, string name, int id, bool& success)
{
    success = false;
    lastOpSuccess = success;

    if (node == nullptr)
    {
        success = true;
        return new Node(name, id);
    }

    if (id < node->id)
        node->left = insert(node->left, name, id, success);
    else if (id > node->id)
        node->right = insert(node->right, name, id, success);
    else
    {
        success = false; //ID exists already
        return node;
    }

    node->height = 1+ max(getHeight(node->right), getHeight(node->left));

    //check balance
    const int balance = getBalanceFactor(node);

    //left heavy
    if (balance > 1)
    {
        if (id < node->left->id) return rotateRight(node);
        if (id > node->right->id) return rotateLeftRight(node);
    }

    //right heavy
    if (balance < -1)
    {
        if (id > node->right->id) return rotateLeft(node);
        if (id < node->left->id) return rotateRightLeft(node);
    }

    return node;
}

Node* AVL::getInorderSuccessor(Node* node)
{
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

Node* AVL::remove(Node* node, int id, bool& success)
{
    if (node == nullptr)
    {
        success = false; // ID not found
        return nullptr;
    }

    if (id < node->id)
        node->left = remove(node->left, id, success);
    else if (id > node->id)
        node->right = remove(node->right, id, success);
    else {
        success = true;

        //one child or no child
        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            return temp; // Return the right child
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            return temp; // Return the left child
        }

        //two children
        Node* temp = getInorderSuccessor(node);
        node->name = temp->name;
        node->id = temp->id;

        bool internalSuccess = false;
        node->right = remove(node->right, temp->id, internalSuccess);
    }

    if (node != nullptr) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    return node;
}

void AVL::searchID(Node* node, int id, bool& found)
{
    if (node == nullptr) return;

    if (id == node->id) {
        cout << node->name << endl;
        found = true;
    } else if (id < node->id) {
        searchID(node->left, id, found);
    } else {
        searchID(node->right, id, found);
    }
}

void AVL::searchName(Node* node, string name, vector<int>& results)
{
    if (node == nullptr) return;

    //preorder traversal
    if (node->name == name) {
        results.push_back(node->id);
    }
    searchName(node->left, name, results);
    searchName(node->right, name, results);
}

void AVL::inorder(Node* node, vector<string>& names)
{
    if (node == nullptr) return;
    inorder(node->left, names);
    names.push_back(node->name);
    inorder(node->right, names);
}

void AVL::preorder(Node* node, vector<string>& names)
{
    if (node == nullptr) return;
    names.push_back(node->name);
    preorder(node->left, names);
    preorder(node->right, names);
}

void AVL::postorder(Node* node, vector<string>& names)
{
    if (node == nullptr) return;
    postorder(node->left, names);
    postorder(node->right, names);
    names.push_back(node->name);
}

void AVL::getInorderNodes(Node* node, vector<Node*>& nodes)
{
    if (node == nullptr) {
        return;
    }
    getInorderNodes(node->left, nodes);
    nodes.push_back(node);
    getInorderNodes(node->right, nodes);
}

Node* AVL::insert(string name, int id)
{
    bool success = false;
    root = insert(root, name, id, success);
    lastOpSuccess = success;

    if (success) cout << "successful" << endl;
    else cout << "unsuccessful" << endl;

    return root;
}

Node* AVL::remove(int id)
{
    bool success = false;
    root = remove(root, id, success);
    lastOpSuccess = success;

    if (success) cout << "successful" << endl;
    else cout << "unsuccessful" << endl;

    return root;
}

vector<string> AVL::getInorder()
{
    vector<string> names;
    inorder(root, names);
    return names;
}

vector<string> AVL::getPreorder()
{
    vector<string> names;
    preorder(root, names);
    return names;
}
*/