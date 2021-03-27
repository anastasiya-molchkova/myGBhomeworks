//                      ‘ј…Ћ — ‘”Ќ ÷»яћ» ƒЋя ¬«ј»ћќƒ≈…—“¬»я — ѕќЋ№«ќ¬ј“≈Ћ≈ћ:
#include "Declarations.h"

// случайным образом определ€ет знак, которым играет игрок
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

// получает размер игрового пол€ от пользовател€
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

// получает от пользовател€ ответ (принимаетс€ всего два варианта ответа)
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

// узнаЄт у пользовател€, хочет ли он сыграть ещЄ раз
bool queryPlayAgain()
{
    std::cout << "Do you want to play again? [y - yes / n - no]: ";
    return askQuestion('y', 'n');
}

// выводит на экран результат игры
void printGameOutcome(const TurnOutcome& outcome, Sign player_sign)
{
    if (outcome.isDraw)
        std::cout << "It's a DRAW, there is no winner.\n\n";
    else if (outcome.victor == player_sign)
        std::cout << "WOW! CONGRATULATIONS! YOU ARE THE WINNER!!!  =) =) =)\n\n";
    else
        std::cout << "AI is a winner... Don't give up! Just try one more time!\n\n";
}