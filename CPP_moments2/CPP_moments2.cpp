#include "Timer.h"      // для измерения времени выполнения кода. Внутри #include <iostream> 
#include <vector>
#include <algorithm>    // для библиотечных функций
#include <utility>      // семантика перемещений при передаче указателя в вектор
//#include <typeinfo>
#include <iomanip>      // форматированный вывод
#include <fstream>
#include <string>

using std::cout; using std::endl;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, 
// на которые указывают эти указатели 
// (нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).

template <typename T>
void swap_pntrs(T*& const ptr1, T*& const ptr2)
{
    T* tmp = ptr1;
    ptr1 = ptr2;
    ptr2 = tmp;
}

void task1()
{
    cout << "Task1:\n";
    int* int_ptr1 = new int(-16);
    cout << "ptr1: " << int_ptr1 << ", value: " << *int_ptr1 << endl;
    int* int_ptr2 = new int(99'555'999);
    cout << "ptr2: " << int_ptr2 << ", value: " << *int_ptr2 << endl;
    cout << "after swap:\n";
    swap_pntrs(int_ptr1, int_ptr2);
    cout << "ptr1: " << int_ptr1 << ", value: " << *int_ptr1 << endl;
    cout << "ptr2: " << int_ptr2 << ", value: " << *int_ptr2 << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Реализуйте шаблонную функцию SortPointers, которая принимает вектор указателей 
// и сортирует указатели по значениям, на которые они указывают.

using std::vector;

template <typename T>
void sort_pointers(vector <T*>& pointers)
{
    std::sort(pointers.begin(), pointers.end(), [](T* l_pntr, T* r_pntr)
        {return *l_pntr < *r_pntr; });
}

template <typename T>
void fill_pointers_vector(vector <T*>& pointers, const size_t size, const int upper_limit)
{
    pointers.reserve(size);
    T* new_ptr(nullptr);
    for (size_t i = 0; i < size; ++i)
    {
        new_ptr = new T;
        *new_ptr =  rand() % upper_limit;

        // !!! на эту строчку ругается, даже если T.type() Но и без неё работает:
        //if (T == typeid(double) || T == typeid(float))
        // добавляем дробную часть:
            *new_ptr += (rand() % 1000)/ static_cast <float>(1000);

        pointers.push_back(std::move(new_ptr));
    }
}

template <typename T>
void print_vector_values(const vector <T*>& pointers)
{
    //cout << "capacity: " << pointers.capacity() << endl;
    cout << std::fixed;    // для дробных чисел будем задавать фиксированное количество знаков после запятой
    for (const auto element : pointers)
        cout << std::setprecision(3) << *element << " ";
    cout << endl;
}

void task2()
{
    cout << "\nTask2:\n";

    const size_t n_elements = 100;
    vector <double*> pntrs;
    fill_pointers_vector(pntrs, n_elements, 1000);
    
    cout << "before sort:\n";
    print_vector_values(pntrs);

    sort_pointers(pntrs);

    cout << "after sort:\n";
    print_vector_values(pntrs);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-3~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Подсчитайте количество гласных букв в книге “Война и мир”.
// Для подсчета используйте 4 способа:
//     count_if и find
//     count_if и цикл for
//     цикл for и find
//     2 цикла for
// Замерьте время каждого способа подсчета и сделайте выводы.

using std::string;
using std::ifstream;

bool is_vowel_forMethod(const char letter, const string& vowels)
{
    for (const auto vwl : vowels)
        if (letter == vwl)
            return true;
    return false;
}

bool is_vowel_findMethod(const char letter, const string& vowels)
{
    if (vowels.find(letter, 0) == string::npos)
        return false;
    return true;
}

// в двух следующих функциях нам понадобится указатель на одну из двух предыдущих функций
typedef bool (*is_vowel_Fcn)(const char, const string&);

size_t count_vowels_in_word_forMethod(const string& word, const string& vowels, is_vowel_Fcn chosen_fcn)
{
    size_t sum = 0;
    for (const auto letter : word)
        if (chosen_fcn(tolower(letter), vowels))
            ++sum;
    return sum;
}

size_t count_vowels_in_word_countIfMethod(const string& word, const string& vowels, is_vowel_Fcn chosen_fcn)
{
    return std::count_if(word.begin(), word.end(), [=](auto letter) 
                       {return chosen_fcn(tolower(letter), vowels); });
}

void task3()
{
    cout << "\nTask3:" << endl;

    ifstream file("War and peace.txt");

    string vowels{ "aeiouy" };
    string word;
    size_t result_sum_vowels = 0;

    Timer timer1("1) count_if and find");
    while (file)
    {
        file >> word;
        result_sum_vowels += count_vowels_in_word_countIfMethod(word, vowels, is_vowel_findMethod);
    }
    file.close();
    timer1.print();
    cout << result_sum_vowels << " vowels\n";

    result_sum_vowels = 0;
    file.open("War and peace.txt");
    Timer timer2("2) count_if and for");
    while (file)
    {
        file >> word;
        result_sum_vowels += count_vowels_in_word_countIfMethod(word, vowels, is_vowel_forMethod);
    }
    file.close();
    timer2.print();
    cout << result_sum_vowels << " vowels\n";

    result_sum_vowels = 0;
    file.open("War and peace.txt");
    Timer timer3("3) for and find");    // этот метод у меня даёт наименьшее время
    while (file)
    {
        file >> word;
        result_sum_vowels += count_vowels_in_word_forMethod(word, vowels, is_vowel_findMethod);
    }
    file.close();
    timer3.print();
    cout << result_sum_vowels << " vowels\n";

    result_sum_vowels = 0;
    file.open("War and peace.txt");
    Timer timer4("4) for and for");
    while (file)
    {
        file >> word;
        result_sum_vowels += count_vowels_in_word_forMethod(word, vowels, is_vowel_forMethod);
    }
    file.close();
    timer4.print();
    cout << result_sum_vowels << " vowels\n";
}

int main()
{
    task1();
    task2();
    task3();
    return 0;
}