#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // {weight, vertex}

void primsAlgorithm(int V, const vector<vector<pii>>& adj) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    // Start with vertex 0
    pq.push({0, 0});
    key[0] = 0;

    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        totalWeight += key[u];

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Edge \tWeight" << endl;
    for (int i = 1; i < V; ++i) {
        cout << parent[i] << " - " << i << " \t" << key[i] << endl;
    }
    cout << "Total MST Weight: " << totalWeight << endl;
}

int main() {
    ifstream infile("input.txt"); // Ensure this file exists
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int V, E;
    infile >> V >> E;

    vector<vector<pii>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        infile >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Undirected graph
    }

    primsAlgorithm(V, adj);

    return 0;
}
