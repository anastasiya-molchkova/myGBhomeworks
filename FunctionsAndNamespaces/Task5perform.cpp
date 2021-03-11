////////////////////////////////////// TASK 5: ///////////////////////////////////////// 
#include <cstdarg>              // ��� ������ � ���������� (variable length argument)
#include "AllTheFunctions.h"

namespace work_with_functions
{
    // ������� ����� ���������� ��������� �� ������ ������� �������, ���������� �� ���������� ����������
    bool* conversion01withVa(const size_t size, ...)
    {
        bool* new_array = new bool[size];   // �������� ������������ ������, ������� �������� ���������� ����������� �����������

        va_list list;
        va_start(list, size);

        for (size_t i = 0; i < size; ++i)
            new_array[i] = !va_arg(list, bool);

        va_end(list);
        return new_array;
    }

    // ���������� ������ ������� - ������� ����������� 0 � 1 � ��������, ��������� � ������� ������ ��������� ������� ������ �������
    void task5()
    {
        cout << "TASK 5\n";

        const size_t SIZE = 15;
        cout << "Initial array:\n0 1 0 1 1 1 0 0 1 0 1 1 1 1 0\n";

        bool* result = conversion01withVa(SIZE, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0);

        cout << "Final array:\n";
        printArray(result, SIZE);
        cout << "\n";

        delete[] result;
    }
}