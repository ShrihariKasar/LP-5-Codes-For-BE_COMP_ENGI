// Assignment 1(a): Design and Implement Parallel Breadth First Search (BFS) using OpenMP

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adj;

public:
    Graph(int v) {
        vertices = v;
        adj.resize(v);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected Graph
    }

    void parallelBFS(int start) {

        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS Traversal: ";

        while (!q.empty()) {

            int size = q.size();

            vector<int> currentLevel;

            // Extract current level nodes
            while (size--) {
                int node = q.front();
                q.pop();

                currentLevel.push_back(node);

                cout << node << " ";
            }

            // Parallel processing of neighbors
            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++) {

                int node = currentLevel[i];

                for (int neighbor : adj[node]) {

                    if (!visited[neighbor]) {

                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                q.push(neighbor);
                            }
                        }
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {

    int v = 7;

    Graph g(v);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    g.parallelBFS(0);

    return 0;
}