////////////////////////////////////// TASK 4: /////////////////////////////////////////
#include "AllTheFunctions.h"

namespace work_with_functions
{
    // рекурсивно считаем "а по модулю b" применительно к размеру массива
    int mod(int a, int b)
    {
        if (a >= b)
            return mod(a - b, b);
        if (a < 0)
            return mod(b + a, b);
        return a;
    }

    void cycleShift(int* arr, const size_t size, const int shift)
    {
        int* copyArr = new int[size];
        for (size_t i = 0; i < size; ++i)
            copyArr[i] = arr[i];

        for (size_t i = 0; i < size; ++i)
            arr[i] = copyArr[mod(i - shift, size)];

        delete[] copyArr;
    }

    void task4()
    {
        cout << "TASK 4\n";

        const size_t SIZE = 10;
        int array[SIZE]{ 17, 53, 20, -43, 11, 48, -22, 14, -32, 35 };

        cout << "Initial array:\n";
        printArray(array, SIZE);

        cout << "Please input an integer number for array cycle shift: ";
        int nShift;
        std::cin >> nShift;

        cycleShift(array, SIZE, nShift);
        cout << "Array after cycle shift:\n";
        printArray(array, SIZE);

        cout << "\n";
    }
}