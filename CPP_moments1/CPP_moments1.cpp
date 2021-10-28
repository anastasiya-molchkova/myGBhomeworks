/*  Имеется база сотрудников и номеров их телефонов. Требуется написать соответствующие структуры для хранения данных 
    и заполнить контейнер записями из базы. 
    Затем необходимо реализовать методы обработки данных, а также вывести на экран всю необходимую информацию.  */

#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>     // для получения числа из строки
#include <iomanip>     // для форматирования вывода
#include <algorithm>   // для стандартных функций sort, for_each, find_if и прочих

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~структура Person~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct Person
{
public:
    string m_surname;
private:
    string m_name;
    optional<string> m_patronymic;
public:
    Person(const string& surname, const string& name, const string& patronymic = "") : m_surname{ surname }, m_name{ name }
    {
        if (patronymic != "")
            m_patronymic = patronymic;
        else
            m_patronymic = nullopt;
    }
    friend ostream& operator<<(ostream& out, const Person& person);
    friend bool operator<(const Person& lft_person, const Person& rght_person);
    friend bool operator==(const Person& lft_person, const Person& rght_person);
};

ostream& operator<<(ostream& out, const Person& person)
{
    // !!! следующая строчка не работает, Ошибка	C2338	optional<T>::value_or(U) requires U to be convertible to T
    //out << person.m_surname << " " << person.m_name << " " << person.m_patronymic.value_or("");
    // поэтому так:
    out << setw(15) << left << person.m_surname << setw(10) << left << person.m_name << setw(20) << left;
    if (person.m_patronymic.has_value())
        out << person.m_patronymic.value();
    else 
        out << " ";
    return out;
}

bool operator<(const Person& lft_person, const Person& rght_person)
{
    return tie(lft_person.m_surname, lft_person.m_name, lft_person.m_patronymic) < tie(rght_person.m_surname, rght_person.m_name, rght_person.m_patronymic);
}

bool operator==(const Person& lft_person, const Person& rght_person)
{
    return tie(lft_person.m_surname, lft_person.m_name, lft_person.m_patronymic) == tie(rght_person.m_surname, rght_person.m_name, rght_person.m_patronymic);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~структура PhoneNumber~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

struct PhoneNumber
{
private:
    int m_country;
    int m_city;
    string m_number;
    optional<int> m_add_number;
public:
    PhoneNumber(const int country, const int city, const string& number, const int add_number = -1) : m_country{country}, m_city{city}, m_number{number}
    {
        if (add_number != -1)
            m_add_number = add_number;
        else
            m_add_number = nullopt;
    }
    friend ostream& operator<<(ostream& out, const PhoneNumber& phone);
    friend bool operator<(const PhoneNumber& lft_phone, const PhoneNumber& rght_phone);
};

ostream& operator<<(ostream& out, const PhoneNumber& phone)
{
    // !!! следующая строчка не работает, Ошибка	C2338	optional<T>::value_or(U) requires U to be convertible to T
    //out << "+" << phone.m_country << "(" << phone.m_city << ")" << phone.m_number << " " << phone.m_add_number.value_or("");
    // поэтому так:
    out << "+" << phone.m_country << "(" << phone.m_city << ")" << phone.m_number;
    if (phone.m_add_number.has_value())
        out << " " << phone.m_add_number.value();
    return out;
}

bool operator<(const PhoneNumber& lft_phone, const PhoneNumber& rght_phone)
{
    return tie(lft_phone.m_country, lft_phone.m_city, lft_phone.m_number, lft_phone.m_add_number) < tie(rght_phone.m_country, rght_phone.m_city, rght_phone.m_number, rght_phone.m_add_number);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~класс PhoneBook~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// пытается превратить строку в число, выдаёт false, если не получилось
inline bool is_number(const string& str, int& number)
{
    std::istringstream istream(str);
    return (istream >> number) ? true : false;
}

class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> data;
public:
    PhoneBook(ifstream& data_from_file) 
    {
        string surname, name, patronymic, number, str_add_number;
        int country, city, add_number;
        while (data_from_file) 
        // !!! почему-то дважды берёт из файла последнюю строку... Не подскажете, почему?
        {
            data_from_file >> surname;
            data_from_file >> name;
            data_from_file >> patronymic;
            data_from_file >> country;
            data_from_file >> city;
            data_from_file >> number;
            data_from_file >> str_add_number;
            if (patronymic == "-")
                patronymic = "";
            if (!is_number(str_add_number, add_number))
                add_number = -1;
                
            Person person{ surname, name, patronymic };
            PhoneNumber phone{ country, city, number, add_number };
            data.push_back(make_pair(person, phone));
        }
        data_from_file.close();
    }

    friend ostream& operator<<(ostream& out, const PhoneBook& pb);
    
    void SortByName()
    {
        sort(data.begin(), data.end(), [](const auto& data1, const auto& data2)
                                       {return data1.first < data2.first; });
    }

    void SortByPhone()
    {
        sort(data.begin(), data.end(), [](const auto& data1, const auto& data2)
            {return data1.second < data2.second; });
    }

    pair<string, PhoneNumber> GetPhoneNumber(const string& surname_to_search)
    {
        size_t count = 0;
        PhoneNumber found_number(0, 0, "");
        for_each(data.begin(), data.end(), [&](const auto& line)
            {
                if (line.first.m_surname == surname_to_search)
                {
                    ++count;
                    found_number = line.second;
                }    
            });
        string result = "";
        if (count == 0)
            result = "not found";
        if (count > 1)
            result = "found more than 1";
        return make_pair(result, found_number);
    }

    void ChangePhoneNumber(const Person& person_to_search, const PhoneNumber& new_number)
    {
        auto found_data = find_if(data.begin(), data.end(), [&](auto& line)
            {
                return (line.first == person_to_search);
            });
        
        // не понимаю, почему нужно было сделать именно через find_if. Мне это решение кажется мутным. Лучше бы через for_each
        if (found_data != data.end())
            found_data->second = new_number;
        // таким образом меняется лишь телефон у первого такого найденного человека
    }
};

ostream& operator<<(ostream& out, const PhoneBook& pb)
{
    for (const auto& [person, phone] : pb.data)
        out << person << " " << phone << endl;
    return out;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    ifstream file("PB.txt");
    PhoneBook book(file);
    cout << book;

    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;
    
    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (answer.first.empty())
            cout << answer.second;
        else
            cout << answer.first;
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458"});
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    book.ChangePhoneNumber(Person{ "Aleksandrov", "Georgii"}, PhoneNumber{ 493, 7637, "12345678", 13 });
    cout << book;

    return 0;
}
