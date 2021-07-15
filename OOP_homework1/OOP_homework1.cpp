/* Практическое задание
1. Создать класс Power, который содержит два вещественных числа. 
   Этот класс должен иметь две переменные-члена для хранения этих вещественных чисел. 
   Еще создать два метода: один с именем set, который позволит присваивать значения переменным, 
   второй — calculate, который будет выводить результат возведения первого числа в степень второго числа. 
   Задать значения этих двух чисел по умолчанию.
2. Написать класс с именем RGBA, который содержит 4 переменные-члена типа std::uint8_t: m_red, m_green, m_blue и m_alpha 
   (#include cstdint для доступа к этому типу). 
   Задать 0 в качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha. 
   Создать конструктор со списком инициализации членов, который позволит пользователю передавать значения 
   для m_red, m_blue, m_green и m_alpha. Написать функцию print(), которая будет выводить значения переменных-членов.
3. Написать класс, который реализует функциональность стека. Класс Stack должен иметь:
   private-массив целых чисел длиной 10;
   private целочисленное значение для отслеживания длины стека;
   public-метод с именем reset(), который будет сбрасывать длину и все значения элементов на 0;
   public-метод с именем push(), который будет добавлять значение в стек. push() должен возвращать значение false, если массив уже заполнен, и true в противном случае;
   public-метод с именем pop() для вытягивания и возврата значения из стека. Если в стеке нет значений, то должно выводиться предупреждение;
   public-метод с именем print(), который будет выводить все значения стека. */

#include <iostream>
#include <cmath>    // для возведения в степень
#include <cstdint>  // для std::uint8_t

// TASK 1
class Power
{
private:
    double m_base = 1;
    double m_exponent = 1;
public:
    Power() {}    // пустой конструктор по умолчанию
    void set(const double base = 1, const double exponent = 1)
    {
        m_base = base;
        m_exponent = exponent;
    }
    double calculate()
    {
        return pow(m_base, m_exponent);
    }
};

void task1()
{
    std::cout << "Task 1, Power class.\n";

    double base = 10;
    double index = 3;

    Power example1;
    example1.set(base, index);
    std::cout << base << " in " << index << " = " << example1.calculate() << '\n';

    base = 100;
    index = -1.0;
    Power example2;
    example2.set(base, index);
    std::cout << base << " in " << index << " = " << example2.calculate() << '\n';

    base = 3.14;
    index = 2;
    Power example3;
    example3.set(base, index);
    std::cout << base << " in " << index << " = " << example3.calculate() << '\n';

    std::cout << std::endl;
}

// TASK 2
class RGBA
{
private:
    std::uint8_t m_red = 0;
    std::uint8_t m_green = 0;
    std::uint8_t m_blue = 0;
    std::uint8_t m_alpha = 255;
public:
    RGBA() {}
    // параметризированный конструктор:
    RGBA(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = 255):
        m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
    {}

    void print()
    {
        std::cout << "RGBA color code is (" << static_cast<int>(m_red) << ", " << static_cast<int>(m_green) 
                          << ", " << static_cast<int>(m_blue) << ", " << static_cast<int>(m_alpha) << ")\n";
    }
};

void task2()
{
    std::cout << "Task 2, RGBA class.\n";

    RGBA color1;
    color1.print();

    RGBA color2 = RGBA(100, 200, 50, 10);
    color2.print();

    RGBA color3 = RGBA(80, 130, 150);
    color3.print();

    std::cout << std::endl;
}

int main()
{
    task1();
    task2();
    return 0;
}