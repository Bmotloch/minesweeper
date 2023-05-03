#include "MinesweeperBoard.hpp"

// kompilacja g++ main.cpp MinesweeperBoard.cpp -o main
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