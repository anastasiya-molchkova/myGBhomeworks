#include <stdio.h>
#include <locale.h>  // для кириллицы
#include <stdlib.h>  // для генерации случайных чисел
#include <math.h>    // для sqrt, fabs, pow

///////////////////////////////// ЗАДАНИЕ 1

// определяем размеры двумерного массива:
#define N 10    // количество строк двумерного массива
#define M 10    // количество столбцов двумерного массива

// содаёт двумерный массив
int** init_array(int** array)
{
    array = (int**)calloc(sizeof(int*), N);
    for (int i = 0; i < N; ++i)
        *(array + i) = (int*)calloc(sizeof(int), M);
    return array;
}

// заполняет массив случайными числами
void fill_array_by_random(int** array, const unsigned max)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            *(*(array + i) + j) = rand() % max;
}

// печатает массив
void print_array(int** array)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
            printf("%4d ", *(*(array + i) + j));
        printf("\n");
    }
}

// меняет местами значения двух чисел
void swap_int(int* number1, int* number2) 
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

// сортирует двумерный массив пузырьковой сортировкой
void bubble_sort(int** array)
{
    // будем получать координаты текущего и следующего элемента массива из счётчика цикла
    int element_row, element_column, next_element_row, next_element_column;

    for (int counter = 0; counter < N * M; ++counter)
        for (int index = 0; index < (N * M - 1); ++index)
        {
            element_row = index / N;
            next_element_row = (index + 1) / N;
            element_column = index % M;
            next_element_column = (index + 1) % M;
            if (array[element_row][element_column] > array[next_element_row][next_element_column])
                swap_int(&array[element_row][element_column], &array[next_element_row][next_element_column]);
        }
}

// Решение первого задания - пузырьковая сортировка двумерного массива
void task1()
{
    printf("1. Пузырьковая сортировка двумерного массива.\n\n");

    int** array = NULL;
    array = init_array(array);
    fill_array_by_random(array, 100);
    printf("Начальный массив:\n");
    print_array(array);

    printf("Отсортированный массив:\n");
    bubble_sort(array);
    print_array(array);
    free(array);

    printf("\n\n");
}

#undef N
#undef M

///////////////////////////////// ЗАДАНИЕ 2

// получает ненулевое число от пользователя
float get_number(const char* text_to_user)
{
    char text_number[256];
    int number = 0;
    do
    {
        printf("%s", text_to_user);
        scanf("%s", text_number);
        number = atof(text_number);
    } while (number == 0);
    return (float)number;
}

#define ELEVEN 11    // количество чисел в последовательности

// получает элементы массива от пользователя
void get_array(float* array)
{
    for (int i = 0; i < ELEVEN; ++i)
        array[i] = get_number("Введите ненулевое число: ");
}

// инвертирует массив
void invert_array(float* array)
{
    for (int i = 0; i < ELEVEN / 2; ++i)
    {
        float temp = array[i];
        array[i] = array[ELEVEN-1-i];
        array[ELEVEN - 1 - i] = temp;
    }
}

// печатает массив
void print_array(const float* array)
{
    for (int i = 0; i < ELEVEN; ++i)
        printf("%.2f  ", array[i]);
    printf("\n");
}

// Решение второго задания - "алгоритм Трабба-Прадо-Кнута"
void task2()
{
    printf("1. Алгоритм Трабба-Прадо-Кнута.\n\n");

    printf("Получение элементов последовательности:\n");
    float array[ELEVEN] = {};
    get_array(array);
    printf("\nПолучена последовательность:\n");
    print_array(array);

    invert_array(array);
    printf("Инвертированная последовательность:\n");
    print_array(array);

    float x;
    for (int i = 0; i < ELEVEN; ++i)
    {
        x = array[i];
        array[i] = sqrt(fabs(x)) + 5 * pow(x, 3);
        if (array[i] > 400)
            printf("Преобразованный  %d-й элемент последовательности %.2f > 400!\n", i+1, array[i]);
    }
    printf("\nПреобразованная оследовательность:\n");
    print_array(array);
    printf("\n\n");
}

#undef ELEVEN

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы

    task1();
    task2();

    return 0;
}