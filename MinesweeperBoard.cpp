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
    board_.resize(getBoardHeight(), getBoardWidth());
    switch (mode_)
    {
    case GameMode::EASY:
        fillBoard(board_, round(0.1 * getBoardHeight() * getBoardWidth()));
        break;
    case GameMode::NORMAL:
        fillBoard(board_, round(0.2 * getBoardHeight() * getBoardWidth()));
        break;
    case GameMode::HARD:
        fillBoard(board_, round(0.3 * getBoardHeight() * getBoardWidth()));
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
        int row = rand() % getBoardHeight();
        int col = rand() % getBoardWidth();
        if (std::find(selected.begin(), selected.end(), row * getBoardWidth() + col) != selected.end())
        {
            i--;
            continue;
        }
        board[row][col].hasMine = true;
        selected.push_back(row * getBoardWidth() + col);
    }
}

void MinesweeperBoard::debug_fillBoard(Array2D<Field> &board)
{
    for (int j = 0; j < getBoardWidth(); j++) // first row
    {
        board[0][j].hasMine = true;
    }
    for (int j = 0; j < getBoardHeight(); j += 2) // every 2nd column
    {
        board[j][0].hasMine = true;
    }
    int size{std::min(getBoardHeight(), getBoardWidth())};
    for (int j = 0; j < size; j++) // every 2nd column
    {
        board[j][j].hasMine = true;
    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return width_;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height_;
}

int MinesweeperBoard::getMineCount() const // wrongly assumed, you need to have all mines not revealed in order to win
{
    int count{0};
    for (int i = 0; i < getBoardHeight(); i++)
    {
        for (int j = 0; j < getBoardWidth(); j++)
        {
            if (board_[i][j].hasMine)
            {
                count++;
            }
        }
    }
    return count;
}

bool MinesweeperBoard::isBoardFresh() const
{
    for (int i = 0; i < getBoardHeight(); i++)
    {
        for (int j = 0; j < getBoardWidth(); j++)
        {
            if (board_[i][j].isRevealed || board_[i][j].hasFlag)
            {
                return false;
            }
        }
    }
    return true;
}

void MinesweeperBoard::relocateMine(int row, int col)
{
    int i = 0;
    while (i != 1)
    {
        int newRow = rand() % getBoardHeight();
        int newCol = rand() % getBoardWidth();
        i++;
        if (board_[newRow][newCol].hasMine)
        {
            i--;
            continue;
        }
        else
        {
            board_[row][col].hasMine = false;
            board_[newRow][newCol].hasMine = true;
        }
    }
}

GameState MinesweeperBoard::getGameState() const
{
    return state_;
}

void MinesweeperBoard::setGameState(GameState state)
{
    switch (state)
    {
    case GameState::RUNNING:
        state_ = GameState::RUNNING;
        break;
    case GameState::FINISHED_LOSS:
        state_ = GameState::FINISHED_LOSS;
        break;
    case GameState::FINISHED_WIN:
        state_ = GameState::FINISHED_WIN;
        break;
    }
}

bool MinesweeperBoard::checkInputRange(int row, int col) const
{
    if (row < 0 || row >= height_ || col < 0 || col >= width_) // - row or col is outside board
    {
        return false;
    }
    return true; // otherwise input correct
}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if (!checkInputRange(row, col))
    {
        return false;
    }
    if (isRevealed(row, col))
    {
        return false;
    }
    if (board_[row][col].hasFlag == false) // - there is no flag on the field
    {
        return false;
    }
    return true;
}

bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (!checkInputRange(row, col)) // - input check
    {
        return false;
    }
    if (board_[row][col].isRevealed == false) // - field was not revealed
    {
        return false;
    }
    return true; // field revealed
}

void MinesweeperBoard::toggleFlag(int row, int col)
{
    if (!checkInputRange(row, col) || isRevealed(row, col) || getGameState() != GameState::RUNNING)
    {
        // doing nothing
    }
    else // toggling
    {
        if (hasFlag(row, col))
        {
            board_[row][col].hasFlag = false; // toggle off
        }
        else
        {
            board_[row][col].hasFlag = true; // toggle on
        }
    }
}

void MinesweeperBoard::revealField(int row, int col)
{
    if (!checkInputRange(row, col) || isRevealed(row, col) || hasFlag(row, col) || getGameState() != GameState::RUNNING)
    {
        // doing nothing
    }
    else
    {
        if (board_[row][col].hasMine == false) // correct deduction
        {
            board_[row][col].isRevealed = true;
            if (checkWin())
            { // check if already won;
                setGameState(GameState::FINISHED_WIN);
            }
        }
        else
        {
            if (isBoardFresh() && mode_ != GameMode::DEBUG) // first action only in normal modes
            {
                relocateMine(row, col); // move the mine
                board_[row][col].isRevealed = true;
            }
            else // bad luck
            {
                board_[row][col].isRevealed = true;
                setGameState(GameState::FINISHED_LOSS);
            }
        }
    }
}

GameState MinesweeperBoard::message() const
{
    GameState state = getGameState();
    switch (state)
    {
    case GameState::FINISHED_LOSS:
        std::cout << "     _____\n"
                  << "    /     \\\n"
                  << "   | () () |\n"
                  << "   |   ^   |\n"
                  << "   |^^^^^^^|\n"
                  << "   |^^^^^^^|\n"
                  << "    \\_____/\n"
                  << "\n"
                  << " B   O   O   M\n"
                  << std::endl;
        break;
    case GameState::FINISHED_WIN:
        std::cout << "Congrats comrade!\n"
                  << "Promoted"
                  << std::endl;
        break;
    case GameState::RUNNING:
        break;
    }
    return state;
}

bool MinesweeperBoard::checkWin() const // if the player won the game (all unrevealed fields have mines)
{
    int unrevealed{0};
    int safe_to_uncover{getBoardHeight() * getBoardWidth() - getMineCount()};
    for (int i = 0; i < getBoardHeight(); i++)
    {
        for (int j = 0; j < getBoardWidth(); j++)
        {
            if (board_[i][j].isRevealed && !board_[i][j].hasMine)
            {
                unrevealed++;
            }
        }
    }
    return (unrevealed == safe_to_uncover);
}

int MinesweeperBoard::countMines(int row, int col) const
{
    if (checkInputRange(row, col) && isRevealed(row, col))
    {
        int count{0};
        for (int i = row - 1; i <= row + 1; i++)
        {
            for (int j = col - 1; j <= col + 1; j++)
            {
                if (i >= 0 && i < getBoardHeight() && j >= 0 && j < getBoardWidth() && board_[i][j].hasMine)
                {
                    count++;
                }
            }
        }
        return count;
    }
    std::cout << -1 << std::endl;
    return -1;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if (!checkInputRange(row, col)) // if row or col is outside board - return '#' character
    {
        return '#';
    }
    if (!isRevealed(row, col))
    {
        if (hasFlag(row, col)) // if the field is not revealed and has a flag - return 'F' character
        {
            return 'F';
        }
        else
        {
            return '_'; // if the field is not revealed and does not have a flag  - return '_' (underscore) character
        }
    }
    else
    {
        if (board_[row][col].hasMine) // if the field is revealed and has mine - return 'x' character
        {
            return 'x';
        }
        else
        {
            if (countMines(row, col) == 0) // if the field is revealed and has 0 mines around - return ' ' (space) character
            {
                return ' ';
            }
            else
            {
                return 48 + countMines(row, col); // if the field is revealed and has some mines around  - return '1' ... '8' (number of mines as a digit)
            }                                     // +48 - numbers in ASCII!
        }
    }
}