﻿/* 1.	Создать программу, которая считывает целое число типа int. И поставить «защиту от дурака»: 
        если пользователь вводит что-то кроме одного целочисленного значения, нужно вывести сообщение об ошибке 
        и предложить ввести число еще раз. Пример неправильных введенных строк:
        rbtrb
        nj34njkn
        1n
   2.	Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки и сбрасывает буфер.*/

#include <iostream>

///////////////////// TASK 1

// получаем от пользователя целое число
int getNumber()
{
    std::cout << "Enter an integer number: ";
    int answer;
    std::cin >> answer;

    while (std::cin.fail() || (std::cin.peek() != '\n'))
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Try again, please: ";
        std::cin >> answer;
    }
    std::cin.ignore(32767, '\n');
    return answer;
}

void task1()
{
    std::cout << "Task 1, with check of users input of integer number.\n";
    int result = getNumber();
    std::cout << "Your correct input is: " << result << std::endl << std::endl;
}

///////////////////// TASK 2

std::ostream& endll(std::ostream& out)
{
    out << "\n\n";
    out.flush();
    return out;
}

void task2()
{
    std::cout << "Task 2, with a special manipulator endll.\n";
    std::cout << "Test: " << endll << "Test finished." << endll;
}

int main()
{
    task1();
    task2();
    return 0;
}
