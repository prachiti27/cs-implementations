#include <iostream>
#include <vector>

using namespace std;

class Node {
    public:
        string key;
        int value;
        Node* next;

        Node(string k, int v) {
            key = k;
            value = v;
            next = nullptr;
        }
};

class HashTable {
    private:
        int size;
        vector<Node*> table;
    public:
        HashTable(int s) {
            size = s;
            table.resize(size, nullptr);
        }
        int hashFunction(string key);
        void insert(string key, int value);
        bool search(string key, int& value);
        void remove(string key);
        void display();
};

int HashTable::hashFunction(string key) {
    int hash = 0;
    for(char c:key) hash = (hash*31 + c) % size;
    return hash;
}

void HashTable::insert(string key, int value) {
    int index = hashFunction(key);
    Node* head = table[index];

    while(head) {
        if(head->key == key) {
            head->value = value;
            return;
        }
        head = head->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

bool HashTable::search(string key, int& value) {
    int index = hashFunction(key);
    Node* curr = table[index];

    while(curr) {
        if(curr->key == key) {
            value = curr->value;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void HashTable::remove(string key) {
    int index = hashFunction(key);
    Node* curr = table[index];
    Node* prev = nullptr;

    while(curr) {
        if(curr->key == key) {
            if(prev == nullptr) table[index] = curr->next;
            else prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void HashTable::display() {
    for(int i=0;i<size;i++) {
        cout<<i<<" : ";
        Node* curr = table[i];
        while(curr) {
            cout<<"("<<curr->key<<","<<curr->value<<") -> ";
            curr = curr->next;
        }
        cout<<"NULL\n";
    }
}

int main() {
    HashTable ht(10);
    ht.insert("abc",100);
    ht.insert("def",200);
    ht.insert("ghi",300);
    ht.display();
    int val;
    if(ht.search("def", val)) cout<<val<<endl;

    ht.remove("def");
    ht.display();
}