/* 1. Создать абстрактный класс Figure (фигура). 
      Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг). 
      Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). 
      Для всех классов создать конструкторы. 
      Для класса Figure добавить чисто виртуальную функцию area() (площадь). 
      Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.
   2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). 
      Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус). 
      От этих классов наследует класс Minivan (минивэн). 
      Создать конструкторы для каждого из классов, чтобы они выводили данные о классах. 
      Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. 
      Обратить внимание на проблему «алмаз смерти». 
      Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса 
      создает самый "дочерний" класс.
   3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). 
      Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
      ●	математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
      ●	унарный оператор (-)
      ●	логические операторы сравнения двух дробей (==, !=, <, >, <=, >=). 
      Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте перегрузить один через другой.
      Продемонстрировать использование перегруженных операторов. */

#include <iostream>
#include <cmath>
#include <string>

//////////////////////////// TASK1
class Figure
{
protected:
    double sqr(double n) const
    {
        return pow(n, 2);
    }
public:
    Figure(){}
    virtual double area() const = 0;
};

class Parallelogram : public Figure
{
protected:
    double m_a = 0;         // сторона a
    double m_b = 0;         // сторона b
    double m_h = 0;         // высота
    double m_sin_alpha = 0; // синус угла между сторонами a и b
public:
    // конструкторы:
    Parallelogram(){}
    Parallelogram(const double a, const double h): m_a(a), m_h(h) {}
    Parallelogram(const double a, const double b, const double sin_alpha) : m_a(a), m_b(b), m_sin_alpha(sin_alpha) {}
    // определение площади параллелограма:
    virtual double area() const override
    {
            return (m_h == 0)?(m_a * m_b * m_sin_alpha):(m_a * m_h);
    }
    // геттеры:
    double get_a_side() const
    {
        return m_a;
    }
    double get_b_side() const
    {
        return m_b;
    }
    double get_height() const
    {
        return m_h;
    }
    double get_angle() const
    {
        return m_sin_alpha;
    }
};

class Circle : public Figure
{
private:
    static const double pi;
    double m_radius = 0;
public:
    Circle(){}
    Circle(const double r): m_radius(r){}
    double area() const override
    {
        return pi * sqr(m_radius);
    }
    double get_radius() const
    {
        return m_radius;
    }
};
const double Circle::pi = 3.14;

class Rectangle : public Parallelogram
{
public:
    Rectangle(){}
    Rectangle(const double a, const double b) : Parallelogram(a, b, 1) 
    {
        m_h = b;
    }
    double area() const override
    {
        return m_a * m_b;
    }
};

class Square : public Parallelogram
{
public:
    Square(){}
    Square(const double a) : Parallelogram(a, a, 1)
    {
        m_h = a;
    }
    double area() const override
    {
        return sqr(m_a);
    }
};

class Rhombus : public Parallelogram
{
public:
    Rhombus(){}
    Rhombus(const double a, const double sin_alpha): Parallelogram(a, a, sin_alpha) {}
    double area() const override
    {
        return sqr(m_a) * m_sin_alpha;
    }
};

void task1()
{
    std::cout << "TASK 1, with geometric figures\n";
    Parallelogram prgrm1(3, 2);
    std::cout << "Parallelogram with side " << prgrm1.get_a_side() << " and height " << prgrm1.get_height() 
              << " has area " << prgrm1.area() << "\n";
    Parallelogram prgrm2(3, 7, 0.5);
    std::cout << "Parallelogram with sides " << prgrm2.get_a_side() << " and " << prgrm2.get_b_side() << " and angles sinus " << prgrm2.get_angle() 
              << " has area " << prgrm2.area() << "\n";
    Circle circle(2);
    std::cout << "Circle with radius " << circle.get_radius() << " has area " << circle.area() << "\n";
    Rectangle rectangle(3, 4);
    std::cout << "Rectangle with sides " << rectangle.get_a_side() << " and " << rectangle.get_b_side() 
              << " has area " << rectangle.area() << "\n";
    Square square(3);
    std::cout << "Square with side " << square.get_a_side() << " has area " << square.area() << "\n";
    Rhombus rhombus(3, 0.632);
    std::cout << "Rhombus with side " << rhombus.get_a_side() << " and angles sinus " << rhombus.get_angle() 
              << " has area " << rhombus.area() << "\n";
    std::cout << std::endl;
}

//////////////////////////// TASK2
class Car
{
protected:
    std::string m_company;
    std::string m_model;
    virtual void intro()
    {
        std::cout << "This is a Car\n";
    }
public:
    Car() 
    { 
        intro(); 
    }
    Car(const std::string& company, const std::string& model): m_company(company), m_model(model) 
    {
        intro();
    }
    virtual ~Car()
    {
        std::cout << "~Car\n";
    }
};

class PassengerCar: virtual public Car
{
protected:
    void intro() override
    {
        std::cout << "This is a Passenger Car\n";
    }
public:
    PassengerCar()
    {
        intro();
    }
    PassengerCar(const std::string& company, const std::string& model) : Car(company, model)
    {
        intro();
    }
    ~PassengerCar()
    {
        std::cout << "~PassengerCar\n";
    }
};

class Bus : virtual public Car
{
protected:
    size_t m_seats_number = 10;
    void intro() override
    {
        std::cout << "This is a Bus\n";
    }
public:
    Bus() 
    {
        intro();
    }
    Bus(const std::string& company, const std::string& model, const size_t seats = 10) : Car(company, model), m_seats_number(seats)
    {
        intro();
    }
    ~Bus()
    {
        std::cout << "~Bus\n";
    }
};

class Miniven: public PassengerCar, public Bus
{
private:
    void intro() override
    {
        std::cout << "This is a Miniven\n";
    }
public:
    Miniven()
    {
        intro();
    }
    Miniven(const std::string& company, const std::string& model, const size_t seats = 10) : Bus(company, model, seats) 
    { 
        intro();
    }
    ~Miniven()
    {
        std::cout << "~Miniven\n";
    }
};

void task2()
{
    std::cout << "TASK 2, with different types of cars\n";
    // чтобы увидеть конструкторы и деструкторы для каждого класса, 
    // каждый пример помещаем в свой собственный блок - зону видимости
    {Car car; }
    {PassengerCar pass_car; }
    {Bus bus; }
    {Miniven miniven; }
    std::cout << std::endl;
}

int main()
{
    task1();
    task2();
    return 0;
}
