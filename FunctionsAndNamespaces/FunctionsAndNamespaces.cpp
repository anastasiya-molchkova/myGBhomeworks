/* 1) Задать целочисленный массив, состоящий из элементов 0 и 1. Например: [ 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 ]. Написать функцию, заменяющую в принятом массиве 0 на 1, 1 на 0 (** без применения if-else, switch, () ? :);
*  2) Задать пустой целочисленный массив размером 8. Написать функцию, которая с помощью цикла заполнит его значениями 1 4 7 10 13 16 19 22;
*  3) Написать функцию, в которую передается не пустой одномерный целочисленный массив, функция должна вернуть истину если в массиве есть место, в котором сумма левой и правой части массива равны.
*  4) Написать функцию, которой на вход подаётся одномерный массив и число n (может быть положительным, или отрицательным), при этом функция должна циклически сместить все элементы массива на n позиций. 
** 5) Написать функцию из первого задания так, чтобы она работала с аргументом переменной длины.
** 6) Написать все функции в отдельных файлах в одном пространстве имён, вызвать их на исполнение в основном файле программы используя указатели на функции.
*/

#include <iostream>

////////////////////////////////////// TASK 1: ///////////////////////////////////////// 
void conversion01(bool* arr, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
        arr[i] = !arr[i];
}

void printArray(bool* arr, const size_t size)
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

void printArray(int* arr, const size_t size)
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

int main()
{
    task1();
    task2();
    return 0;
}
