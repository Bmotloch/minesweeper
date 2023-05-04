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

void MinesweeperBoard::debug_display() const
{
    std::cout << "       ";
    for (int i = 0; i < getBoardWidth(); i++)
    {
        std::cout << "   " << i << "   ";
    }
    std::cout << std::endl;
    for (int i = 0; i < getBoardHeight(); i++)
    {
        std::cout << "   " << i << "   ";
        for (int j = 0; j < getBoardWidth(); j++)
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
            if(checkWin()){// check if already won;
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
        std::cout << "Better luck next ti...oh, right :/" << std::endl;
        break;
    case GameState::FINISHED_WIN:
        std::cout << "Congrats comrade!" << std::endl;
        break;
    case GameState::RUNNING:
        break;
    }
    return state;
}

bool MinesweeperBoard::checkWin() // if the player won the game (all unrevealed fields have mines)
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
    return(unrevealed==safe_to_uncover);
}