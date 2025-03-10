#include "dijkstras.h"
#include <gtest/gtest.h>

int main(int argc, char * argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> p(G.numVertices, -1);
    int src = 0;
    int dest = 12;

    vector<int> distances = dijkstra_shortest_path(G, src, p);
    vector<int> path = extract_shortest_path(distances, p, dest);

    cout << "shortest path" << " : ";
    print_path(path, path.size());
    return result;
}