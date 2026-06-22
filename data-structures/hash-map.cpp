#include <iostream>
#include <vector>
#include <list>

using namespace std;

class HashMap {
private:
    int bucketSize;
    vector<list<pair<int, int>>> table;

    int hashFunction(int key);

public:
    HashMap(int size = 10);

    void put(int key, int value);

    int get(int key);

    void remove(int key);

    bool containsKey(int key);

    void display();
};

HashMap::HashMap(int size) {
    bucketSize = size;
    table.resize(bucketSize);
}

int HashMap::hashFunction(int key) {
    return key % bucketSize;
}

void HashMap::put(int key, int value) {
    int index = hashFunction(key);

    for (auto &p : table[index]) {
        if (p.first == key) {
            p.second = value;
            return;
        }
    }

    table[index].push_back({key, value});
}

int HashMap::get(int key) {
    int index = hashFunction(key);

    for (auto &p : table[index]) {
        if (p.first == key)
            return p.second;
    }

    return -1;
}

void HashMap::remove(int key) {
    int index = hashFunction(key);

    auto &bucket = table[index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
}

bool HashMap::containsKey(int key) {
    int index = hashFunction(key);

    for (auto &p : table[index]) {
        if (p.first == key)
            return true;
    }

    return false;
}

void HashMap::display() {
    for (int i = 0; i < bucketSize; i++) {
        cout << i << " : ";

        for (auto &p : table[i]) {
            cout << "(" << p.first << "," << p.second << ") ";
        }

        cout << endl;
    }
}

int main() {
    HashMap mp;

    mp.put(10, 100);
    mp.put(20, 200);
    mp.put(15, 150);

    cout << mp.get(20) << endl;

    mp.display();
}