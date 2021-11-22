#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <string>
#include <map>

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*  Используя ассоциативный контейнер, напишите программу, 
    которая будет считывать данные введенные пользователем из стандартного потока ввода 
    и разбивать их на предложения. 
    Далее программа должна вывести пользователю все предложения, отсортировав их по длине. */

std::multimap<size_t, std::string> split_by_sentences(const std::string& text)
{
    std::multimap<size_t, std::string> sentences;
    std::string sentence{};
    for (const char c : text)
    {
        if (sentence.empty() && c == ' '); // игнорируем первый пробел в предложении
        else 
            sentence += c;
        if ((c == '.') || (c == '?') || (c == '!'))            // конец предложения
        {
            // !!! Почему-то добавляет все предложения, даже повторяющиеся (когда такие пары ключ-значение уже есть... 
            sentences.insert({sentence.length(), sentence});   // добавляем в словарь
            sentence = "";                                     // начинаем заново
        }
    }
    return sentences;
}

void print_ordered_sentences(const std::multimap<size_t, std::string>& sentences)
{
    for (const auto& [length, sentence] : sentences)
        std::cout << length << ": " << sentence << "\n";
}

void task2()
{
    std::cout << "TASK 2\n";
    std::cout << "Please input a text:\n";
    std::string text;
    std::getline(std::cin, text);

    std::cout << "\nUnique ordered sentences from your text:\n";
    print_ordered_sentences(split_by_sentences(text));
}

int main()
{
    task1();
    task2();
    return 0;
}