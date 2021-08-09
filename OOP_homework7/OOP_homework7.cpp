/* 1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. 
      Перегрузите оператор вывода для данного класса. 
      Создайте два "умных" указателя today и date. Первому присвойте значение сегодняшней даты. 
      Для него вызовите по отдельности методы доступа к полям класса Date, а также выведите на экран данные всего объекта 
      с помощью перегруженного оператора вывода. Затем переместите ресурс, которым владеет указатель today в указатель date. 
      Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.
   2. По условию предыдущей задачи создайте два умных указателя date1 и date2. 
●	Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой 
    (сравнение происходит по датам). Функция должна вернуть более позднюю дату.
●	Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.

    Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.*/

#include <iostream>
#include <memory>     // для std::unique_ptr
#include <utility>    // для std::move

class Date
{
private:
    uint16_t m_day = 1;
    uint16_t m_month = 1;
    uint16_t m_year = 1990;
public:
    Date() = default;
    Date(const uint16_t day, const uint16_t month, const uint16_t year): m_day(day), m_month(month), m_year(year) {}
    uint16_t get_day() const
    {
        return m_day;
    }
    uint16_t get_month() const
    {
        return m_month;
    }
    uint16_t get_year() const
    {
        return m_year;
    }
};

std::ostream& operator<<(std::ostream& out, const Date& date)
{
    if (date.get_day() < 10)
        out << '0';
    out << date.get_day() << ".";
    if (date.get_month() < 10)
        out << '0';
    out << date.get_month() << "." << date.get_year();
    return out;
}

void task1()
{
    std::cout << "Task 1, with Date class and smart pointers.\n";

    std::unique_ptr <Date> today = std::make_unique<Date>(9, 8, 2021);
    std::unique_ptr <Date> date = std::make_unique<Date>();

    std::cout << "Today: " << today->get_day() << ", month: " << today->get_month() << ", year: " << today->get_year() << '\n';
    std::cout << *today << std::endl;


    date = std::move(today);
    std::cout << "Today after move to date: ";
    if (today)
        std::cout << *today;
    else 
        std::cout << "empty pointer";
    std::cout << ", date: " << *date << std::endl << std::endl;
}

int main()
{
    task1();
    return 0;
}
