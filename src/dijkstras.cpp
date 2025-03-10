#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.resize(n, -1);
    vector<int> visited(n, false);

    priority_queue<Edge> pq;
    pq.push(Edge(source, 0, 0));
    distance[source] = 0;

    while(!pq.empty()) {
        Edge current = pq.top();
        pq.pop();
        int u = current.src;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const auto& e: G[u]) {
            int v = e.src;
            int w = e.weight;

            if (!visited[v] && (distance[u] + w) < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push(Edge(v,distance[v], 0));
            }
        }
    }
    return {};
}

// vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {}

// void print_path(const vector<int>& v, int total) {}