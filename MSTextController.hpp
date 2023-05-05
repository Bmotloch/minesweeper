#pragma once
#ifndef MSTEXTCONTROLLER__
#define MSTEXTCONTROLLER__
#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"

class MSTextController
{
private:
    MinesweeperBoard &textboard;
    const MSBoardTextView &textview;

public:
    MSTextController(MinesweeperBoard &board, const MSBoardTextView &view);
    ~MSTextController();
    void play() const;
};

#endif