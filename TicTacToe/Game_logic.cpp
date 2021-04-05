//                      ���� � ���������, ������������� ������ ����:
#include "Declarations.h"

// ��������� ����� �� ������������ ���� ������ � ���. ������, ���� ��� ����� ���������� (���-�� �������)
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

// ������ ��� �������� ����� � ����������� ����������, ���� �������� ��������. ���� �������� �� ��������, ������ �� ������.
#define CHECK_LINE(start_row, start_column, delta_row, delta_column) \
        if (checkLine(field, start_row, start_column, delta_row, delta_column)) {\
            outcome.isOver = true; \
            outcome.victor = field.cells[start_row*field.size + start_column] == (CellStatus::X) ? Sign::X : Sign::O; \
            return outcome; \
        }

// ��������� ���� �� ���������� ���� - ������� �� ����� ��� �����. ���������� ��������� ������ ����.
TurnOutcome checkTurnOutcome(const Field& field)
{
    TurnOutcome outcome{};

    // �������� �� �������:
    for (size_t row = 0; row < field.size; row++)
        CHECK_LINE(row, 0, 0, 1)
    // �������� �� ��������:
    for (size_t column = 0; column < field.size; column++)
        CHECK_LINE(0, column, 1, 0)
    // �������� ���� ����������:
    CHECK_LINE(0, 0, 1, 1)
    CHECK_LINE(0, (field.size - 1), 1, -1)

    if (isDraw(field))
    {
        outcome.isDraw = true;
        outcome.isOver = true;
    }
    return outcome;
}
// ����� ������, ����������� ���� ����, �� ������� �� ��� ����
#undef CHECK_LINE

// ��������� ���� ������������
TurnOutcome processPlayerTurn(GameData& game)
{
    std::cout << "Enter row and column (0 0 to give up): ";
    int row, column;
    std::cin >> row >> column;

    // ���������� ����, ���� ������, ����������� ������ ����������
    TurnOutcome outcome;
    if (row == 0 && column == 0)
    {
        outcome.isOver = true;
        outcome.isDraw = false;
        outcome.victor = (game.player_sign == Sign::X) ? Sign::O : Sign::X;
        return outcome;
    }
    
    // �� ������, ������ - �����
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

// ��������� ���� ����������
TurnOutcome processAITurn(GameData& game)
{
    Sign ai_sign = (game.player_sign == Sign::X) ? Sign::O : Sign::X;
    std::cout << "The field after computer's turn:\n";

    // ������ ������ �������� ������ ������ ����:
    const auto n_empty_cells = game.field.size * game.field.size;
    size_t* empty_cells = new size_t[n_empty_cells]{};
    const size_t kInvalidCellIdx = 63580;
    std::fill_n(empty_cells, n_empty_cells, kInvalidCellIdx);

    // ��������� ������ ���������, ������� ������� ����� ������ ������
    size_t last_empty_cell_idx = 0;
    for (size_t i = 0; i < n_empty_cells; i++)
    {
        if (game.field.cells[i] == CellStatus::Empty)
        {
            empty_cells[last_empty_cell_idx] = i;
            last_empty_cell_idx++;
        }
    }

    // ���� ��� ������ ���, ������ ���� � ����� ����:
    if (last_empty_cell_idx == n_empty_cells)
    {
        putSign(game.field, ai_sign, game.field.size / 2, game.field.size / 2);
        delete[] empty_cells;
        return checkTurnOutcome(game.field);
    }

    TurnOutcome outcome{};
    // ��� ������ ������ �� ������� ���������, ����� �� ��������� ��������� ����. ���� ��, �� ��� � �����
    for (size_t i = 0; i < last_empty_cell_idx; i++)
    {
        size_t target = empty_cells[i];
        // ������ � ������ ������ ���� ����, ����� ����� ��������� � ���� ��� ����������� ����, ������� �� �������
        putSign(game.field, ai_sign, target / game.field.size, target % game.field.size);
        outcome = checkTurnOutcome(game.field);
        if (outcome.isOver)
        {
            delete[] empty_cells;
            return outcome;
        }
        // ����� ������� ������������ ����
        game.field.cells[target] = CellStatus::Empty;
    }
    
    // ��� ������ ������ �� ������� ���������, ����� �� ����� �� ��������� ���� ��������� ����. ���� ��, �� �����, ����� ���
    for (size_t i = 0; i < last_empty_cell_idx; i++)
    {
        size_t target = empty_cells[i];
        // ������ � ������ ������ ���� ����, ����� ����� ����� � ���� ��� ����������� ����, ������ ����
        putSign(game.field, game.player_sign, target / game.field.size, target % game.field.size);
        outcome = checkTurnOutcome(game.field);
        if (outcome.isOver)  // ���� ���� ����� ����� ����������� ����, ������ ���, ����� ���� ���� � ��� ������
        {
            game.field.cells[target] = (ai_sign == Sign::X) ? CellStatus::X : CellStatus::O;
            delete[] empty_cells;
            return checkTurnOutcome(game.field);
        }
        // ����� ������� ������������ ����
        game.field.cells[target] = CellStatus::Empty;
    }

    // ���� �������� ��������� � ��������� ��� ���� �� ��������, ������ ���� ���� � ����� ������ ������
    size_t random_empty_cell = rand() % last_empty_cell_idx;
    size_t target = empty_cells[random_empty_cell];
    putSign(game.field, ai_sign, target / game.field.size, target % game.field.size);
    delete[] empty_cells;
    return checkTurnOutcome(game.field);
}

// ���� - ���� ��������� � ������� ���� ���-�� ��� �� ���������� ������ ��� �������
TurnOutcome runGameLoop(GameData& game)
{
    // ������ ��� ��������� �� ������� ���� - ������ ��� ����������
    TurnOutcome (*Xturn)(GameData& game);
    TurnOutcome (*Oturn)(GameData& game);
    // � ����������� �� ����, ���� ����� �������, ����������, �� ��� ��� ��������� ������ ���������
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
    // ���� ���� - ������� ����� ��������, ����� ������, ���� �����-�� ��� �� �������� ����
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