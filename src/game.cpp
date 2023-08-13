#include "game.hpp"
#include <iostream>

Game::Game(): X(0), O(0), turn(Player::X) {};
Game::Game(int X, int O, Player turn) : X(X), O(O), turn(turn) {};

std::vector<int> Game::win_cases = {
  TL | TM | TR,
  ML | MM | MR,
  BL | BM | BR,
  TL | ML | BL,
  TM | MM | BM,
  TR | MR | BR,
  TL | MM | BR,
  BL | MM | TR
};

void Game::print() const {
  std::cout << "+-----+-----+-----+\n|     |     |     |\n|";

  for (int i = 0; i < 9; i++)
  {
    std::cout << "  ";
    if (((1 << i) & X) != 0)
      std::cout << "\x1B[31mX\x1B[0m";
    else if (((1 << i) & O) != 0)
      std::cout << "\x1B[33mO\x1B[0m";
    
    else
      std::cout << i + 1;
    std::cout << "  |";
    if (i != 0 && (i + 1) % 3 == 0)
    {
      std::cout << "\n|     |     |     |\n+-----+-----+-----+";
      if (i != 8) std::cout << "\n|     |     |     |\n|";
      else std::cout << std::endl;
    }
  }
}