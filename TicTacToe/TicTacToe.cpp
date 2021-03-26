/* Консольная игра "Крестики-Нолики", но на красивом поле и с искусственным интеллектом ;)  */

#include "Declarations.h"
#include <cstdlib>        // для функций выбора случайного числа srand() и rand()
#include <ctime>          // чтобы в randomize опираться на время запуска программы


int main()
{
    //аналог randomize с привязкой ко времени запуска:
    srand(static_cast<unsigned int>(time(0)));
    rand();

    GameData game = game_initialization();       // запрашиваем размер поля, динамически создаём массив нужного размера
    bool shouldExit = false;
    
    while(!shouldExit) 
    {
        clear_field(game.field);
        game.player_sign = getPlayerSign();
        auto outcome = runGameLoop(game);
        printGameOutcome(outcome, game.player_sign);
        shouldExit = !queryPlayAgain();
    }

    game_exit(game);                             // освобождаем память, выделенную под поле
    return 0;
}