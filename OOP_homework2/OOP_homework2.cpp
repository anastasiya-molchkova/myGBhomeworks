/* 1. Создать класс Person (человек) с полями: имя, возраст, пол и вес. 
      Определить методы переназначения имени, изменения возраста и веса. 
      Создать производный класс Student (студент), имеющий поле года обучения. 
      Определить методы переназначения и увеличения этого значения. 
      Создать счетчик количества созданных студентов. В функции main() создать несколько студентов. 
      По запросу вывести определенного человека.
   2. Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт). 
      У Fruit есть две переменные-члена: name (имя) и color (цвет). 
      Добавить новый класс GrannySmith, который наследует класс Apple. */

#include <iostream>
#include <string>
#include <vector>

///////////////////////////////// TASK 1
enum Sexes { FEMALE = 0, MALE = 1 };

class Person
{
protected:
    std::string m_name = "";
    unsigned short m_age = 0;
    Sexes m_sex = MALE;
    float m_weight = 100;
public:
    // конструкторы:
    Person () {}
    Person(const std::string& name, const unsigned short age, Sexes sex, const float weight):
        m_name(name), m_age(age), m_sex(sex), m_weight(weight)
    {}
    // сеттеры:
    void set_name(const std::string& name)
    {
        m_name = name;
    }
    void set_age(const unsigned short age)
    {
        m_age = age;
    }
    void set_weight(const float weight)
    {
        m_weight = weight;
    }
};

class Student : public Person
{
private:
    unsigned short m_year = 0;
public:
    static size_t students_counter;
    // конструкторы:
    Student() 
    {
        ++students_counter;
    }
    Student(const std::string& name, const unsigned short age, Sexes sex, const float weight, const unsigned short year) :
        Person(name, age, sex, weight), m_year(year)
    {
        ++students_counter;
    }
    // методы:
    void set_year(const unsigned short year)
    {
        m_year = year;
    }
    void increase_year()
    {
        ++m_year;
    }
    void print()
    {
        std::cout << "Student " << m_name << ", " << m_age << " years old, " << ((m_sex == MALE)?"male":"female") << ", "
                  << m_weight << " kg., " << m_year << " year of study\n";
    }
};

// обнуляем статическую переменную-счётчик вне класса:
size_t Student::students_counter = 0;

void task1()
{
    std::cout << " TASK 1, with Student class\n\n";
    // создадим несколько студентов:
    std::vector <Student> students
    { Student("Sonya", 18, FEMALE, 50, 2),
      Student("Vasya", 17, MALE, 60, 1),
      Student("Lisa", 19, FEMALE, 54, 3),
      Student("Igor", 20, MALE, 65, 4),
      Student("Artem", 19, MALE, 67, 3) };

    // запрашиваем, какого студента нужно вывести:
    std::cout << Student::students_counter << " students have been created. Which one do you want to check?\n";
    size_t st_number = 0;
    while (st_number < 1 || st_number > Student::students_counter)
    {
        std::cout << "enter a number from 1 to " << Student::students_counter << ": ";
        std::cin >> st_number;
    } ;
    
    // и выводим данные интересующего студента:
    students.at(st_number - 1).print();
    std::cout << std::endl;
}

///////////////////////////////// TASK 2
class Fruit
{
protected:
    std::string m_name = "";
    std::string m_color = "";
public:
    Fruit () {}
    Fruit(const std::string& name, const std::string& color): m_name(name), m_color(color)
    {}
    std::string getName () const
    {
        return m_name;
    }
    std::string getColor() const
    {
        return m_color;
    }
};

class Apple : public Fruit
{
public:
    Apple(): Fruit("apple", "red/yellow/green") {}
    Apple(const std::string& name, const std::string& color) : Fruit(name, color)
    {}
    Apple(const std::string& color) : Fruit("apple", color)
    {}
};

class Banana : public Fruit
{
public:
    Banana(): Fruit("banana", "yellow") {}
    Banana(const std::string& color) : Fruit("banana", color)
    {}
    Banana(const std::string& name, const std::string& color) : Fruit(name, color)
    {}
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("Granny Smith apple", "green") {}
    GrannySmith(const std::string& color) : Apple("Granny Smith apple", color)
    {}
    GrannySmith(const std::string& name, const std::string& color) : Apple(name, color)
    {}
};

void task2()
{
    std::cout << " TASK 2, with Fruit classes\n\n";

    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
    
    std::cout << std::endl;
}

int main()
{
    task1();
    task2();
    return 0;
}