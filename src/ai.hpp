#pragma once

#include "game.hpp"
#include <vector>
#include <map>

enum Result { O_Win = -1, Unrated, Tie, X_Win };

struct Node {
  Game position;
  Result value = Unrated;
  std::vector<Node*> children;

  Node(Game position, Result value);
};

void make_tree(Node* start, const Player turn);
void rate(Node* start, Player turn);