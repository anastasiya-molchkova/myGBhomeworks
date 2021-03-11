////////////////////////////////////// TASK 1: ///////////////////////////////////////// 
#include "AllTheFunctions.h"

namespace work_with_functions
{
    void conversion01(bool* arr, const size_t size)
    {
        for (size_t i = 0; i < size; ++i)
            arr[i] = !arr[i];
    }

    void printArray(const bool* arr, const size_t size)
    {
        for (size_t i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }

    void task1()
    {
        cout << "TASK 1\n";

        const size_t SIZE = 15;
        bool array[SIZE]{ 0,1,0,1,1,1,0,0,1,0,1,1,1,1,0 };

        cout << "Initial array:\n";
        printArray(array, SIZE);

        conversion01(array, SIZE);
        cout << "Final array:\n";
        printArray(array, SIZE);

        cout << "\n";
    }
}