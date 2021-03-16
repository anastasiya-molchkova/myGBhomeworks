/* 1. Описать макрокоманду, проверяющую, входит ли переданное ей число в диапазон от нуля (включительно) до переданного ей второго аргумента (исключительно)
   2. Описать макрокоманду, получающую доступ к элементу двумерного массива (организованного динамически) посредством разыменования указателей
   3* Описать макрокоманду, возвращающую количество элементов локального массива, принимающую на вход ссылку на массив и его тип */

#include <iostream>
// TASK 1:
#define ZERO 0
#define CHECK_LIMIT(NUMB, MAX) ((NUMB >= ZERO && NUMB < MAX)? true : false)

// TASK 2:
#define GET_ELEMENT(ARR, COLMNS, row, col) (*((&ARR[0][0])+(row*COLMNS)+col))

int main()
{
    /////////////////////////// TASK 1 //////////////////////////////////
    std::cout << "Task 1 check:\n";
    int number = 323, upper_limit = 100;
    if (CHECK_LIMIT(number, upper_limit))
        std::cout << "Number " << number << " fits the range from " << ZERO << " to " << upper_limit << '\n';
    else
        std::cout << "Number " << number << " doesn't fit the range from " << ZERO << " to " << upper_limit << "\n\n";

    /////////////////////////// TASK 2 //////////////////////////////////
    std::cout << "Task 2 check:\n";
    // будем динамически создавать массив NxM:
    const size_t N = 3;
    const size_t M = 4;
    int** array = new int* [N];
    for (size_t i = 0; i < N; ++i)
        array[i] = new int[M];
    
    // заполняем массив NxM, выводим в виде матрицы:
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
        {
            array[i][j] = (i+1) * 10 + j;
            std::cout << array[i][j] << " ";
            if (j + 1 == M)
                std::cout << '\n';
        }
    
    size_t x = 1, y = 2;
    std::cout << "Element [" << x << "][" << y << "] = " << GET_ELEMENT(array, M, x, y) << "\n\n";

    return 0;
}
