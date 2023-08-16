#pragma once

#include "game.hpp"
#include <vector>
#include <memory>

enum Result { O_Win = -1, Unrated, Tie, X_Win };

struct Node {
  Game position;
  Result value = Unrated;
  std::vector<std::shared_ptr<Node>> children;

  Node(Game position, Result value);
};

void make_tree(std::shared_ptr<Node>&, Player turn);
void rate(std::shared_ptr<Node>&, Player turn);