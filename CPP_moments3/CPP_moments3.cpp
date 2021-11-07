#include <iostream>
#include <vector>
#include <numeric>   // для std::accumulate

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
    std::cout << "Result vector: ";
    print_vector(vec);
}

int main()
{
    task1();
    return 0;
}