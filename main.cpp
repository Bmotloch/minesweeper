#include <string>
#include <iostream>
#include "Array2D.h"

//kompilacja g++ main.cpp -o main
struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard
{
private:
    const int nrows{100};
    const int ncols{100};
    Array2D<Field> board_{nrows, ncols};
    void initialiseBoard(Array2D<Field> &board);
    int width_;
    int height_;

public:
    MinesweeperBoard(int rows, int columns);
    ~MinesweeperBoard();
    void debug_display() const;
    char debug_checkRevealed(bool) const;
    char debug_checkFlag(bool) const;
    char debug_checkMine(bool) const;
};

MinesweeperBoard::MinesweeperBoard(int rows, int columns) : height_{std::min(rows, 100)}, width_{std::min(columns, 100)}
{
    board_.resize(height_, width_);
    initialiseBoard(board_);
}

MinesweeperBoard::~MinesweeperBoard()
{
}

void MinesweeperBoard::initialiseBoard(Array2D<Field> &board)
{
    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            board[i][j].hasMine = false;
            board[i][j].hasFlag = false;
            board[i][j].isRevealed = false;
        }
    }
    board[0][0].hasMine = true;
    board[1][1].isRevealed = true;
    board[0][2].hasMine = true;
    board[0][2].hasFlag = true;
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

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <height> <width>\n";
        return 1;
    }

    int height = std::stoi(argv[1]);
    int width = std::stoi(argv[2]);

    MinesweeperBoard board(height, width);
    board.debug_display();
    return 0;
}