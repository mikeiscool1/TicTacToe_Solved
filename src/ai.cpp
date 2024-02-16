#include "ai.hpp"
#include <iostream>

Node::Node(Game position, Result value): position(position), value(value) {};

std::vector<Node> nodes;
std::unordered_map<int, Node*> table;

void reserve() {
  // reserve enough space to support all possible tic tac toe positions
  // Necessary because if a new vector is allocated due to needing new space, all pointers become invalid (dangling)
  // This number can be calculated by seeing the size of `nodes` is after running `make_tree`
  // Making this number any smaller will cause the entire program to fail. See second comment.
  nodes.reserve(5477);
}

// function that converts a board position into one integer allowing for quicker search.
inline int hash(int X, int O) {
  return X | (O << 9);
}

void make_tree(Node& start, Player&& turn) {
  for (int pos = TL; pos <= BR; pos <<= 1) {
    if (!start.position.is_free(pos)) continue;

    // create new game instance
    Game child_game = start.position;
    child_game.turn = turn;
    child_game.place(pos, turn);

    // check if node has already been evaluated.
    int pos_hash = hash(child_game.X, child_game.O);
    auto it = table.find(pos_hash);
    if (it != table.end()) {
      start.children.push_back(it->second);
      continue;
    }

    // create new node
    nodes.push_back({ child_game, Unrated });
    Node& child = nodes.back();

    if (child_game.winner()) {
      if (turn == Player::X) child.value = X_Win;
      else child.value = O_Win;
    } 
    else if (child_game.is_tie()) child.value = Tie;

    // node has been evaluated, add it to the table. 
    // If this same board position is ever revisited, it will push `child` directly, rather than creating a new node.
    table.insert({ pos_hash, &child });
    start.children.push_back(&child);

    // If the node does not have a resolution, continue creating a tree from it.
    if (child.value == Unrated) make_tree(child, turn == Player::X ? Player::O : Player::X);
  }
}

void rate(Node& start, Player turn) {
  Result best = Unrated;
  for (Node* child : start.children) {
    if (child->value == Unrated)
      rate(*child, turn == Player::X ? Player::O : Player::X);

    if (turn == Player::X && (child->value > best || best == Unrated)) best = child->value;
    else if (turn == Player::O && (child->value < best || best == Unrated)) best = child->value;
  }

  start.value = best;
}