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

///////////////////////// TASK 1:

class Date
{
private:
    uint16_t m_day = 1;
    uint16_t m_month = 1;
    uint16_t m_year = 1990;
public:
    Date() = default;
    Date(const uint16_t day, const uint16_t month, const uint16_t year): m_day(day), m_month(month), m_year(year) 
    {
        // я решила не делать полную проверку дат, чтобы не связываться с февралём и високосными годами
        // заменим лишь заведомо неверные числа и месяца
        if ((m_day > 31) || (m_month > 12))
        {
            std::cerr << "\nWarning: wrong date: " << m_day << "." << m_month << "." << m_year << " will be replaced to: ";
            if (m_day > 31)
                m_day = 28;
            if (m_month > 12)
                m_month = 12;
            std::cout << m_day << "." << m_month << "." << m_year << '\n';
        } 
    }
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

///////////////////////// TASK 2:

// перегрузим оператор сравнения двух дат
bool operator<(const Date& date1, const Date& date2)
{
    if (date1.get_year() < date2.get_year())
        return true;
    else if (date1.get_year() > date2.get_year())
        return false;
    else  // года у дат совпадают
    {
        if (date1.get_month() < date2.get_month())
            return true;
        else if (date1.get_month() > date2.get_month())
            return false;
        else  // у дат совпадают годы и месяцы
            return (date1.get_day() < date2.get_day()) ? true : false;
    }
}

// я не знаю, как сделать так, чтобы функция принимала указатели std::unique_ptr <Date>, но чтобы они не обнулились
Date latest_date(const std::unique_ptr <Date>& date_ptr1, const std::unique_ptr <Date>& date_ptr2)
{
    return (*date_ptr1 < *date_ptr2) ? (*date_ptr2) : (*date_ptr1);
}

// чтобы возвращать указатели через параметры, я передаю их по ссылке...
void exchange(std::unique_ptr <Date>& date1, std::unique_ptr <Date>& date2)
{
    auto temp = std::move(date1);
    date1 = std::move(date2);
    date2 = std::move(temp);
}

void task2()
{
    std::cout << "Task 2, with handover of smart pointers to functions.\n";

    std::unique_ptr <Date> date1 = std::make_unique<Date>(9, 8, 2021);
    std::unique_ptr <Date> date2 = std::make_unique<Date>(33, 18, 2021);
    std::cout << "Date 1: " << *date1 << " Date 2: " << *date2 << std::endl;

    std::cout << "The latest date is: " << latest_date(date1, date2) << std::endl;
    std::cout << "After comparison:\n";
    std::cout << "Date 1: " << *date1 << " Date 2: " << *date2 << std::endl;

    exchange(date1, date2);
    std::cout << "After exchange:\n";
    std::cout << "Date 1: " << *date1 << " Date 2: " << *date2 << std::endl << std::endl;
}

int main()
{
    task1();
    task2();
    return 0;
}
