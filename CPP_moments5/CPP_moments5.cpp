#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*  Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, 
    и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз).
    Продемонстрировать работу функции, передав итераторы различных типов.  */

template <typename Iterator>
void print_words(Iterator beg, Iterator end)
{
    std::set <std::string> words;
    for (Iterator it = beg; it < end; ++it)
    {
        words.insert(*it);
    }
    for (const auto& wrd : words)
        std::cout << wrd << " ";
    std::cout << std::endl;
}

void task1()
{
    std::cout << "TASK 1\n";

    std::cout << "test with vector:\n";
    std::vector <std::string> example1{ "big", "huge", "enormous", "elephant", "huge", "whale", "big", "giant", "great", "monster", "giant" };
    print_words(example1.begin(), example1.end());

    std::cout << "test with deque:\n";
    std::deque <std::string> example2{ "big", "huge", "enormous", "elephant", "huge", "whale", "big", "giant", "great", "monster", "giant" };
    print_words(example2.begin(), example2.end());

    std::cout << "test with list:\n";
    std::list <std::string> example3{ "big", "huge", "enormous", "elephant", "huge", "whale", "big", "giant", "great", "monster", "giant" };
    // !!! не работает: Ошибка C2676 бинарный "<": "Iterator" не определяет этот оператор или преобразование к типу приемлемо к встроенному оператору
    // print_words(example3.begin(), example3.end());

    std::cout << std::endl;
}

int main()
{
    task1();
    return 0;
}