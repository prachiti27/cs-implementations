#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;

    Node(int val) {
        key = val;
        left = right = NULL;
        height = 1;
    }
};

int getHeight(Node *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

int getBalance(Node *root) {
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

void updateHeight(Node *root) {
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node *root, int key) {

    if (root == NULL)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* minValueNode(Node *root) {
    Node *curr = root;
    while (curr->left != NULL)
        curr = curr->left;
    return curr;
}

Node* deleteNode(Node *root, int key) {

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {

        if (root->left == NULL || root->right == NULL) {

            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            delete temp;
        }

        else {

            Node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool search(Node *root, int key) {
    if (root == NULL)
        return false;

    if (root->key == key)
        return true;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

void inorder(Node *root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void preorder(Node *root) {
    if (root == NULL)
        return;

    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {

    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder: ";
    inorder(root);

    cout << "\nPreorder: ";
    preorder(root);

    cout << "\n";

    root = deleteNode(root, 40);

    cout << "After deleting 40:\n";
    inorder(root);

    cout << "\n";

    if (search(root, 25))
        cout << "25 Found\n";
    else
        cout << "25 Not Found\n";

    return 0;
}