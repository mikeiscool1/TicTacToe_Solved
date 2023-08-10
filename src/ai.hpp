#pragma once

#include "game.hpp"
#include <vector>
#include <map>

enum Result { O_Win = -1, Unrated, Tie, X_Win };

struct Node {
  Game& position;
  // the last move to get to this position
  Square move;
  Result value = Unrated;
  Node* parent;
  std::vector<Node*> children;

  Node(Game& position, Square move, Result value, Node* parent);
};

void make_tree(Node* start, const Player turn);
void rate(Node* start, Player turn);