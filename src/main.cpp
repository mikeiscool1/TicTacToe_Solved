#include <iostream>
#include <algorithm>
#include "game.hpp"
#include "ai.hpp"

void play() {
  Game game;
  Player play_as;
  Player ai_as;

  while (true) {
    std::string turn;
    std::cout << "Play as \x1B[31mX\x1B[0m or \x1B[33mO\x1B[0m: ";
    std::cin >> turn;

    if (turn == "X" || turn == "x") play_as = Player::X, ai_as = Player::O;
    else if (turn == "O" || turn == "o") play_as = Player::O, ai_as = Player::X;
    else {
      std::cout << "Invalid input. Try again.\n";
      continue;
    }

    break;
  }

  // calculate moves
  Node current_node = { game, Unrated, 0 };
  reserve();
  current_node.value = minimax(current_node, Player::X, 0).result;

  if (play_as == Player::X) game.print();

  Player turn = Player::X;

  while (true) {
    if (turn == ai_as) {
      std::vector<Node*> best_nodes;
      best_nodes.reserve(8);

      for (Node* node : current_node.children)
        if (node->value == current_node.value) best_nodes.push_back(node);

      Node best_node = *best_nodes[0];
      if (current_node.value != Tie) {
        // try winning faster
        // We dont have to worry about if we're losing, because the AI can never be losing.
        for (const Node* node : best_nodes)
          if (node->rating_depth < best_node.rating_depth)
            best_node = *node;
      }

      game.X = best_node.position.X;
      game.O = best_node.position.O;
      
      // move down the tree
      current_node = best_node;

      if (game.winner(turn)) {
        game.print();
        std::cout << (turn == Player::X ? "X" : "O") << " wins!\n";
        return;
      }

      if (game.is_tie()) {
        game.print();
        std::cout << "Game is a tie.\n";
        return;
      }

      turn = play_as;

      game.print();
      continue;
    } else {
      std::cout << "Your turn: ";
    }

    int square;
    std::cin >> square;

    if (square > 9 || square < 1) {
      std::cout << "Invalid square.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard the remaining input
      continue;
    }

    int at = 1 << (square - 1);

    if (!game.is_free(at)) {
      std::cout << "Square is already occupied\n";
      continue;
    }

    game.place(at, turn);

    if (game.winner(turn)) {
      game.print();
      std::cout << (turn == Player::X ? "X" : "O") << " wins!\n";
      return;
    }

    if (game.is_tie()) {
      game.print();
      std::cout << "Game is a tie.\n";
      return;
    }

    turn = ai_as;

    // move down the tree
    current_node = **std::find_if(current_node.children.begin(), current_node.children.end(), 
      [&game](Node* i) 
      { return i->position.X == game.X && i->position.O == game.O; }
    );
  }
}

int main() {
  play();
  return 0;
}