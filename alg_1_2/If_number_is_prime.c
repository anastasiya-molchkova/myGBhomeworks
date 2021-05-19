/* Проверяем, простое ли число */

#define _CRT_SECURE_NO_WARNINGS // иначе clang ругается
#include <stdio.h>
#include <locale.h>   // для кириллицы
#include <math.h>     // для квадратного корня

// получаем целое положительное число от пользователя в рамках диапазона 0, max
unsigned get_number()
{
    char text_number[256]; 
    int number = 0;
    do
    {
        printf("Введите целое положительное число больше 1: ");
        scanf("%s", text_number);
        number = atof(text_number);
    } while (number < 2);
    return (unsigned)number;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");  // для кириллицы

    printf("Данная программа проверяет введённое число на простоту.\n\n");

    unsigned number = get_number();

    int is_prime = 1;
    if (number > 2)
    {
        unsigned divider;
	double sqr_root = sqrt(number)

        for (divider = 2; divider <= sqr_root; divider++)
            if (number % divider == 0)
            {
                is_prime = 0;
                break;
            }
     }

    printf("Число %d %sявляется простым\n\n", number, (is_prime)?"":"не ");

    return 0;
}