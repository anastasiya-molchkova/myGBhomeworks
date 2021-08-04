/* 1.	Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
   2.	Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
        Подсказка: чтобы определить шаблон с использованием двух разных типов, просто разделите параметры типа шаблона запятой.
   3.	Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа. 
        Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, 
        а второй — любого типа данных.
        Подсказка: при вызове конструктора класса Pair из конструктора класса StringValuePair не забудьте указать, 
        что параметры относятся к классу Pair. */

#include <iostream>
#include <string>
using std::cout; using std::string;

//////////////////////////// TASK 1

template <typename T>
class Pair1
{
private:
    T m_first;
    T m_second;
public:
    Pair1() = delete;
    Pair1(const T a, const T b): m_first{a}, m_second{b} {}
    T first() const
    {
        return m_first;
    }
    T second() const
    {
        return m_second;
    }
};

void task1()
{
    cout << "Task 1, with pair of one type\n";
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << "\n\n";
}

//////////////////////////// TASK 2

template <class T1, typename T2>
class Pair
{
protected:
    T1 m_first;
    T2 m_second;
public:
    Pair() = default;
    Pair(const T1 a, const T2 b) : m_first{ a }, m_second{ b } {}
    virtual T1 first() const
    {
        return m_first;
    }
    T2 second() const
    {
        return m_second;
    }
};

void task2()
{
    cout << "Task 2, with pair of different types\n";
    Pair<int, double> p1(6, 7.8);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2(3.4, 5);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << "\n\n";
}

//////////////////////////// TASK 3

template <typename T2>
class StringValuePair: public Pair<string, T2>
{
public:
    StringValuePair(const string text, const T2 value) : Pair<string, T2>(text, value)
    {}
};

void task3()
{
    cout << "Task 3, with pair of string and another type\n";
    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << "\n\n";
}

int main()
{
    task1();
    task2();
    task3();
    return 0;
}