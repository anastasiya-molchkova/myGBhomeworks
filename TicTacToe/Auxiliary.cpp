#include "Declarations.h"

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

bool isDraw(const Field& field)
{
    for (size_t i = 0; i < field.size; i++)
        for (size_t j = 0; j < field.size; j++)
            if (field.cells[i][j] == CellStatus::Empty)
                return false;
    return true;
}