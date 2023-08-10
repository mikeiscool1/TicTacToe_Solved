#include "game.hpp"
#include <iostream>
#include <vector>

Game::Game(): X(0), O(0), turn(Player::X) {};
Game::Game(int X, int O, Player turn) : X(X), O(O), turn(turn) {};

void Game::place(int at, Player as) {
  if (as == Player::X) X |= at;
  else O |= at;
}

bool Game::is_free(int at) {
  if ((X | O) & at) return false;
  return true;
}

bool Game::is_tie() {
  return ((X | O) == ALL);
}

bool Game::winner() {
  static std::vector<int> win_cases = {
    TL | TM | TR,
    ML | MM | MR,
    BL | BM | BR,
    TL | ML | BL,
    TM | MM | BM,
    TR | MR | BR,
    TL | MM | BR,
    BL | MM | TR
  };

  int bit = turn == Player::X ? X : O;

  for (const int& win_case : win_cases)
    if ((bit & win_case) == win_case) return true;
  
  return false;
}

void Game::print()
{
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