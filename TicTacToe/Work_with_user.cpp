//                      ���� � ��������� ��� �������������� � �������������:
#include "Declarations.h"

// ��������� ������� ���������� ����, ������� ������ �����
Sign getPlayerSign()
{
    std::cout << "\nYour sign is ";
    bool isX = rand() % 2;
    if (isX)
    {
        std::cout << "X\n";
        return Sign::X;
    }
    std::cout << "O\n";
    return Sign::O;
}

// �������� ������ �������� ���� �� ������������
size_t getSize()
{
    std::cout << "Please input the field size: ";
    int answer;
    std::cin >> answer;
    const size_t min_size = 3;
    const size_t max_size = 20;
    while (std::cin.fail() || answer < min_size || answer > max_size)
    {

        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Please try to input the field size again, it should be from " << min_size << " to " << max_size << ": ";
        std::cin >> answer;
    }
    std::cin.ignore(32767, '\n');
    return static_cast<size_t>(answer);
}

// ����� � ������������, ����� �� �� ������� ��� ���
bool queryPlayAgain()
{
    std::cout << "Do you want to play again? [y - yes / n - no]: ";
    char yes{ 'y' }, no{ 'n' }, sign{};
    std::cin >> sign;
    sign = tolower(sign);
    while (sign != yes && sign != no)
    {
        std::cout << "Wrong input: received '" << sign << "', should be one of " << yes << " or " << no << "\n";
        std::cin >> sign;
        sign = tolower(sign);
    }
    return (sign == yes);
}

// ������� �� ����� ��������� ����
void printGameOutcome(const TurnOutcome& outcome, Sign player_sign)
{
    if (outcome.isDraw)
        std::cout << "It's a DRAW, there is no winner.\n\n";
    else if (outcome.victor == player_sign)
        std::cout << "WOW! CONGRATULATIONS! YOU ARE THE WINNER!!!  =) =) =)\n\n";
    else
        std::cout << "AI is a winner... Don't give up! Just try one more time!\n\n";
}