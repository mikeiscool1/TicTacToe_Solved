#pragma once

#include "game.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

enum Result { O_Win = -1, Unrated, Tie, X_Win };

struct Node {
  Game position;
  Result value = Unrated;
  // rating_depth is not the real depth of the node, but rather the depth of the node its rating is from
  // Used to play the moves that either win quicker or lose slower.
  int rating_depth;
  std::vector<Node*> children;

  Node(Game& position, Result value, int rating_depth = 0);
};

struct Output {
  Result result;
  int depth;
};

Output minimax(Node& node, Player turn, int depth);
void reserve();