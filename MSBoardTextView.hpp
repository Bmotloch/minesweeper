#pragma once
#ifndef MSBBOARDTEXTVIEW__
#define MSBBOARDTEXTVIEW__
#include "MinesweeperBoard.hpp"
class MSBoardTextView
{
private:
    const MinesweeperBoard &textboard;

public:
    MSBoardTextView(const MinesweeperBoard &board);
    ~MSBoardTextView();
    void display() const;
};

#endif