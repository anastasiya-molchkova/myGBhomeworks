/* 1. Описать макрокоманду, проверяющую, входит ли переданное ей число в диапазон от нуля (включительно) до переданного ей второго аргумента (исключительно)
   2. Описать макрокоманду, получающую доступ к элементу двумерного массива (организованного динамически) посредством разыменования указателей
   3* Описать макрокоманду, возвращающую количество элементов локального массива, принимающую на вход ссылку на массив и его тип */

#include <iostream>
// TASK 1:
#define ZERO 0
#define CHECK_LIMIT(NUMB, MAX) ((NUMB >= ZERO && NUMB < MAX)? true : false)

int main()
{
    std::cout << "Task 1 check:\n";
    int number = 323, upper_limit = 100;
    if (CHECK_LIMIT(number, upper_limit))
        std::cout << "Number " << number << " fits the range from " << ZERO << " to " << upper_limit << '\n';
    else 
        std::cout << "Number " << number << " doesn't fit the range from " << ZERO << " to " << upper_limit << '\n';
    
    
    return 0;
}
