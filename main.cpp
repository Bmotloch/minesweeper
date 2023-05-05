#include "MinesweeperBoard.hpp"
#include "MSBoardTextView.hpp"

// kompilacja g++ main.cpp MinesweeperBoard.cpp -o main
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <height> <width> <GameMode>\n";
        return 1;
    }
    srand(time(0));
    int height{std::stoi(argv[1])};
    int width{std::stoi(argv[2])};
    GameMode mode{getGameMode(argv[3])};
    MinesweeperBoard board(height, width, mode);
    MSBoardTextView view(board);
    while (board.getGameState() == GameState::RUNNING)
    {
        std::string choice{""}, row{""}, col{""};
        view.display();
        std::cin >> choice >> row >> col;
        system("clear");
        if (choice == "f")
        {
            board.toggleFlag(std::stoi(row), std::stoi(col));
            board.message();
        }
        if (choice == "r")
        {
            board.revealField(std::stoi(row), std::stoi(col));
            board.message();
        }
    }
    return 0;
}