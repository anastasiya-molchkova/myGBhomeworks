/* Консольная игра "Крестики-Нолики", но на красивом поле и с искусственным интеллектом ;)  */

#include "Declarations.h"
#include <cstdlib>        // для функций выбора случайного числа srand() и rand()
#include <ctime>          // чтобы в randomize опираться на время запуска программы


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