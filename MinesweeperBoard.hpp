#pragma once
#ifndef MINESBOARD_H__
#define MINESBOARD_H__
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

enum class GameState
{
    RUNNING,
    FINISHED_WIN,
    FINISHED_LOSS
};

GameMode getGameMode(const std::string &str);
class MinesweeperBoard
{
private:
    const int maxsize{100};
    Array2D<Field> board_{maxsize, maxsize};
    void fillBoard(Array2D<Field> &board, int mineCount);
    void debug_fillBoard(Array2D<Field> &board);
    char debug_checkRevealed(bool) const;
    char debug_checkFlag(bool) const;
    char debug_checkMine(bool) const;
    void relocateMine(int row, int col);
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    bool checkInputRange(int row, int col) const;
    bool hasFlag(int row, int col) const;
    bool isRevealed(int row, int col) const;
    bool isBoardFresh() const;
    int width_, height_;
    GameMode mode_;
    GameState state_{GameState::RUNNING};
    void setGameState(GameState state);
    bool checkWin();
    char getFieldInfo(int row, int col) const;
    int countMines(int row, int col) const;

public:
    MinesweeperBoard(int rows, int columns, GameMode mode);
    ~MinesweeperBoard();
    GameState getGameState() const;
    GameState message() const;
    void debug_display() const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
};

#endif