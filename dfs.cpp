// Assignment 1(b): Design and Implement Parallel Depth First Search (DFS) using OpenMP

#include <iostream>
#include <vector>
#include <stack>
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

    void parallelDFS(int start) {

        vector<bool> visited(vertices, false);
        stack<int> st;

        st.push(start);

        cout << "Parallel DFS Traversal: ";

        while (!st.empty()) {

            int node;

            #pragma omp critical
            {
                node = st.top();
                st.pop();
            }

            if (!visited[node]) {

                visited[node] = true;

                cout << node << " ";

                // Parallel traversal of adjacent nodes
                #pragma omp parallel for
                for (int i = 0; i < adj[node].size(); i++) {

                    int neighbor = adj[node][i];

                    if (!visited[neighbor]) {

                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                st.push(neighbor);
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

    g.parallelDFS(0);

    return 0;
}