//                      ���� �� ���������������� ���������:
#include "Declarations.h"

// ���������, ����� �� ������� ���� � ������ � ��������� ������������ (������� �� 0)
bool isCellAvailable(const Field& field, const int row, const int column)
{
    if (row < 0 || column < 0 || row >= field.size || column >= field.size)
        return false;
    if (field.cells[row*field.size + column] != CellStatus::Empty)
        return false;
    return true;
}

// ������ ������������ ���� � ��������� ������ � ��������� ������������
void putSign(Field& field, const Sign sign, const size_t row, const size_t column)
{
    field.cells[row*field.size + column] = (sign == Sign::X) ? CellStatus::X : CellStatus::O;
}

// ���������, ��� ����� ������ ���
bool isDraw(const Field& field)
{
    for (size_t i = 0; i < field.size; i++)
        for (size_t j = 0; j < field.size; j++)
            if (field.cells[i*field.size + j] == CellStatus::Empty)
                return false;
    return true;
}

// �������� ���������� ������ ������ �������� ����
void print_field_coordinates(const size_t field_size)
{
    std::string frame_between{};
    for (size_t i = 0; i < field_size; ++i)
        frame_between += "------";

    std::cout << "field coordinates:\n";
    for (size_t i = 0; i < field_size; ++i)
    {
        for (size_t j = 0; j < field_size; ++j)
        {
            std::cout << std::setw(2) << std::right << i + 1 << " " << std::setw(2) << std::left << j + 1;
            if (j + 1 < field_size)
                std::cout << "|";
        }
        if (i + 1 < field_size)
            std::cout << '\n' << frame_between << '\n';
    }
    std::cout << "\n\n";
}

// ����������� ������ ������� ����, ���������� ������ ���� � ������������
GameData game_initialization()
{
    GameData game{};
    auto field_size = getSize();
    game.field.size = field_size;
    game.field.cells = new CellStatus[field_size * field_size];
    print_field_coordinates(field_size);
    return game;
}

// ������� ��� ������ �������� ���� ��� ���������� ����� ����
void clear_field(Field& field)
{
    for (auto i = 0; i < field.size * field.size; ++i)
        field.cells[i] = CellStatus::Empty;
}

// �������� ������� ��������� �������� ����
void printField(const Field& field)
{
    std::string frame = "   ";             // ��������� ���������� ��� ����� ����� � ������ ����
    std::string frame_between = "---";     // ��������� ���������� ��� ����� ����� �������� ����
    std::cout << "    ";
    // ������ ����� � �������� ������ ��������:
    for (size_t i = 0; i < field.size; ++i) 
    {
        // �������� ������ ��������
        std::cout << std::setw(4) << std::left << i + 1;
        frame += "====";
        frame_between += "----";
    }
    std::cout << '\n' << frame << '\n';
    for (size_t i = 0; i < field.size; ++i)
    // �������� ���� �� �������, i - ����� ������
    {
        // �������� ������ �����
        std::cout << std::setw(2) << std::left << i + 1 << "|";
        for (size_t j = 0; j < field.size; ++j)
        {
            // j - ����� �������
            switch (field.cells[i * field.size + j])
            { // �������� ���������� ������ ������
            case CellStatus::Empty:
                std::cout << "   |";
                break;
            case CellStatus::X:
                std::cout << " \x1b[31mX \x1b[0;0m|";    // �������� ������� ������� ������
                break;
            case CellStatus::O:
                std::cout << " \x1b[34mO \x1b[0;0m|";    // �������� ����� ����� ������
                break;
            }
        }
        // ��������� ������ ���� ������������ ����
        std::cout << '\n';
        if (i < field.size - 1)
            std::cout << frame_between << '\n';
    }
    std::cout << frame << '\n';
}

// ����������� ������, ���������� ��� ���� ��� ������������� ����
void game_exit(GameData& game)
{
    delete[] game.field.cells;
}