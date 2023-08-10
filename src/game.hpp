#pragma once

enum class Player {
  X, O, None
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

  Game();
  Game(int X, int O, Player turn);

  void place(int at, Player as);
  bool is_free(int at);
  bool is_tie();
  bool winner();
  void print();
};