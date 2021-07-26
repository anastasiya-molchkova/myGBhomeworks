#ifndef ARRAYINT_H
#define ARRAYINT_H

#include <iostream>
#include <cassert> // для assert()

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr) { }
    ArrayInt(int length);
    ~ArrayInt();

    void erase();
    int getLength() const;
    int& operator[](int index);
    void resize(int newLength);
    void insertBefore(int value, int index);
    void push_back(int value);

    // функции для домашней работы:
    int pop_back();
    int pop_front();
    void sort();
    void print() const;
 
};

#endif
