#include "ArrayInt.h"

ArrayInt::ArrayInt(int length) :
    m_length(length)
{
    assert(length >= 0);

    if (length > 0)
        m_data = new int[length];
    else
        m_data = nullptr;
}

ArrayInt::~ArrayInt()
{
    delete[] m_data;
}

void ArrayInt::erase()
{
    delete[] m_data;

    // ����� ��� ����� ������� m_data �������� nullptr, ����� �� ������ �� ���� �������� ���������
    m_data = nullptr;
    m_length = 0;
}

int ArrayInt::getLength() const
{
    return m_length;
}

int& ArrayInt::operator[](int index)
{
    assert(index >= 0 && index < m_length);
    return m_data[index];
}

// ������� resize �������� ������ �������. ��� ������������ �������� �����������. ������� ���������
void ArrayInt::resize(int newLength)
{
    // ���� ������ ��� ������ ����� � return
    if (newLength == m_length)
        return;

    // ���� ����� ������� ������ ������ � ������ ��� � ����� return
    if (newLength <= 0)
    {
        erase();
        return;
    }

    // ������ �����, ��� newLength >0
    // �������� ����� ������
    int* data = new int[newLength];

    // ����� ����� ����������� � ����������� ���������� ��������� � ����� ������
    // ����� ����������� ������� ���������, ������� �� ���� � ������� �� ��������
    if (m_length > 0)
    {
        int elementsToCopy = (newLength > m_length) ? m_length : newLength;

        // ���������� �������� ��������
        for (int index = 0; index < elementsToCopy; ++index)
            data[index] = m_data[index];
    }

    // ������� ������ ������, ��� ��� �� ��� ��� �� �����
    delete[] m_data;

    // � ���������� ������ ������� ������� �����! �������� ��������, m_data ���������
    // �� ��� �� �����, �� ������� ��������� ��� ����� ����������� ���������� ������. ���������
    // ������ ���� ����������� ���������� � ��� �� ����� ����������, ����� ������ �� ������� ���������
    m_data = data;
    m_length = newLength;
}

void ArrayInt::insertBefore(int value, int index)
{
    // �������� ������������ ������������� �������
    assert(index >= 0 && index <= m_length);

    // ������� ����� ������ �� ���� ������� ������ ������� �������
    int* data = new int[m_length + 1];

    // �������� ��� �������� �� index-�
    for (int before = 0; before < index; ++before)
        data[before] = m_data[before];

    // ��������� ����� ������� � ����� ������
    data[index] = value;

    // �������� ��� �������� ����� ������������ ��������
    for (int after = index; after < m_length; ++after)
        data[after + 1] = m_data[after];

    // ������� ������ ������ � ���������� ������ ���� ����� 
    delete[] m_data;
    m_data = data;
    ++m_length;
}

void ArrayInt::push_back(int value) 
{ 
    insertBefore(value, m_length); 
}

// ����� ���������� �������� ������� �� �������� ������:
int ArrayInt::pop_back()
{
    assert(m_length > 0);
    int last_element = (*this)[m_length - 1];
    (*this)[m_length - 1] = 0;
    --m_length;
    return last_element;
}

int ArrayInt::pop_front()
{
    assert(m_length > 0);
    const int first_element = m_data[0];
    if (m_length == 1)
        erase();
    else
    {
        m_data[0] = 0;
        m_data = m_data + 1;
        --m_length;
    }
    return first_element;
}

// ������ ������� �������� ���� �����
void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

// ������� ����������
void qsort(int* array, int first, int last)
{
    int i = first;
    int j = last;

    int base_element = array[(first + last) / 2];

    do
    {
        while (array[i] < base_element) i++;
        while (array[j] > base_element) j--;

        if (i <= j)
        {
            swap(&array[i], &array[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)  qsort(array, i, last);
    if (first < j) qsort(array, first, j);
}

void ArrayInt::sort()
{
    qsort(m_data, 0, m_length - 1);
}

void ArrayInt::print() const
{
    if (m_length == 0)
    {
        std::cout << "vector is empty!\n";
        return;
    }
    for (int i = 0; i < m_length; ++i)
        std::cout << m_data[i] << " ";
    std::cout << std::endl;
}
