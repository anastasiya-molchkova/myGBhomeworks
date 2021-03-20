/* Консольная игра "Крестики-Нолики", но на красивом поле и с искусственным интеллектом ;)  */

#include <iostream>
#include <cstdlib>   // для функций выбора случайного числа srand() и rand()
#include <ctime>     // чтобы в randomize опираться на время запуска программы
#include <string>    // для рисования рамки поля

// возможные состояния клетки игры в крестики-нолики:
enum class CellStatus{Empty = 0, X, O};

using cellSize = size_t;
enum class Colors{Green, Red, Yellow, Blue, Black, White};

struct CellParameters
{
    Colors color;
    cellSize length;
    cellSize width;
};

// поле для игры в крестики-нолики:
struct Field
{
	static const short field_size = 3;               // требует именно static!
	CellParameters cell_data;
	CellStatus cells[field_size][field_size];
};

enum class Sign {O, X};

struct GameData
{
    Field field;
    Sign player_sign;
};

Sign getPlayerSign() 
{
    std::cout << "You are ";
    bool isX = rand() % 2;
    if (isX)
    {
        std::cout << "X\n";
        return Sign::X;
    }
    std::cout << "O\n";
    return Sign::O;
}

bool isCellAvailable(const Field& field, const int row, const int column)
{
    if (row < 0 || column < 0 || row >= field.field_size || column >= field.field_size)
        return false;
    if (field.cells[row][column] != CellStatus::Empty)
        return false;
    return true;
}

void putSign(Field& field, const Sign player_sign, const int row, const int column)
{
    field.cells[row][column] = (player_sign == Sign::X) ? CellStatus::X : CellStatus::O;
}

void processPlayerTurn(Field& field, Sign player_sign) 
{
    std::cout << "Enter row and column: ";
    int row, column;
    std::cin >> row >> column;

    while (!isCellAvailable(field, row - 1, column - 1)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong input, please enter row and column of an empty cell: ";
        std::cin >> row >> column;
    }
    putSign(field, player_sign, row - 1, column - 1);
}

void printField(const Field& field)
{
    std::string frame = "===";
    std::string frame_between = "---";
    for (size_t i = 0; i < field.field_size; ++i)
    {
        frame += "==";
        frame_between += "--";
    }
    std::cout << frame << '\n';
    for (size_t i = 0; i < field.field_size; ++i)
    {
        std::cout << "||";
        for (size_t j = 0; j < field.field_size; ++j)
        {
            switch (field.cells[i][j])
            {
            case CellStatus::Empty:
                std::cout << " ";
                break;
            case CellStatus::X:
                std::cout << "X";
                break;
            case CellStatus::O:
                std::cout << "O";
                break;
            default:
                std::cout << "E";
                break;
            }
            std::cout << "|";
        }
        std::cout << "|\n";
        if (i != field.field_size -1) 
            std::cout << frame_between << '\n';
    }
    std::cout << frame << '\n';
}

void runGameLoop(Sign sign)
{
    GameData game {};
    bool isGameOver = false;
    if (sign == Sign::X)
        while (!isGameOver)
        {
            processPlayerTurn(game.field, sign);
            printField(game.field);
            //computerTurn();
            //printTurnResult();
        }
    else
        while (!isGameOver)
        {
            //computerTurn();
            processPlayerTurn(game.field, sign);
            printField(game.field);
            //printTurnResult();
        }
    //printGameOutcome();
}

bool askQuestion(char positive, char negative) 
{
    char sign{};
    std::cin >> sign;
    sign = tolower(sign);

    while (sign != positive && sign != negative) 
    {
        std::cout << "Wrong input: received '" << sign << "', should be one of " << positive << " or " << negative << "\n";
        std::cin >> sign;
        sign = tolower(sign);
    }
    return sign == positive;
}

bool queryPlayAgain() 
{
    std::cout << "Want to play again? [y or n]: ";
    return askQuestion('y', 'n');
}

int main()
{
    //аналог randomize с привязкой ко времени запуска:
    srand(static_cast<unsigned int>(time(0)));
    rand();

    bool shouldExit = false;
    
    while(!shouldExit) 
    {
        Sign player_sign = getPlayerSign();
        runGameLoop(player_sign);
        //auto outcome = runGameLoop(player_sign);
        //printGameOutcome(outcome, player_sign);
        shouldExit = !queryPlayAgain();
    }

    return 0;
}