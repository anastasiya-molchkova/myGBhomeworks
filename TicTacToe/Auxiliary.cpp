#include "Declarations.h"

bool isCellAvailable(const Field& field, const int row, const int column)
{
    if (row < 0 || column < 0 || row >= field.size || column >= field.size)
        return false;
    if (field.cells[row*field.size + column] != CellStatus::Empty)
        return false;
    return true;
}

void putSign(Field& field, const Sign player_sign, const size_t row, const size_t column)
{
    field.cells[row*field.size + column] = (player_sign == Sign::X) ? CellStatus::X : CellStatus::O;
}

bool isDraw(const Field& field)
{
    for (size_t i = 0; i < field.size; i++)
        for (size_t j = 0; j < field.size; j++)
            if (field.cells[i*field.size + j] == CellStatus::Empty)
                return false;
    return true;
}

GameData game_initialization()
{
    GameData game{};
    std::cout << "===========================WELCOME TO TIC-TAC-TOE GAME!===========================\n";
    auto field_size = getSize();
    game.field.size = field_size;
    game.field.cells = new CellStatus[field_size * field_size];

    std::string frame_between{};
    for (size_t i = 0; i < field_size; ++i)
        frame_between += "------";
    
    std::cout << "field coordinates:\n";
    for (size_t i = 0; i < field_size; ++i)
        for (size_t j = 0; j < field_size; ++j)
        {
            std::cout << i + 1 << " " << j + 1;
            if (j + 1 < field_size)
                std::cout << " | ";
            else if (i + 1 < field_size)
                std::cout << '\n' << frame_between << '\n';
        }
    std::cout << "\n\n";

    return game;
}

void clear_field(Field& field)
{
    for (auto i = 0; i < field.size * field.size; ++i)
        field.cells[i] = CellStatus::Empty;
}

void game_exit(GameData& game)
{
    delete[] game.field.cells;
}