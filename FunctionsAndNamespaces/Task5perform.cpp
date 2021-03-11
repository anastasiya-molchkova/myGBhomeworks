////////////////////////////////////// TASK 5: ///////////////////////////////////////// 
#include <cstdarg>              // для работы с эллипсисом (variable length argument)
#include "AllTheFunctions.h"

namespace work_with_functions
{
    // функция будет возвращать указатель на первый элемент массива, созданного из переданных аргументов
    bool* conversion01withVa(const size_t size, ...)
    {
        bool* new_array = new bool[size];   // создадим динамический массив, который заполним изменёнными переданными аргументами

        va_list list;
        va_start(list, size);

        for (size_t i = 0; i < size; ++i)
            new_array[i] = !va_arg(list, bool);

        va_end(list);
        return new_array;
    }

    // реализация пятого задания - сделать конвертацию 0 в 1 и наоборот, передавая в функцию список элементов массива вместо массива
    void task5()
    {
        cout << "TASK 5\n";

        const size_t SIZE = 15;
        cout << "Initial array:\n0 1 0 1 1 1 0 0 1 0 1 1 1 1 0\n";

        bool* result = conversion01withVa(SIZE, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0);

        cout << "Final array:\n";
        printArray(result, SIZE);
        cout << "\n";

        delete[] result;
    }
}