//First Come First Serve
#include <bits/stdc++.h>

using namespace std;

class Process{
    int id, bt, at, ct, tat, wt;
    public:
        void input(Process*, int);
        void calc(Process*, int);
        void show(Process*, int);
        void sort(Process*, int);
};

void Process::input(Process *p, int n){
    for(int i=0;i<n;i++) {
        cout<<"\nEnter arrival time for process "<<(i+1)<<":\n";
        cin>>p[i].at;
        cout<<"\nEnter burst time for process "<<(i+1)<<":\n";
        cin>>p[i].bt;
        p[i].id = i+1;
    }
}

void Process::calc(Process *p, int n) {
    int sum = 0;
    sum += p[0].at;
    for(int i=0;i<n;i++) {
        sum += p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if(sum<p[i+1].at) {
            int t = p[i+1].at - sum;
            sum += t;
        }
    }
}

void Process::sort(Process *p, int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(p[j].at > p[j+1].at) {
                int temp;
                temp = p[i].bt;
                p[i].bt = p[j+1].bt;
                p[j+1].bt = temp;

                temp = p[j].at;
                p[j].at = p[j+1].at;
                p[j+1].at = temp;

                temp = p[j].id;
                p[j].id = p[j+1].id;
                p[j+1].id = temp;
            }
        }
    }
}

void Process::show(Process *p, int n){
    cout<<"Process\tArrival\tBrust\tWaiting\tTurnAround\tCompletion\n";
    for(int i=0;i<n;i++) {
        cout<<" P["<<p[i].id<<"]\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].wt<<"\t"<<p[i].tat<<"\t\t"<<p[i].ct<<"\n";
    }
}

int main() {
    int n;
    cout<<"\nEnter the number of processes in your system:\n";
    cin>>n;
    Process *p = new Process[n];
    Process f;
    f.input(p,n);
    f.sort(p,n);
    f.calc(p,n);
    f.show(p,n);
}