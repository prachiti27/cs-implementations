#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> kahnAlgorithm(int n, vector<vector<int>>& edges) {

    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];

        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo;

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        topo.push_back(node);

        for (int neighbour : adj[node]) {

            indegree[neighbour]--;

            if (indegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    if (topo.size() != n) {
        return {};
    }

    return topo;
}

int main() {

    int n = 6;

    vector<vector<int>> edges = {
        {5, 2},
        {5, 0},
        {4, 0},
        {4, 1},
        {2, 3},
        {3, 1}
    };

    vector<int> ans = kahnAlgorithm(n, edges);

    if (ans.empty()) {
        cout << "Cycle detected\n";
    }
    else {
        cout << "Topological Order: ";

        for (int node : ans) {
            cout << node << " ";
        }
    }

    return 0;
}