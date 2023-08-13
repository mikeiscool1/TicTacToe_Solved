#pragma once
#include <vector>

enum class Player {
  X, O
};

enum Square {
  TL = 1 << 0,
  TM = 1 << 1,
  TR = 1 << 2,
  ML = 1 << 3,
  MM = 1 << 4,
  MR = 1 << 5,
  BL = 1 << 6,
  BM = 1 << 7,
  BR = 1 << 8,
  ALL = (1 << 9) - 1
};

struct Game {
  int X = 0;
  int O = 0;
  Player turn;
  static std::vector<int> win_cases;

  Game();
  Game(int X, int O, Player turn);

  inline void place(int at, Player as) {
    if (as == Player::X) X |= at;
    else O |= at;
  };

  inline bool is_free(int at) const {
    if ((X | O) & at) return false;
    return true;
  };

  inline bool is_tie() const {
    return ((X | O) == ALL);
  };

  inline bool winner() const {
    int bit = turn == Player::X ? X : O;

    for (int win_case : win_cases)
      if ((bit & win_case) == win_case) return true;

    return false;
  };

  void print() const;
};