#include "MSBoardTextView.hpp"

MSBoardTextView::MSBoardTextView(const MinesweeperBoard &board) : textboard{board}
{

}

MSBoardTextView::~MSBoardTextView(){
    
}

void MSBoardTextView::display()const
{
    std::cout << "     ";
    for (int i = 0; i < textboard.getBoardWidth(); i++)
    {
        std::cout << "  " << i << "  ";
    }
    std::cout << std::endl;
    for (int i = 0; i < textboard.getBoardHeight(); i++)
    {
        std::cout << "  " << i << "  ";
        for (int j = 0; j < textboard.getBoardWidth(); j++)
        {
            std::cout << "[ "
                      << textboard.getFieldInfo(i, j)
                      << " ]";
        }
        std::cout << std::endl;
    }
}