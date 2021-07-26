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
    //std::cout << vector.pop_front() << std::endl;
    vector.print();

}

int main()
{
    task1();
    return 0;
}