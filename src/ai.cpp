#include "ai.hpp"
#include <iostream>
#include <unordered_map>

std::unordered_map<int, std::shared_ptr<Node>> table;

Node::Node(Game position, Result value): position(position), value(value) {};

inline int hash(int X, int O) {
  return X | (O << 9);
}

void make_tree(std::shared_ptr<Node>& start, Player turn) {
  for (int pos = TL; pos <= BR; pos <<= 1) {
    if (!start->position.is_free(pos)) continue;

    // create new game instance
    Game child_game = start->position;
    child_game.turn = turn;
    child_game.place(pos, turn);

    // calculate node value
    int pos_hash = hash(child_game.X, child_game.O);
    auto it = table.find(pos_hash);
    if (it != table.end()) {
      start->children.push_back(it->second);
      continue;
    }

    // create new node
    std::shared_ptr<Node> child = std::make_shared<Node>(child_game, Unrated);

    if (child_game.winner()) {
      if (turn == Player::X) child->value = X_Win;
      else child->value = O_Win;
    } 
    else if (child_game.is_tie()) child->value = Tie;

    table.insert({ pos_hash, child });
    start->children.push_back(child);

    if (child->value == Unrated) make_tree(child, turn == Player::X ? Player::O : Player::X);
  }
}

void rate(std::shared_ptr<Node>& start, Player turn) {
  Result best = Unrated;
  for (std::shared_ptr<Node>& child : start->children) {
    if (child->value == Unrated)
      rate(child, turn == Player::X ? Player::O : Player::X);

    if (turn == Player::X && (child->value > best || best == Unrated)) best = child->value;
    else if (turn == Player::O && (child->value < best || best == Unrated)) best = child->value;
  }

  start->value = best;
}