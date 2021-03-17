/* 1. Описать макрокоманду, проверяющую, входит ли переданное ей число в диапазон от нуля (включительно) до переданного ей второго аргумента (исключительно)
   2. Описать макрокоманду, получающую доступ к элементу двумерного массива (организованного динамически) посредством разыменования указателей
   3* Описать макрокоманду, возвращающую количество элементов локального массива, принимающую на вход ссылку на массив и его тип */

#include <iostream>
// TASK 1:
#define ZERO 0
#define CHECK_LIMIT(NUMB, MAX) ((NUMB >= ZERO && NUMB < MAX)? true : false)

// TASK 2:
#define GET_ELEMENT(ARR, row, col) *(*(ARR + row) + col)

// TASK 3:
#define GET_ARRAY_SIZE(ARR, TYPE) (sizeof(ARR)/sizeof(TYPE))

void task1();
void task2();
void task3();

int main()
{
    /////////////////////////// TASK 1 //////////////////////////////////
    std::cout << "Task 1 check:\n";
    task1();

    /////////////////////////// TASK 2 //////////////////////////////////
    std::cout << "Task 2 check:\n";
    task2();

    /////////////////////////// TASK 3 //////////////////////////////////
    std::cout << "Task 3 check:\n";
    task3();

    return 0;
}

void task1()
{
    int number = 323, upper_limit = 100;
    if (CHECK_LIMIT(number, upper_limit))
        std::cout << "Number " << number << " fits the range from " << ZERO << " to " << upper_limit << '\n';
    else
        std::cout << "Number " << number << " doesn't fit the range from " << ZERO << " to " << upper_limit << "\n\n";
}

void task2()
{
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
            array[i][j] = (i + 1) * 10 + j;
            std::cout << array[i][j] << " ";
            if (j + 1 == M)
                std::cout << '\n';
        }

    // проверяем определённый элемент массива с помощью макроса: 
    size_t x = 1, y = 2;
    std::cout << "Element [" << x << "][" << y << "] = " << GET_ELEMENT(array, x, y) << "\n\n";

    // освобождаем выделенную под массив память:
    for (size_t i = 0; i < N; ++i)
        delete[] array[i];
    delete[] array;
}

void task3()
{
    int array[]{10, 26, 15, 23, 11, 32, 39, 23, 25, 16};
    std::cout << "An array: ";
    for (auto& element : array) 
        std::cout << element << " ";
    std::cout << "\nhas " << GET_ARRAY_SIZE(array, int) << " elements.\n\n";
}