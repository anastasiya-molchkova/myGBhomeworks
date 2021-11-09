#include <iostream>
#include <vector>
#include <numeric>   // для std::accumulate
#include <iomanip>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK 1~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Написать функцию, добавляющую в конец списка вещественных чисел элемент, 
// значение которого равно среднему арифметическому всех его элементов.

void add_average(std::vector<double>& real_numbers)
{
    real_numbers.push_back(std::accumulate(real_numbers.begin(), real_numbers.end(), 0.0) / real_numbers.size());
}

void print_vector(const std::vector<double>& vec)
{
    for (const auto n : vec)
        std::cout << n << " ";
    std::cout << std::endl;
}

void task1()
{
    std::cout << "TASK 1:\n";
    std::vector<double> vec{ 2.1, 3.0, 5.5, 10.0, 9.65 };
    std::cout << "Initial vector: "; 
    print_vector(vec);
    add_average(vec);
    std::cout << "Result vector:  ";
    print_vector(vec);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK 2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы.

class Matrix
{
private:
    size_t dimension = 1;
    std::vector<std::vector<int>> content;     // будем использовать вектор векторов, т.к. нам понадобится обращение к произвольным элементам
    Matrix() {}                                // таким образом запрещаем создавать матрицы без содержания
public:
    // конструктор с размерностью и векторами строк
    Matrix(const size_t n, const std::vector<std::vector<int>> arrays) : dimension(n), content(arrays)
    {
        content.reserve(dimension);
        for (size_t i = 0; i < dimension; ++i)
            content[i].reserve(dimension);
    }
    void print() const
    {
        for (const auto& row : content)
        {
            for (size_t j = 0; j < dimension; ++j)
                std::cout << std::setw(5) << row[j];
            std::cout << std::endl;
        }
    }
    // получает матрицу из начальной "вычитанием" строки и столбца нужного номера
    Matrix get_minor_matrix(const size_t row, const size_t col) const
    {
        Matrix m(dimension, content);
        --m.dimension;
        m.content.erase(m.content.begin()+row);
        for (size_t i = 0; i < m.dimension; ++i)
            m.content[i].erase(m.content[i].begin() + col);
        return m;
    }
    // рекурсивная функция нахождения определителя матрицы
    int det() const
    {
        if (dimension == 1)
            return content[0][0];
        if (dimension == 2)
            return (content[0][0] * content[1][1] - content[1][0] * content[0][1]);
        int det = 0;
        // считаем по первой строке, её индекс 0
        for (size_t j = 0; j < dimension; ++j)
        {
            if (j % 2 == 0) // множитель (-1) в степени (номер строки+номер столбца) сводится к этому условию
                det += content[0][j] * get_minor_matrix(0, j).det();
            else
                det -= content[0][j] * get_minor_matrix(0, j).det();
        }
        return det;
    }
};

void task2()  // определители для матриц были проверены в онлайн-калькуляторе, всё считается верно
{
    std::cout << "\nTASK 2:\n";

    Matrix m1(1, { { 5 } });
    std::cout << "M1:\n";
    m1.print();
    std::cout << "det(M1) = " << m1.det() << std::endl;

    Matrix m2(2, { { 1 , 2}, {3, 4} });
    std::cout << "M2:\n";
    m2.print();
    std::cout << "det(M2) = " << m2.det() << std::endl;

    Matrix m3(3, { { 1, 2, 3}, {4, -2, -3}, {-1, 10, 1 } });
    std::cout << "M3:\n";
    m3.print();
    std::cout << "det(M3) = " << m3.det() << std::endl;

    Matrix m4(4, { { 1, -2, 3, 4}, {-3, -2, 2, 10}, {-1, 10, 4, -3 }, {2, -1, 1, -2} });
    std::cout << "M4:\n";
    m4.print();
    std::cout << "det(M4) = " << m4.det() << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TASK 3~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Реализовать собственный класс итератора, с помощью которого можно будет 
// проитерироваться по диапазону целых чисел в цикле for-range-based.

class Iterated_int
{
private:
    int* iterator;
    size_t size = 0;
    std::vector<int> array;
public:
    Iterated_int(const size_t capacity): size(capacity), array{}, iterator(&array[0])
    {
        array.reserve(size);
    }
    Iterated_int(const std::vector<int>& numbers) : size(numbers.size()), array{numbers}, iterator(&array[0])
    {}
    void add(const int element)
    {
        array.push_back(element);
        ++size;
    }
    int get(const size_t index) const
    {
        return array.at(index);
    }
    void del(const size_t index)
    {
        array.erase(array.begin()+index);
        --size;
    }
    int* begin()
    {
        return &array[0];
    }
    int* end()
    {
        // !!! здесь ругается "cannot seek value-initialiized vector itarator"
        //return iterator+size;
        // !!! а так ругается на "vector itarators incompatible"
        //return array.end();
        // !!! а так ругается на "vector subscript out of range"
        //return &array[size];
    }
    void operator++()
    {
        ++iterator;
    }
    int& operator*()
    {
        return *iterator;
    }
    void print() const
    {
        for (const auto element : array)
            std::cout << element << "  ";
        std::cout << std::endl;
    }
};

void task3()
{
    std::cout << "\nTASK 3:\n";
    Iterated_int data({ 3, -4, 13, 34, 23, 32, 11 });
    std::cout << "Initial data: ";
    data.print();

    // !!! дальше возникает run time error при попытке получить data.end()
    for (auto el : data)
        el *= 2;
    std::cout << "Doubled data: ";
    data.print();

}

int main()
{
    task1();
    task2();
    task3();
    return 0;
}