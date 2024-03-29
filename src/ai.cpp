#include "ai.hpp"
#include <iostream>

Node::Node(Game& position, Result value, int rating_depth): 
  position(position), value(value), rating_depth(rating_depth) {}

std::vector<Node> nodes;
std::unordered_map<int, Node*> table;

void reserve() {
  // reserve just enough space for all the nodes created.
  // This number can be calculated by seeing the size of `nodes` is after running `minimax`
  // Necessary because if a new vector is allocated due to needing new space, all pointers become invalid (dangling)
  // Therefore, making this number any smaller will cause the entire program to fail.
  nodes.reserve(5477);
}

// function that converts a board position into one integer allowing for quicker search.
inline int hash(int X, int O) {
  return X | (O << 9);
}

Output minimax(Node& node, Player turn, int depth) {
  // create children nodes
  Player other_player = turn == Player::X ? Player::O : Player::X;

  // slight optimization
  int children_amount = 9 - __builtin_popcount(node.position.X | node.position.O);
  node.children.reserve(children_amount);

  for (int pos = TL; pos <= BR; pos <<= 1) {
    if (!node.position.is_free(pos)) continue;
    Game position = node.position;
    position.place(pos, turn);

    int pos_hash = hash(position.X, position.O);
    if (auto it = table.find(pos_hash); it != table.end()) {
      node.children.push_back(it->second);
      continue;
    }

    Result child_result = Unrated;
    if (position.winner(turn)) {
      if (turn == Player::X) child_result = X_Win;
      else child_result = O_Win;
    }
    else if (position.is_tie()) child_result = Tie;

    nodes.push_back({ position, child_result });
    Node* child = &nodes.back();

    node.children.push_back(child);
    table.insert({ pos_hash, child });
  }

  // rate
  Result best_value = turn == Player::X ? O_Win : X_Win;
  for (Node* child : node.children) {
    if (child->value == Unrated) {
      Output output = minimax(*child, other_player, depth + 1);
      child->value = output.result;
      child->rating_depth = output.depth;
    }

    best_value = turn == Player::X 
      ? std::max(best_value, child->value) 
      : std::min(best_value, child->value);
  }

  node.rating_depth = depth;
  return { best_value, depth };
}