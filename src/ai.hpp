#pragma once

#include "game.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

enum Result { O_Win = -1, Unrated, Tie, X_Win };

struct Node {
  Game position;
  Result value = Unrated;
  std::vector<Node*> children;

  Node(Game position, Result value);
};

void reserve();
// create a decision tree of all possible positions in Tic Tac Toe
void make_tree(Node& start, Player&& turn);
// Implement the MiniMax algorithm to assign a rating to all nodes created in `make_tree`
void rate(Node& start, Player turn);