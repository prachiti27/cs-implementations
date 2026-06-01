#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    Node* insert(Node* node, int val) {
        if (node == nullptr)
            return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);

        return node;
    }

    bool search(Node* node, int key) {
        if (node == nullptr)
            return false;

        if (node->data == key)
            return true;

        if (key < node->data)
            return search(node->left, key);

        return search(node->right, key);
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->data) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->data) {
            node->right = deleteNode(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* successor = findMin(node->right);

            node->data = successor->data;

            node->right = deleteNode(node->right, successor->data);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }
};

int main() {
    BST tree;

    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int val : values)
        tree.root = tree.insert(tree.root, val);

    cout << "Inorder Traversal: ";
    tree.inorder(tree.root);
    cout << endl;

    int key = 40;
    cout << "Search " << key << ": ";
    cout << (tree.search(tree.root, key) ? "Found" : "Not Found") << endl;

    cout << "\nDeleting 50..." << endl;
    tree.root = tree.deleteNode(tree.root, 50);

    cout << "Inorder after deletion: ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "Preorder: ";
    tree.preorder(tree.root);
    cout << endl;

    cout << "Postorder: ";
    tree.postorder(tree.root);
    cout << endl;

    return 0;
}