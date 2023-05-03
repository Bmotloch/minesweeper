#include <string>
#include <iostream>
#include "Array2D.h"

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
