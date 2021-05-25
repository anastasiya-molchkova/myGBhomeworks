#include <stdio.h>
#include <locale.h>  // для кириллицы
#include <stdlib.h>  // для генерации случайных препятствий в задаче с королём
#include <time.h>    // для генерации случайных препятствий в задаче с королём
#include <string.h>  // для работы со строками

// вспомогательная функция - получаем целое положительное число от пользователя
unsigned get_positive_number(const char* text_to_user)
{
    char text_number[256];
    int number = 0;
    do
    {
        printf("%s", text_to_user);
        scanf("%s", text_number);
        number = atoi(text_number);
    } while (number <= 0);
    return (unsigned)number;
}

///////////////////////////////// ЗАДАНИЕ 1

const int MAX_LENGTH = 100;  // ограничение на длину символьной строки (нуль-терминированного массива символов)

// рекурсивно переводит число в двоичную запись (последовательно деля число на 2 и добавляя остаток от деления в bin_number слева)
int convert_to_bin(int number, char* bin_number, unsigned current_bin_record_length)
{
    if (number == 0)
    {
        puts(bin_number);
        return 0;
    }
    else if (current_bin_record_length == MAX_LENGTH)
    {
        printf("ЧИСЛО СЛИШКОМ ВЕЛИКО ДЛЯ МАКСИМАЛЬНО ВОЗМОЖНОЙ ДВОИЧНОЙ ЗАПИСИ!\n");
        return 1;
    }
    else
    {
        // получаем остаток от деления на 2 в виде символа
        char char_to_add{ ((number % 2) == 0) ? '0' : '1' };
        // смещаем то, что уже есть в двоичной записи на 1 знак вправо:
        ++current_bin_record_length;
        for (int i = (current_bin_record_length - 1); i >= 0; i--)
            bin_number[i + 1] = bin_number[i];
        // добавляем полученный остаток в качестве первого символа двоичной записи
        bin_number[0] = char_to_add;
        convert_to_bin(number/2, bin_number, current_bin_record_length);
    }
}

// Решение первого задания - запрашиваем число и переводим его в двоичную запись
void task1()
{
    printf("1. Перевод числа в двоичную запись.\n");
    int n = get_positive_number("Введите положительное целое число: ");
    printf("Это же число в двоичной записи: ");
    
    char bin_number[MAX_LENGTH] = "";
    unsigned length_of_binary_record = 0;
    
    int result = convert_to_bin(n, bin_number, length_of_binary_record);

    printf("\n\n");
}

///////////////////////////////// ЗАДАНИЕ 2 и 3

// рекурсивная функция возведения числа в степень
unsigned exponentiation(unsigned basis, unsigned index)
{
    if ((basis == 0) || (basis == 1) || (index == 1))
        return basis;
    return basis * exponentiation(basis, index - 1);
}

// рекурсивная функция возведения числа в степень, использующая свойство чётности степени
unsigned exponentiation2(unsigned basis, unsigned index)
{
    if ((basis == 0) || (basis == 1) || (index == 1))
        return basis;
    if (index % 2 == 0)
        return exponentiation(basis * basis, index / 2);
    return basis * exponentiation(basis, index - 1);
}

// решение второго и третьего задания - возведение заданного числа в заданную степень
void task23()
{
    printf("2. Возведение числа в степень.\n");
    unsigned a = get_positive_number("Введите число, которое нужно возвести в степень: ");
    unsigned n = get_positive_number("Введите показатель степени: ");
    printf("Число %d в степени %d: %d", a, n, exponentiation(a, n));
    printf("\n\n");

    printf("3. Возведение числа в степень, используя чётность степени.\n");
    printf("Число %d в степени %d: %d", a, n, exponentiation2(a, n));
    printf("\n\n");
}

///////////////////////////////// ЗАДАНИЕ 4

#define sizeX 5       // размер шахматного поля по горизонтали
#define sizeY 5       // размер шахматного поля по вертикали

// рекурсивное вычисление количества маршрутов до клетки с координатами x и y на поле с препятствиями
int routes_number(int x, int y, int desk[sizeX][sizeY])
{
    if ((x == 0) && (y == 0))     // начальная клетка
        return 0;
    if ((x == 0) || (y == 0))     // клетка по краю поля
        return 1;
    if ((desk[x][y - 1] == 1) && (desk[x - 1][y] == 1)) // обе предыдущие клетки (слева и сверху) - с препятствиями
        return 0;
    if (desk[x][y - 1] == 1)                            // клетка сверху - с препятствием
        return routes_number(x - 1, y, desk);
    if (desk[x - 1][y] == 1)
        return routes_number(x, y - 1, desk);           // клетка слева - с препятствием
    // иначе:
    return routes_number(x - 1, y, desk) + routes_number(x, y - 1, desk);
}

// решение четвёртого задания - нахождение количества маршрутов короля до каждой клетки поля при наличии на нём препятствий
void task4()
{
    printf("4. Подсчёт количества маршрутов короля из угла в угол с условием, что он ходит только вправо и вниз.\n");
    
    // Генерируем и печатаем поле как двумерный массив с 0 и 1: 
    printf("Препятствия на доске расставлены случайным образом и обозначены единицей:\n");
    srand(time(NULL));                 // типа randomize, чтобы с каждым запуском программы генерировались разные числа
    int desk[sizeX][sizeY];            // массив с препятствиями
    for (int x = 0; x < sizeX; ++x)
    {
        for (int y = 0; y < sizeY; ++y)
        {
            desk[x][y] = rand() % 2;
            printf("%7d", desk[x][y]);
        }
        printf("\n");
    }
    if (desk[0][0] == 1)
        printf("Считаем, что клетка старта занята королём ;-)\n");

    // выводим на экран результат как количество маршрутов до каждой клетки поля:
    printf("Количество маршрутов до каждой клетки:\n");
    for (int x = 0; x < sizeX; ++x)
    {
        for (int y = 0; y < sizeY; ++y)
            printf("%7d", routes_number(x, y, desk));
        printf("\n");
    }

    printf("\n\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы

    task1();
    task23();
    task4();

    return 0;
}