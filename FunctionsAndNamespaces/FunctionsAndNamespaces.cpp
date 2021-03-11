﻿/* 1) Задать целочисленный массив, состоящий из элементов 0 и 1. Написать функцию, заменяющую в принятом массиве 0 на 1, 1 на 0 без применения if-else, switch, () ? :
*  2) Задать пустой целочисленный массив размером 8. Написать функцию, которая с помощью цикла заполнит его значениями 1 4 7 10 13 16 19 22
*  3) Написать функцию, в которую передается не пустой одномерный целочисленный массив, функция должна вернуть истину если в массиве есть место, в котором сумма левой и правой части массива равны.
*  4) Написать функцию, которой на вход подаётся одномерный массив и число n, функция должна циклически сместить все элементы массива на n позиций. 
** 5) Написать функцию из первого задания так, чтобы она работала с аргументом переменной длины.
** 6) Написать все функции в отдельных файлах в одном пространстве имён, вызвать их на исполнение в основном файле программы используя указатели на функции.
*/

#include <iostream>
#include <cstdarg>        // для работы с эллипсисом (variable length argument)

////////////////////////////////////// TASK 1: ///////////////////////////////////////// 
void conversion01(bool* arr, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
        arr[i] = !arr[i];
}

void printArray(const bool* arr, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

void task1()
{
    std::cout << "TASK 1\n";

    const size_t SIZE = 15;
    bool array[SIZE]{ 0,1,0,1,1,1,0,0,1,0,1,1,1,1,0 };

    std::cout << "Initial array:\n";
    printArray(array, SIZE);

    conversion01(array, SIZE);
    std::cout << "Final array:\n";
    printArray(array, SIZE);

    std::cout << "\n";
}

////////////////////////////////////// TASK 2: /////////////////////////////////////////
void arrFullfill(int* arr, const size_t size)
{
    arr[0] = 1;
    for (size_t i = 1; i < size; ++i)
        arr[i] = arr[i-1] + 3;
}

void printArray(const int* arr, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

void task2()
{
    std::cout << "TASK 2\n";

    const size_t SIZE = 8;
    int array[SIZE]{};

    std::cout << "Initial array:\n";
    printArray(array, SIZE);

    arrFullfill(array, SIZE);
    std::cout << "Final array:\n";
    printArray(array, SIZE);

    std::cout << "\n";
}

////////////////////////////////////// TASK 3: /////////////////////////////////////////
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
            std::cout << "There is a sum balance in this array!\nLeft array part: ";
            printArray(arr, i);
            std::cout << "and right array part: ";
            printArray(arr + i, size - i);
            std::cout << "are equal by sum of elements.\n\n";
            return true;
        }
    return false;
}

void task3()
{
    std::cout << "TASK 3\n";

    int sizeMayBeWrong = 0;
    do
    {
        std::cout << "Please input a positive integer array size:\n";
        std::cin >> sizeMayBeWrong;

    } while (sizeMayBeWrong <= 0);
    size_t size = static_cast<size_t>(sizeMayBeWrong);

    int* array = new int[size];
    std::cout << "Please enter all the array elements now:\n";
    for (size_t i = 0; i < size; ++i)
        std::cin >> array[i];

    std::cout << "The given array:\n";
    printArray(array, size);

    if (checkBalance(array, size) == false)
        std::cout << "There is no sum balance in this array.\n\n";

    delete[] array;
}

////////////////////////////////////// TASK 4: /////////////////////////////////////////
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
    std::cout << "TASK 4\n";

    const size_t SIZE = 10;
    int array[SIZE]{17, 53, 20, -43, 11, 48, -22, 14, -32, 35};

    std::cout << "Initial array:\n";
    printArray(array, SIZE);

    std::cout << "Please input an integer number for array cycle shift: ";
    int nShift;
    std::cin >> nShift;

    cycleShift(array, SIZE, nShift);
    std::cout << "Array after cycle shift:\n";
    printArray(array, SIZE);

    std::cout << "\n";
}

////////////////////////////////////// TASK 5: ///////////////////////////////////////// 
// функция будет возвращать указатель на первый элемент массива, созданного из переданных аргументов
bool * conversion01withVa(const size_t size, ...)
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
    std::cout << "TASK 5\n";

    const size_t SIZE = 15;
    std::cout << "Initial array:\n0 1 0 1 1 1 0 0 1 0 1 1 1 1 0\n";

    bool* result = conversion01withVa(SIZE, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0);

    std::cout << "Final array:\n";
    printArray(result, SIZE);
    std::cout << "\n";

    delete [] result;
}

int main()
{
    task1();
    task2();
    task3();
    task4();
    task5();
    return 0;
}