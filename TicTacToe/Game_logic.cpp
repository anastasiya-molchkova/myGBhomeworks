#include <iostream>
#include "Declarations.h"

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

#define CHECK_LINE(start_row, start_column, delta_row, delta_column) \
        if (checkLine(field, start_row, start_column, delta_row, delta_column)) {\
            outcome.isOver = true; \
            outcome.victor = field.cells[start_row*field.size + start_column] == (CellStatus::X) ? Sign::X : Sign::O; \
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

void processAITurn(Field& field, Sign ai_sign)
{
    std::cout << "The field after computer's turn:\n";

    // создаём массив индексов пустых клеток поля:
    const auto n_empty_cells = field.size * field.size;
    size_t* empty_cells = new size_t[n_empty_cells]{};
    const size_t kInvalidCellIdx = 63580;
    std::fill_n(empty_cells, n_empty_cells, kInvalidCellIdx);

    // заполняем массив индексами, считаем сколько всего пустых клеток
    size_t last_empty_cell_idx = 0;
    for (size_t i = 0; i < n_empty_cells; i++)
    {
        if (field.cells[i] == CellStatus::Empty)
        {
            empty_cells[last_empty_cell_idx] = i;
            last_empty_cell_idx++;
        }
    }

    // если это первый ход, ставим знак в центр поля:
    if (last_empty_cell_idx == n_empty_cells)
    {
        putSign(field, ai_sign, field.size / 2, field.size / 2);
        delete[] empty_cells;
        return;
    }

    for (size_t i = 0; i < last_empty_cell_idx; i++)
    {
        size_t target = empty_cells[i];
        // ставим в пустую клетку поля знак, каких ходит компьютер и если это заканчивает игру, выходим из функции
        putSign(field, ai_sign, target / field.size, target % field.size);
        auto outcome = checkTurnOutcome(field);
        if (outcome.isOver)
        {
            delete[] empty_cells;
            return;
        }
        // иначе стираем поставленный знак
        field.cells[target] = CellStatus::Empty;

        // ставим в пустую клетку поля знак, каких ходит игрок и если это заканчивает игру, ставим свой
        auto player_sign = (ai_sign == Sign::X) ? Sign::O : Sign::X;
        putSign(field, player_sign, target / field.size, target % field.size);
        outcome = checkTurnOutcome(field);
        if (outcome.isOver)  // если этим ходом игрок заканчивает игру, мешаем ему, ставя свой знак в эту клетку
        {
            field.cells[target] = (ai_sign == Sign::X) ? CellStatus::X : CellStatus::O;
            delete[] empty_cells;
            return;
        }
        // иначе стираем поставленный знак
        field.cells[target] = CellStatus::Empty;
    }
    // если ситуация стабильна и следующий ход игру не закончит, ставим свой знак в любую пустую клетку
    size_t random_empty_cell = rand() % last_empty_cell_idx;
    size_t target = empty_cells[random_empty_cell];
    putSign(field, ai_sign, target / field.size, target % field.size);
    delete[] empty_cells;
}

TurnOutcome runGameLoop(GameData& game)
{
    TurnOutcome outcome{};

    void (*Xturn)(Field&, Sign);
    void (*Oturn)(Field&, Sign);
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