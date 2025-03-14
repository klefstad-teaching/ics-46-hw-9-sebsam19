#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<int> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    distance[source] = 0;

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const auto& e: G[u]) {
            int v = e.dst;
            int w = e.weight;

            if (distance[u] != INF && !visited[v] && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> holder;
    if (distances[destination] == INF) {
        return holder;
    }

    for (int i = destination; i != -1; i = previous[i]) {
        holder.push_back(i);
    }
    reverse(holder.begin(), holder.end());
    return holder;
}

void print_path(const vector<int>& v, int total) {
    if (!v.empty()) {
        for (size_t i = 0; i <v.size(); ++i) {
            cout << v[i] << " ";
        }
    }
    cout << "\n" << "Total cost is " << total << endl;
}