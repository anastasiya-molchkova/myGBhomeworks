#include <iostream>
#include <utility>

using std::cout; using std::endl;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK-1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Реализуйте шаблонную функцию Swap, которая принимает два указателя и обменивает местами значения, 
// на которые указывают эти указатели 
// (нужно обменивать именно сами указатели, переменные должны оставаться в тех же адресах памяти).

template <typename T>
void swap(T* const ptr1, T* const ptr2)
{
    T tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void task1()
{
    cout << "Task1:\n";
    int* int_ptr1 = new int(-16);
    cout << "ptr1: " << int_ptr1 << ", value: " << *int_ptr1 << endl;
    int* int_ptr2 = new int(99'555'999);
    cout << "ptr2: " << int_ptr2 << ", value: " << *int_ptr2 << endl;
    cout << "after swap:\n";
    swap(int_ptr1, int_ptr2);
    cout << "ptr1: " << int_ptr1 << ", value: " << *int_ptr1 << endl;
    cout << "ptr2: " << int_ptr2 << ", value: " << *int_ptr2 << endl;
}

int main()
{
    task1();
    return 0;
}