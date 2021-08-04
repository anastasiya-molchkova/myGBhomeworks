/* 1.	Добавить в контейнерный класс, который был написан в этом уроке, методы:
   ●	для удаления последнего элемента массива (аналог функции pop_back() в векторах)
   ●	для удаления первого элемента массива (аналог pop_front() в векторах)
   ●	для сортировки массива
   ●	для вывода на экран элементов.
   2.	Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать максимально быстрый алгоритм.*/

//////////////////// TASK1
#include "ArrayInt.h"

void task1()
{
    std::cout << "TASK1 with artificial vector\n";
    ArrayInt vector;
    vector.push_back(2);
    vector.push_back(1);
    vector.push_back(5);
    vector.push_back(9);
    vector.push_back(-4);
    vector.push_back(6);

    vector.insertBefore(7, 2);
    vector.print();

    std::cout << vector.pop_back() << std::endl;
    vector.print();
    vector.sort();
    vector.print();
    std::cout << vector.pop_front() << std::endl;
    vector.print();
    std::cout << std::endl;
}

//////////////////// TASK2
#include <vector>

void task2()
{
    std::cout << "TASK2 with different values in vector\n";

    // тестовый вектор с неуникальными числами:
    std::vector <int> all_numbers{ 323, 28, 237, 34, 948, 32, 323, 372, 219, 48, 948, 28, 34, 948, 323, 32, 28, 372, 219, 948 };
    
    // будем идти по вектору всех чисел, добавляя не повторяющиеся в вектор с уникальными числами
    // размер этого вектора будет нужным нам количеством неповторяющихся чисел
    std::vector <int> unique_numbers{};

    for (const auto& number : all_numbers)
    {
        bool number_is_unique = true;
        for (const auto& uniq_number : unique_numbers)
        {
            if (number == uniq_number)
            {
                number_is_unique = false;
                break;
            }
        }
        if (number_is_unique)
            unique_numbers.push_back(number);
        /* как вариант можно было бы добавлять значение, вставляя его так, 
        чтобы вектор с уникальными значениями оставался упорядоченным (сортировка вставками).
        Тогда при проверке очередного числа мы бы сравнивали его не со всеми уникальными, 
        а только пока не найдём большее число. 
        ...Но я подумала, что это сомнительное усовершенствование алгоритма, так как при упорядоченной вставке
        пришлось бы каждый раз дорого перекраивать вектор уникальных значений, "сдвигая" хвост. */
    }

    std::cout << "Number of unique numbers in test vector is " << unique_numbers.size() << "\n" << std::endl;
}

int main()
{
    task1();
    task2();
    return 0;
}