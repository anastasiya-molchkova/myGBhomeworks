#include <stdio.h>
#include <locale.h>  // для кириллицы
#include <stdlib.h>  // для генерации случайных чисел

///////////////////////////////// ЗАДАНИЕ 1

// заполняет массив случайными числами
void fill_array_by_random(int* array, int len, const unsigned max)
{
    for (int i = 0; i < len; ++i)
        array[i] = rand() % max;
}

// печатает массив
void print_array(int* array, int len)
{
    for (int i = 0; i < len; ++i)
        printf("%4d ", array[i]);
    printf("\n");
}

// меняет местами значения двух чисел
void swap(int* number1, int* number2) 
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

// сортирует массив сортировкой вставками
// 1-в-1 функция с урока, можно не проверять
void sort_by_inserts(int* array, int len)
{
    int temp, pos;
    for (int i = 1; i < len; ++i) 
    {
        temp = array[i];
        pos = i - 1;
        while (pos >= 0 && array[pos] > temp) 
        {
            array[pos + 1] = array[pos];
            pos--;
        }
        array[pos + 1] = temp;
    }
}

// сортирует массив быстрой сортировкой (Хоара)
// 1-в-1 функция с урока, можно не проверять
void qsort(int* array, int first, int last)
{
    int i = first;
    int j = last;

    int base_element = array[(first + last) / 2];

    do 
    {
        while (array[i] < base_element) i++;
        while (array[j] > base_element) j--;

        if (i <= j) 
        {
            swap(&array[i], &array[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)  qsort(array, i, last);
    if (first < j) qsort(array, first, j);
}

// ищет элемен-медиану массива, возвращает его индекс
int find_median(int* array, int len)
{
    // проверяем если медиана - первый элемент
    if (((array[0] <= array[len / 2]) && (array[0] >= array[len])) || ((array[0] >= array[len / 2]) && (array[0] <= array[len])))
        return 0;
    // проверяем если медиана - последний элемент
    if (((array[len] <= array[0]) && (array[len] >= array[len/2])) || ((array[len] >= array[0]) && (array[len] <= array[len/2])))
        return len;
    // иначе
    return len/2;
}

// сортирует массив улучшенной быстрой сортировкой
void improved_qsort(int* array, int first, int last)
{
    int len = 1 + last - first;
    if (len <= 10)
        sort_by_inserts(array, len);
    else
    {
        int median = find_median(array, len);
        if (array[median] != array[(first + last) / 2])
            swap(&array[(first + last) / 2], &array[median]);
        qsort(array, first, last);
    }
}

// Решение первого задания - улучшенная быстрая сортировка массива
void task1()
{
    printf("1. Улучшенная быстрая сортировка двумерного массива.\n\n");

    const int array_length = 200;
    int array[array_length];

    fill_array_by_random(array, array_length, 1000);
    printf("Начальный массив:\n");
    print_array(array, array_length);

    printf("Отсортированный массив:\n");
    improved_qsort(array, 0, array_length - 1);
    print_array(array, array_length);

    printf("\n\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы

    task1();

    return 0;
}