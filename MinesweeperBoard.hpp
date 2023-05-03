#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Array2D.h"

struct Field
{
    bool hasMine{false};
    bool hasFlag{false};
    bool isRevealed{false};
};

enum class GameMode
{
    DEBUG,
    EASY,
    NORMAL,
    HARD
};

GameMode getGameMode(const std::string &str);
class MinesweeperBoard
{
private:
    const int nrows{100};
    const int ncols{100};
    Array2D<Field> board_{nrows, ncols};
    void fillBoard(Array2D<Field> &board, int mineCount);
    void debug_fillBoard(Array2D<Field> &board);
    char debug_checkRevealed(bool) const;
    char debug_checkFlag(bool) const;
    char debug_checkMine(bool) const;
    int width_;
    int height_;
    GameMode mode_;

public:
    MinesweeperBoard(int rows, int columns, GameMode mode);
    ~MinesweeperBoard();
    void debug_display() const;
};
