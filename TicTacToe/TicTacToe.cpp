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
	static const short size = 3;               // требует именно static!
	CellParameters cell_data;
	CellStatus cells[size][size];
};

enum class Sign {O, X};

struct GameData
{
    Field field;
    Sign player_sign;
};

Sign getPlayerSign() 
{
    std::cout << "Your sign is ";
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
    if (row < 0 || column < 0 || row >= field.size || column >= field.size)
        return false;
    if (field.cells[row][column] != CellStatus::Empty)
        return false;
    return true;
}

void putSign(Field& field, const Sign player_sign, const size_t row, const size_t column)
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
    for (size_t i = 0; i < field.size; ++i)
    {
        frame += "==";
        frame_between += "--";
    }
    std::cout << frame << '\n';
    for (size_t i = 0; i < field.size; ++i)
    {
        std::cout << "||";
        for (size_t j = 0; j < field.size; ++j)
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
        if (i != field.size -1) 
            std::cout << frame_between << '\n';
    }
    std::cout << frame << '\n';
}

struct TurnOutcome 
{
    bool isOver;
    Sign victor;
    bool isDraw;
};

bool isDraw(const Field& field) 
{
    for (size_t i = 0; i < field.size; i++) 
        for (size_t j = 0; j < field.size; j++)
            if (field.cells[i][j] == CellStatus::Empty)
                return false;
    return true;
}

bool checkLine(const Field& field, size_t start_row, size_t start_column, int delta_row, int delta_column) 
{
    size_t current_row = start_row;
    size_t current_column = start_column;
    auto first = field.cells[start_row][start_column];
    if (first == CellStatus::Empty) 
        return false;
    while (current_row < field.size && current_column < field.size && current_row >= 0 && current_column >= 0)
    {
        if (field.cells[current_row][current_column] != first)
            return false;
        current_row += delta_row;
        current_column += delta_column;
    }
    return true;
}

#define CHECK_LINE(start_row, start_column, delta_row, delta_column) \
        if (checkLine(field, start_row, start_column, delta_row, delta_column)) {\
            outcome.isOver = true; \
            outcome.victor = field.cells[start_row][start_column] == (CellStatus::X) ? Sign::X : Sign::O; \
            return outcome; \
        }

TurnOutcome checkTurnOutcome(const Field& field) 
{
    TurnOutcome outcome{};

    // проверка по строкам:
    for (size_t row = 0; row < field.size; row++)
        CHECK_LINE(row, 0, 0, 1)
    // проверка по столбцам:
    for (size_t column = 0; column < field.size; column++)
        CHECK_LINE(0, column, 1, 0)
    // проверка двух диагоналей:
    CHECK_LINE(0, 0, 1, 1)
    CHECK_LINE(0, (field.size - 1), 1, -1)

    if (isDraw(field))
    {
        outcome.isDraw = true;
        outcome.isOver = true;
    }

    return outcome;
}

#undef CHECK_LINE

void processAITurn(Field& field, Sign ai_sign)
{
    std::cout << "\nThe field after computer's turn:\n";

    // создаём массив индексов пустых клеток поля:
    const auto n_empty_cells = field.size * field.size;
    size_t empty_cells[n_empty_cells]{};
    const size_t kInvalidCellIdx = 63580;
    std::fill_n(empty_cells, n_empty_cells, kInvalidCellIdx);
    
    // заполняем массив индексами, считаем сколько всего пустых клеток
    size_t last_empty_cell_idx = 0;
    for (size_t i = 0; i < n_empty_cells; i++)
    {
        if (field.cells[i / field.size][i % field.size] == CellStatus::Empty)
        {
            empty_cells[last_empty_cell_idx] = i;
            last_empty_cell_idx++;
        }
    }

    // если это первый ход, ставим знак в центр поля:
    if (last_empty_cell_idx == n_empty_cells)
    {
        putSign(field, ai_sign, field.size/2, field.size / 2);
        return;
    }
    
    for (size_t i = 0; i < last_empty_cell_idx; i++)
    {
        size_t target = empty_cells[i];
        // ставим в пустую клетку поля знак, каких ходит компьютер и если это заканчивает игру, выходим из функции
        putSign(field, ai_sign, target / 3, target % 3);
        auto outcome = checkTurnOutcome(field);
        if (outcome.isOver)
            return;
        // иначе стираем поставленный знак
        field.cells[target / field.size][target % field.size] = CellStatus::Empty;
        
        // ставим в пустую клетку поля знак, каких ходит игрок и если это заканчивает игру, ставим свой
        auto player_sign = (ai_sign == Sign::X) ? Sign::O : Sign::X;
        putSign(field, player_sign, target / 3, target % 3);
        outcome = checkTurnOutcome(field);
        if (outcome.isOver)  // если этим ходом игрок заканчивает игру, мешаем ему, ставя свой знак в эту клетку
        {
            field.cells[target / field.size][target % field.size] = (ai_sign == Sign::X) ? CellStatus::X : CellStatus::O;
            return;
        }
        // иначе стираем поставленный знак
        field.cells[target / field.size][target % field.size] = CellStatus::Empty;
    }
    // если ситуация стабильна и следующий ход игру не закончит, ставим свой знак в любую пустую клетку
    size_t random_empty_cell = rand() % last_empty_cell_idx;
    size_t target = empty_cells[random_empty_cell];
    putSign(field, ai_sign, target / 3, target % 3);
}

void printGameOutcome(const TurnOutcome& outcome, Sign player_sign)
{
    if (outcome.isDraw)
        std::cout << "It's a DRAW, there is no winner.\n\n";
    else if (outcome.victor == player_sign)
        std::cout << "WOW! CONGRATULATIONS! YOU ARE THE WINNER!!!  =) =) =)\n\n";
    else
        std::cout << "AI is a winner... Don't give up! Just try one more time!\n\n";
}

TurnOutcome runGameLoop(Sign player_sign)
{
    GameData game {};
    TurnOutcome outcome{};

    void (*Xturn)(Field&, Sign);
    void (*Oturn)(Field&, Sign);
    if (player_sign == Sign::X)
    {
        Xturn = processPlayerTurn;
        Oturn = processAITurn;
    }
    else
    {
        Xturn = processAITurn;
        Oturn = processPlayerTurn;
    }

    while (true)
    {
        Xturn(game.field, Sign::X);
        printField(game.field);
        outcome = checkTurnOutcome(game.field);
        if (outcome.isOver)
            return outcome;

        Oturn(game.field, Sign::O);
        printField(game.field);
        outcome = checkTurnOutcome(game.field);
        if (outcome.isOver)
            return outcome;
    }
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
    std::cout << "Do you want to play again? [y - yes / n - no]: ";
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
        auto outcome = runGameLoop(player_sign);
        printGameOutcome(outcome, player_sign);
        shouldExit = !queryPlayAgain();
    }

    return 0;
}