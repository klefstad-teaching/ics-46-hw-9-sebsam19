#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(dijkstras_insertion, inserting) {
  Graph G;
  file_to_graph("src/small.txt", G);
  vector<int> p(G.numVertices, -1);
  int src = 0;
  int dest = 3;

  vector<int> distance = dijkstra_shortest_path(G, src, p);
  vector<int> path = extract_shortest_path(distance, p, dest);

  EXPECT_TRUE(path[0] == 0);
  EXPECT_TRUE(path[1] == 3);
}

TEST(ladder_testing, ladder) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  EXPECT_TRUE(generate_word_ladder("cat", "dog", word_list).size() == 4);
}