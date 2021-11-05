#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
//#include <typeinfo>
#include <iomanip>      // матированный вывод

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

int main()
{
    task1();
    task2();
    return 0;
}