//                      ФАЙЛ С ФУНКЦИЯМИ, ОПРЕДЕЛЯЮЩИМИ ЛОГИКУ ИГРЫ:
#include "Declarations.h"

// проверяет линию на одинаковость всех знаков в ней. Истина, если все знаки одинаковые (кто-то победил)
bool checkLine(const Field& field, size_t start_row, size_t start_column, int delta_row, int delta_column)
{
    size_t current_row = start_row;
    size_t current_column = start_column;
    auto first = field.cells[start_row*field.size + start_column];
    if (first == CellStatus::Empty)
        return false;
    while (current_row < field.size && current_column < field.size && current_row >= 0 && current_column >= 0)
    {
        if (field.cells[current_row* field.size + current_column] != first)
            return false;
        current_row += delta_row;
        current_column += delta_column;
    }
    return true;
}

// макрос для проверки линии и определения победителя, если проверка пройдена. Если проверка не пройдена, ничего не делает.
#define CHECK_LINE(start_row, start_column, delta_row, delta_column) \
        if (checkLine(field, start_row, start_column, delta_row, delta_column)) {\
            outcome.isOver = true; \
            outcome.victor = field.cells[start_row*field.size + start_column] == (CellStatus::X) ? Sign::X : Sign::O; \
            return outcome; \
        }

// проверяет поле на завершение игры - выигрыш по линии или ничью. Возвращает структуру исхода игры.
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
// чтобы макрос, определённый чуть выше, не повлиял на код ниже
#undef CHECK_LINE

// процедура хода пользователя
TurnOutcome processPlayerTurn(GameData& game)
{
    std::cout << "Enter row and column (0 0 to give up): ";
    int row, column;
    std::cin >> row >> column;

    // заканиваем игру, если сдаётся, присваиваем победу компьютеру
    TurnOutcome outcome;
    if (row == 0 && column == 0)
    {
        outcome.isOver = true;
        outcome.isDraw = false;
        outcome.victor = (game.player_sign == Sign::X) ? Sign::O : Sign::X;
        return outcome;
    }
    
    // не сдаётся, значит - ходит
    while (!isCellAvailable(game.field, row - 1, column - 1))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong input, please enter row and column of an empty cell: ";
        std::cin >> row >> column;
    }
    putSign(game.field, game.player_sign, row - 1, column - 1);

    return checkTurnOutcome(game.field);
}

// процедура хода компьютера
TurnOutcome processAITurn(GameData& game)
{
    Sign ai_sign = (game.player_sign == Sign::X) ? Sign::O : Sign::X;
    std::cout << "The field after computer's turn:\n";

    // создаём массив индексов пустых клеток поля:
    const auto n_empty_cells = game.field.size * game.field.size;
    size_t* empty_cells = new size_t[n_empty_cells]{};
    const size_t kInvalidCellIdx = 63580;
    std::fill_n(empty_cells, n_empty_cells, kInvalidCellIdx);

    // заполняем массив индексами, считаем сколько всего пустых клеток
    size_t last_empty_cell_idx = 0;
    for (size_t i = 0; i < n_empty_cells; i++)
    {
        if (game.field.cells[i] == CellStatus::Empty)
        {
            empty_cells[last_empty_cell_idx] = i;
            last_empty_cell_idx++;
        }
    }

    // если это первый ход, ставим знак в центр поля:
    if (last_empty_cell_idx == n_empty_cells)
    {
        putSign(game.field, ai_sign, game.field.size / 2, game.field.size / 2);
        delete[] empty_cells;
        return checkTurnOutcome(game.field);
    }

    TurnOutcome outcome{};
    // для пустых клеток по очереди проверяем, может ли компьютер закончить игру. Если да, то так и ходим
    for (size_t i = 0; i < last_empty_cell_idx; i++)
    {
        size_t target = empty_cells[i];
        // ставим в пустую клетку поля знак, каких ходит компьютер и если это заканчивает игру, выходим из функции
        putSign(game.field, ai_sign, target / game.field.size, target % game.field.size);
        outcome = checkTurnOutcome(game.field);
        if (outcome.isOver)
        {
            delete[] empty_cells;
            return outcome;
        }
        // иначе стираем поставленный знак
        game.field.cells[target] = CellStatus::Empty;
    }
    
    // для пустых клеток по очереди проверяем, может ли игрок на следующем ходе закончить игру. Если да, то ходим, мешая ему
    for (size_t i = 0; i < last_empty_cell_idx; i++)
    {
        size_t target = empty_cells[i];
        // ставим в пустую клетку поля знак, каких ходит игрок и если это заканчивает игру, ставим свой
        putSign(game.field, game.player_sign, target / game.field.size, target % game.field.size);
        outcome = checkTurnOutcome(game.field);
        if (outcome.isOver)  // если этим ходом игрок заканчивает игру, мешаем ему, ставя свой знак в эту клетку
        {
            game.field.cells[target] = (ai_sign == Sign::X) ? CellStatus::X : CellStatus::O;
            delete[] empty_cells;
            return checkTurnOutcome(game.field);
        }
        // иначе стираем поставленный знак
        game.field.cells[target] = CellStatus::Empty;
    }

    // если ситуация стабильна и следующий ход игру не закончит, ставим свой знак в любую пустую клетку
    size_t random_empty_cell = rand() % last_empty_cell_idx;
    size_t target = empty_cells[random_empty_cell];
    putSign(game.field, ai_sign, target / game.field.size, target % game.field.size);
    delete[] empty_cells;
    return checkTurnOutcome(game.field);
}

// игра - ходы крестиков и ноликов пока чей-то ход не завершится ничьей или победой
TurnOutcome runGameLoop(GameData& game)
{
    // создаём два указателя на функции хода - игрока или компьютера
    TurnOutcome (*Xturn)(GameData& game);
    TurnOutcome (*Oturn)(GameData& game);
    // в зависимости от того, кому выпал крестик, определяем, на чей ход указывает каждый указатель
    if (game.player_sign == Sign::X)
    {
        Xturn = processPlayerTurn;
        Oturn = processAITurn;
    }
    else
    {
        Xturn = processAITurn;
        Oturn = processPlayerTurn;
    }

    TurnOutcome outcome{};
    while (true) 
    // цикл игры - сначала ходят крестики, потом нолики, пока какой-то ход не завершит игру
    {
        outcome = Xturn(game);
        printField(game.field);
        if (outcome.isOver)
            return outcome;

        outcome = Oturn(game);
        printField(game.field);
        if (outcome.isOver)
            return outcome;
    }
}