#include "ai.hpp"
#include <iostream>

Node::Node(Game& position, Square move, Result value, Node* parent): position(position), move(move), value(value), parent(parent) {};

int hash(int X, int O) {
  return X | (O << 9);
}

void make_tree(Node* start, const Player turn) {
  for (int pos = TL; pos <= BR; pos <<= 1) {
    if (!start->position.is_free(pos)) continue;

    // create new game instance

    Game child_game = start->position;
    child_game.turn = turn;
    child_game.place(pos, turn);

    // create new node

    Node* child = new Node(child_game, (Square)pos, Unrated, start);

    // calculate node value

    if (child_game.winner()) {
      if (turn == Player::X) child->value = X_Win;
      else child->value = O_Win;
    } 
    else if (child_game.is_tie()) child->value = Tie;

    start->children.push_back(child);

    if (child->value == Unrated) make_tree(child, turn == Player::X ? Player::O : Player::X);
  }
}

void rate(Node* start, const Player turn) {
  Result best = Unrated;
  for (Node* child : start->children) {
    if (child->value == Unrated)
      rate(child, turn == Player::X ? Player::O : Player::X);

    if (turn == Player::X && (child->value > best || best == Unrated)) best = child->value;
    else if (turn == Player::O && (child->value < best || best == Unrated)) best = child->value;
  }

  start->value = best;
}