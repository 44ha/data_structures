#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph {
private:
    int V;
    bool directed;
    vector<vector<int>> adj;

    void dfsHelper(int v, vector<bool>& visited) const {
        visited[v] = true;
        cout << v << " ";
        for (int u : adj[v])
            if (!visited[u]) dfsHelper(u, visited);
    }

    bool hasCycleHelper(int v, vector<bool>& visited,
                        vector<bool>& inStack) const {
        visited[v] = true;
        inStack[v] = true;
        for (int u : adj[v]) {
            if (!visited[u] && hasCycleHelper(u, visited, inStack)) return true;
            if (inStack[u]) return true;
        }
        inStack[v] = false;
        return false;
    }

    void topoHelper(int v, vector<bool>& visited, stack<int>& st) const {
        visited[v] = true;
        for (int u : adj[v])
            if (!visited[u]) topoHelper(u, visited, st);
        st.push(v);
    }

public:
    Graph(int vertices, bool isDirected = false)
        : V(vertices), directed(isDirected), adj(vertices) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    void bfs(int start) const {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "BFS from " << start << ": ";
        while (!q.empty()) {
            int v = q.front(); q.pop();
            cout << v << " ";
            for (int u : adj[v])
                if (!visited[u]) { visited[u] = true; q.push(u); }
        }
        cout << "\n";
    }

    void dfs(int start) const {
        vector<bool> visited(V, false);
        cout << "DFS from " << start << ": ";
        dfsHelper(start, visited);
        cout << "\n";
    }

    bool hasCycle() const {
        vector<bool> visited(V, false);
        vector<bool> inStack(V, false);
        for (int i = 0; i < V; ++i)
            if (!visited[i] && hasCycleHelper(i, visited, inStack)) return true;
        return false;
    }

    void topologicalSort() const {
        vector<int> inDegree(V, 0);
        for (int u = 0; u < V; ++u)
            for (int v : adj[u]) ++inDegree[v];

        queue<int> q;
        for (int i = 0; i < V; ++i)
            if (inDegree[i] == 0) q.push(i);

        cout << "Topological order: ";
        int visited = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            cout << v << " ";
            ++visited;
            for (int u : adj[v])
                if (--inDegree[u] == 0) q.push(u);
        }
        if (visited != V) cout << "(cycle detected)";
        cout << "\n";
    }

    void printAdj() const {
        for (int i = 0; i < V; ++i) {
            cout << i << " -> ";
            for (int v : adj[i]) cout << v << " ";
            cout << "\n";
        }
    }
};

class WeightedGraph {
private:
    int V;
    vector<vector<pair<int,int>>> adj;

public:
    WeightedGraph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    vector<int> dijkstra(int src) const {
        vector<int> dist(V, INF);
        dist[src] = 0;

        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    void printShortestPaths(int src) const {
        auto dist = dijkstra(src);
        cout << "Shortest distances from vertex " << src << ":\n";
        for (int i = 0; i < V; ++i) {
            cout << "  -> " << i << " : ";
            if (dist[i] == INF) cout << "INF\n";
            else cout << dist[i] << "\n";
        }
    }
};

int main() {
    cout << "=== Undirected Graph (BFS / DFS) ===\n";
    Graph g(6, false);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "Adjacency list:\n";
    g.printAdj();
    g.bfs(0);
    g.dfs(0);

    cout << "\n=== Directed Graph (Cycle / Topo Sort) ===\n";
    Graph dag(6, true);
    dag.addEdge(5, 2);
    dag.addEdge(5, 0);
    dag.addEdge(4, 0);
    dag.addEdge(4, 1);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);
    dag.topologicalSort();
    cout << "Has cycle: " << (dag.hasCycle() ? "yes" : "no") << "\n";

    cout << "\n=== Weighted Graph (Dijkstra) ===\n";
    WeightedGraph wg(5);
    wg.addEdge(0, 1, 10);
    wg.addEdge(0, 2, 3);
    wg.addEdge(1, 3, 2);
    wg.addEdge(2, 1, 4);
    wg.addEdge(2, 3, 8);
    wg.addEdge(2, 4, 2);
    wg.addEdge(3, 4, 5);
    wg.printShortestPaths(0);

    return 0;
}
