#include "MSTextController.hpp"

MSTextController::MSTextController(MinesweeperBoard &board, const MSBoardTextView &view) : textboard{board}, textview{view}
{
}

MSTextController::~MSTextController()
{
}

void MSTextController::play() const
{
    std::cout << "Usage:\n"
              << "< f - flag || r - reveal > < row > < column >" << std::endl;
    while (textboard.getGameState() == GameState::RUNNING)
    {
        int row{0}, col{0};
        std::string choice{""};
        textview.display();
        std::cout << "Your move: ";
        if (std::cin >> choice >> row >> col)
        {
            system("clear");
            if (choice == "f")
            {
                textboard.toggleFlag(row, col);
                textboard.message();
            }
            else if (choice == "r")
            {

                textboard.revealField(row, col);
                textboard.message();
            }
            else
            {
                std::cout << "Incorrect option:\n";
            }
        }
        else
        {
            std::cout << "Invalid coordinates" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
