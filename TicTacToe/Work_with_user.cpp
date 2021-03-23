#include <iostream>
#include <string>          // для рисования рамки поля
#include "Declarations.h"

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

size_t getSize()
{
    std::cout << "Please input the field size: ";
    int answer;
    std::cin >> answer;
    while (std::cin.fail() || answer <= 0 || answer > 50)
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Please try to input the field size again: ";
        std::cin >> answer;
    }
    std::cin.ignore(32767, '\n');
    return static_cast<size_t>(answer);
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
        if (i != field.size - 1)
            std::cout << frame_between << '\n';
    }
    std::cout << frame << '\n';
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