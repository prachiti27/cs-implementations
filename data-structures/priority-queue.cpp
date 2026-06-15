#include <iostream>
#include <vector>

using namespace std;

class PriorityQueue {
    private:
        vector<int> heap;
    public:
        void push(int x);
        void pop();
        int top();
        int size();
        bool empty();
};

void PriorityQueue::push(int x) {
    heap.push_back(x);
    int idx = heap.size() - 1;

    while(idx > 0) {
        int parent = (idx-1)/2;

        if(heap[parent] < heap[idx]) {
            swap(heap[parent], heap[idx]);
            idx = parent;
        }
        else break;
    }
}

void PriorityQueue::pop() {
    if(heap.empty()) return;

    swap(heap[0], heap.back());

    heap.pop_back();

    int idx = 0;
    int n = heap.size();

    while(true) {
        int left = 2*idx + 1;
        int right = 2*idx + 1;
        int largest = idx;

        if(left<n && heap[left] > heap[largest])
            largest = left;
        if(right<n && heap[right] > heap[largest])
            largest = right;

        if(largest == idx) break;

        swap(heap[idx], heap[largest]);
        idx = largest;
    }
}

int PriorityQueue::top() {
    if(heap.empty())
    {
        cout<<"No element in heap"<<endl;
        return 0;
    }
    return heap[0];
}

int PriorityQueue::size() {
    return heap.size();
}

bool PriorityQueue::empty() {
    return heap.empty();
}

void display(PriorityQueue pq) {
    while(!pq.empty()) {
        cout<<pq.top()<<"  ";
        pq.pop();
    }
    cout<<endl;
}

int main() {
    PriorityQueue pq;
    pq.push(30);
    pq.push(10);
    pq.push(20);
    pq.push(50);
    pq.push(70);

    display(pq);

    pq.pop();

    display(pq);
}
