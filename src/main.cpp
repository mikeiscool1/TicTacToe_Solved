#include <iostream>
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
      std::cout << "Invalid input. Try again." << std::endl;
      continue;
    }

    break;
  }

  // calculate moves
  std::shared_ptr<Node> current_node = std::make_shared<Node>(game, Unrated);
  make_tree(current_node, Player::X);
  free_table();
  rate(current_node, Player::X);

  if (play_as == Player::X) game.print();

  while (true) {
    if (game.turn == ai_as) {
      // AI's turn
      // find which of the node's childrens' values match the node's value, and then use that move
      std::shared_ptr<Node>& best_node = *std::find_if(current_node->children.begin(), current_node->children.end(), 
        [&current_node](std::shared_ptr<Node>& i)
        { return i->value == current_node->value; }
      );

      game.X = best_node->position.X;
      game.O = best_node->position.O;
      
      // move down the tree
      current_node = best_node;

      if (game.winner()) {
        game.print();
        std::cout << (game.turn == Player::X ? "X" : "O") << " wins!" << std::endl;
        return;
      }

      if (game.is_tie()) {
        game.print();
        std::cout << "Game is a tie." << std::endl;
        return;
      }

      game.turn = play_as;

      game.print();
      continue;
    } else {
      std::cout << "Your turn: ";
    }

    int square;
    std::cin >> square;

    if (square > 9 || square < 1) {
      std::cout << "Invalid square." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard the remaining input
      continue;
    }

    int at = 1 << (square - 1);

    if (!game.is_free(at)) {
      std::cout << "Square is already occupied" << std::endl;
      continue;
    }

    game.place(at, game.turn);

    if (game.winner()) {
      game.print();
      std::cout << (game.turn == Player::X ? "X" : "O") << " wins!" << std::endl;
      return;
    }

    if (game.is_tie()) {
      game.print();
      std::cout << "Game is a tie." << std::endl;
      return;
    }

    game.turn = ai_as;

    // move down the tree
    current_node = *std::find_if(current_node->children.begin(), current_node->children.end(), 
      [&game](std::shared_ptr<Node>& i) 
      { return i->position.X == game.X && i->position.O == game.O; }
    );
  }
}

int main() {
  play();
  return 0;
}