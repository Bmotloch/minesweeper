#include "MinesweeperBoard.hpp"

GameMode getGameMode(const std::string &str)
{
    if (str == "DEBUG")
    {
        std::cout << "Chosen mode: " << str << std::endl;
        return GameMode::DEBUG;
    }
    else if (str == "EASY")
    {
        std::cout << "Chosen mode: " << str << std::endl;
        return GameMode::EASY;
    }
    else if (str == "NORMAL")
    {
        std::cout << "Chosen mode: " << str << std::endl;
        return GameMode::NORMAL;
    }
    else if (str == "HARD")
    {
        std::cout << "Chosen mode: " << str << std::endl;
        return GameMode::HARD;
    }
    else
    {
        std::cerr << "Wrong GameMode!\nEASY mode was chosen as default\n";
        return GameMode::EASY;
    }
}

MinesweeperBoard::MinesweeperBoard(int rows, int columns, GameMode mode) : height_{std::min(rows, 100)}, width_{std::min(columns, 100)}, mode_{mode}
{
    board_.resize(height_, width_);
    switch (mode_)
    {
    case GameMode::EASY:
        fillBoard(board_, round(0.1 * height_ * width_));
        break;
    case GameMode::NORMAL:
        fillBoard(board_, round(0.2 * height_ * width_));
        break;
    case GameMode::HARD:
        fillBoard(board_, round(0.3 * height_ * width_));
        break;
    case GameMode::DEBUG:
        debug_fillBoard(board_);
        break;
    }
}

MinesweeperBoard::~MinesweeperBoard()
{
}

void MinesweeperBoard::fillBoard(Array2D<Field> &board, int mineCount)
{
    std::vector<int> selected;
    for (int i = 0; i < mineCount; i++)
    {
        int row = rand() % height_;
        int col = rand() % width_;
        if (std::find(selected.begin(), selected.end(), row * width_ + col) != selected.end())
        {
            i--;
            continue;
        }
        board[row][col].hasMine = true;
        selected.push_back(row * width_ + col);
    }
}

void MinesweeperBoard::debug_fillBoard(Array2D<Field> &board)
{
    for (int j = 0; j < width_; j++) // first row
    {
        board[0][j].hasMine = true;
    }
    for (int j = 0; j < height_; j += 2) // every 2nd column
    {
        board[j][0].hasMine = true;
    }
    int size{std::min(height_, width_)};
    for (int j = 0; j < size; j++) // every 2nd column
    {
        board[j][j].hasMine = true;
    }
}

void MinesweeperBoard::debug_display() const
{
    std::cout << "       ";
    for (int i = 0; i < width_; i++)
    {
        std::cout << "   " << i << "   ";
    }
    std::cout << std::endl;
    for (int i = 0; i < height_; i++)
    {
        std::cout << "   " << i << "   ";
        for (int j = 0; j < width_; j++)
        {
            std::cout << "["
                      << debug_checkMine(board_[i][j].hasMine)
                      << " "
                      << debug_checkRevealed(board_[i][j].isRevealed)
                      << " "
                      << debug_checkFlag(board_[i][j].hasFlag)
                      << "]";
        }
        std::cout << std::endl;
    }
}

char MinesweeperBoard::debug_checkRevealed(bool check) const
{
    if (!check)
    {
        return '.';
    }
    else
    {
        return 'o';
    }
}

char MinesweeperBoard::debug_checkFlag(bool check) const
{
    if (!check)
    {
        return '.';
    }
    else
    {
        return 'f';
    }
}

char MinesweeperBoard::debug_checkMine(bool check) const
{
    if (!check)
    {
        return '.';
    }
    else
    {
        return 'M';
    }
}
