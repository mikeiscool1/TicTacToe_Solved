#pragma once

#include "game.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

enum Result { O_Win = -1, Unrated, Tie, X_Win };

struct Node {
  Game position;
  Result value = Unrated;
  std::vector<std::shared_ptr<Node>> children;

  Node(Game position, Result value);
};

// create a decision tree of all possible positions in Tic Tac Toe
void make_tree(std::shared_ptr<Node>&, Player turn);
// Implement the MiniMax algorithm to assign a rating to all nodes created in `make_tree`
void rate(std::shared_ptr<Node>&, Player turn);
// Free all shared pointers in the global table map
void free_table();