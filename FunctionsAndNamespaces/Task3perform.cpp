////////////////////////////////////// TASK 3: /////////////////////////////////////////
#include "AllTheFunctions.h"

namespace work_with_functions
{
    int sumElements(const int* arr, const size_t firstIndex, const size_t lastIndex)
    {
        int sum = 0;
        for (size_t i = firstIndex; i <= lastIndex; ++i)
            sum += arr[i];
        return sum;
    }

    bool checkBalance(const int* arr, const size_t size)
    {
        for (size_t i = 1; i < size; ++i)
            if (sumElements(arr, 0, i - 1) == sumElements(arr, i, size - 1))
            {
                cout << "There is a sum balance in this array!\nLeft array part: ";
                printArray(arr, i);
                cout << "and right array part: ";
                printArray(arr + i, size - i);
                cout << "are equal by sum of elements.\n\n";
                return true;
            }
        return false;
    }

    void task3()
    {
        cout << "TASK 3\n";

        int sizeMayBeWrong = 0;
        do
        {
            cout << "Please input a positive integer array size:\n";
            std::cin >> sizeMayBeWrong;

        } while (sizeMayBeWrong <= 0);
        size_t size = static_cast<size_t>(sizeMayBeWrong);

        int* array = new int[size];
        cout << "Please enter all the array elements now:\n";
        for (size_t i = 0; i < size; ++i)
            std::cin >> array[i];

        cout << "The given array:\n";
        printArray(array, size);

        if (checkBalance(array, size) == false)
            cout << "There is no sum balance in this array.\n\n";

        delete[] array;
    }
}