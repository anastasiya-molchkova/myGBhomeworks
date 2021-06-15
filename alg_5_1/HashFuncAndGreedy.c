#include <stdio.h>
#include <locale.h>

/////////////////////// ЗАДАНИЕ 1

typedef int hashCode;

// возвращает хэш для переданной строки как сумму кодов её символов
hashCode hashFunctionForText(char* text)
{
    hashCode result = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        result += (hashCode)text[i];
        ++i;
    }
    return result;
}

// задаёт строку и выводит на экран её и её хэш
void task1()
{
    printf("\n1. Получение хэша для строки.\n\n");
    const unsigned int MAX_SIZE = 100;
    char string[MAX_SIZE] = "This is a test string";
    printf("Строка: ");
    puts(string);
    printf("Хэш строки: %d\n\n", hashFunctionForText(string));
}

/////////////////////// ЗАДАНИЕ 2

typedef unsigned int money;

// набирает заданную сумму минимальным количеством монет заданного номинала, используя жадный алгоритм
void task2()
{
    printf("\n2. Набор заданной суммы монетами с помощью жадного алгоритма.\n\n");
    const money sum = 98;
    printf("Сумма: %d\n", sum);

    // задаём упорядоченный по убыванию массив номиналов монет
    const int coins_number = 5;
    const money coins_value[coins_number] = { 50, 10, 5, 2, 1 };
    
    money left_to_collect = sum;
    int max_coin_idx = 0;         // индекс соответствует монете максимального из имеющихся номиналов
    printf("Монеты: ");
    while (left_to_collect > 0)  // набираем монеты, уменьшая оставшуюся для набора сумму, пока не наберём всю
    {
        // если текущий номинал превышает остаток, переходим к следующему, поменьше:
        while (coins_value[max_coin_idx] > left_to_collect)
            ++max_coin_idx;
        
        // выводим на экран номинал очередной монеты и уменьшаем остаток:
        printf("%d ", coins_value[max_coin_idx]);      
        left_to_collect -= coins_value[max_coin_idx];
    }
    printf("\n\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    task2();
    return 0;
}