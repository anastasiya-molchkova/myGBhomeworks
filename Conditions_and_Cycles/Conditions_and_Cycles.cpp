/* 1. Написать программу, проверяющую что сумма двух чисел лежит в пределах от 10 до 20 (включительно), если да – вывести true, в противном случае – false;
 * 2. Написать программу, проверяющую, является ли некоторое число - натуральным простым. Простое число - это число, которое делится без остатка только на единицу и себя само.
 * 3. Написать программу, выводящую на экран “истину”, если две целочисленные константы, объявленные в её начале либо равны десяти сами по себе, либо их сумма равна десяти.
 * 4. Написать программу, которая определяет является ли год високосным. Каждый 4-й год является високосным, кроме каждого 100-го, при этом каждый 400-й – високосный. Для проверки работы вывести результаты работы программы в консоль */

#include <iostream>

int main()
{
    // TASK 1:
    std::cout << "TASK 1:\n";
    const int min = 10;
    const int max = 20;
    int number1 = 0;
    int number2 = 0;
    std::cout << "Please enter an integer number: ";
    std::cin >> number1;
    std::cout << "Please enter an integer number: ";
    std::cin >> number2;
    bool sum_check = false;
    if (((number1 + number2) >= min) && ((number1 + number2) <= max))
        sum_check = true;
    std::cout << "The result of sum check is " << std::boolalpha << sum_check << "\n\n";

    // TASK 2:
    std::cout << "TASK 2:\n";
    int number3 = 0;
    std::cout << "Please enter a positive integer number to check for dividers: ";
    std::cin >> number3;
    if (number3 <= 3)
        std::cout << "The number is negative or simple\n\n";
    else // число не меньше 4 - уже достаточно для нормальной проверки
    {
        bool is_simple = true;
        // понятно, что число всегда делится на 1 и само себя, нам нужно понять, есть ли у него другие делители.
        // чтобы это понять, достаточно проверить его делители, не превышающие половины этого числа.
        for (int div = 2; div <= (number3 / 2); ++div)
            if ((number3 % div) == 0)
            {
                is_simple = false;
                break;                              // если нашли хоть один делитель, выходим из цикла
            }
        std::cout << "The number is simple is " << is_simple << "\n\n";
    }

    // TASK 3:
    std::cout << "TASK 3:\n";
    const int ten = 10;
    bool check_for_ten = false;
    if ((number1 == ten) || (number2 == ten) || ((number1 + number2) == ten))
        check_for_ten = true;
    std::cout << "The result of check " << number1 << " and " << number2 << " for ten is " << check_for_ten << "\n\n";

    // TASK 4:
    std::cout << "TASK 4:\n";
    int year = 0;
    std::cout << "Please enter a year: ";
    std::cin >> year;
    bool is_leap_year = false;
    if (year % 400 == 0)
        is_leap_year = true;
    // если не делится на 100 и 400, но делится на 4
    else if ((year % 100 != 0) && (year % 4 == 0))
        is_leap_year = true;
    // иначе не делится на 4 без остатка, остаётся false
    std::cout << "This year is leap is " << is_leap_year << "\n\n";
    
    return 0;
}