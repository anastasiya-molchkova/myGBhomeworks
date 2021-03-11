////////////////////////////////////// TASK 2: /////////////////////////////////////////
#include "AllTheFunctions.h"

namespace work_with_functions
{
    void arrFullfill(int* arr, const size_t size)
    {
        arr[0] = 1;
        for (size_t i = 1; i < size; ++i)
            arr[i] = arr[i - 1] + 3;
    }

    void printArray(const int* arr, const size_t size)
    {
        for (size_t i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

    void task2()
    {
        cout << "TASK 2\n";

        const size_t SIZE = 8;
        int array[SIZE]{};

        cout << "Initial array:\n";
        printArray(array, SIZE);

        arrFullfill(array, SIZE);
        cout << "Final array:\n";
        printArray(array, SIZE);

        cout << "\n";
    }
}
