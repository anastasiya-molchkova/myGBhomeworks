/* 1. Написать программу, вычисляющую выражение a * (b + (c / d)) и выводящую результат с плавающей точкой, где a, b, c, d – целочисленные константы;
 * 2. Дано целое число, выведите на экран разницу между этим числом и числом 21. Если же заданное число больше, чем 21, необходимо вывести удвоенную разницу между этим числом и 21. При выполнении задания следует использовать тернарный оператор.
 * 3. Написать программу, вычисляющую выражение из первого задания, а переменные для неё инициализировать в другом файле
 * 4. Описать трёхмерный целочисленный массив, размером 3х3х3, указатель на значения внутри массива и при помощи операции разыменования вывести на экран значение центральной ячейки получившегося куба [1][1][1] */

#include <iostream>
#include "ValuesForTask3.h"

int main()
{
    // TASK 1:
    std::cout << "TASK 1:\n";
    const int a = 10;
    const int b = 17;
    const int c = 21;
    const int d = 32;
    double expressionResult = (static_cast<double>(c) / d);
    expressionResult = a * (b + expressionResult);
    std::cout << "The result of the expression " << a << " * (" << b << " + (" << c << " / " << d << ")) is : " << expressionResult << "\n\n";

    // TASK 2:
    std::cout << "TASK 2:\n";
    const int twentyOne = 21;
    std::cout << "Please enter an integer number: ";
    int number = 0;
    std::cin >> number;
    int difference = twentyOne - number;
    std::cout << "The result of a comparison your number with " << twentyOne << " is " << ((number <= twentyOne) ? difference : 2*(-difference)) << "\n\n";

    // TASK 3:
    std::cout << "TASK 3:\n";
    expressionResult = (static_cast<double>(another_c) / another_d);
    expressionResult = another_a * (another_b + expressionResult);
    std::cout << "The result of the expression " << another_a << " * (" << another_b << " + (" << another_c << " / " << another_d << ")) is : " << expressionResult << "\n\n";

    return 0;
}