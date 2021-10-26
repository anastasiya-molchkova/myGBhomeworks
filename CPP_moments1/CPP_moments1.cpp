/*  Имеется база сотрудников и номеров их телефонов. Требуется написать соответствующие структуры для хранения данных 
    и заполнить контейнер записями из базы. 
    Затем необходимо реализовать методы обработки данных, а также вывести на экран всю необходимую информацию.  */

#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std;

//                    структура Person
struct Person
{
private:
    string m_surname;
    string m_name;
    optional<string> m_patronymic;
public:
    Person(const string& surname, const string& name, const string& patronymic = "") : m_surname{ surname }, m_name{ name }
    {
        if (patronymic != "")
            m_patronymic.value() = patronymic;
        else
            m_patronymic = nullopt;
    }
    friend ostream& operator<<(ostream& out, const Person& person);
    friend bool operator<(const Person& lft_person, const Person& rght_person);
    friend bool operator==(const Person& lft_person, const Person& rght_person);
};

ostream& operator<<(ostream& out, const Person& person)
{
    if (person.m_patronymic.has_value())
        out << person.m_name << " " << person.m_patronymic.value() << " " << person.m_surname;
    else
        out << person.m_name << " " << person.m_surname;
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

//                    структура PhoneNumber
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
            m_add_number.value() = add_number;
        else
            m_add_number = nullopt;
    }
    friend ostream& operator<<(ostream& out, const PhoneNumber& phone);
};

ostream& operator<<(ostream& out, const PhoneNumber& phone)
{
    if (phone.m_add_number.has_value())
        out << "+" << phone.m_country << "(" << phone.m_city << ")" << phone.m_number << " " << phone.m_add_number.value();
    else
        out << "+" << phone.m_country << "(" << phone.m_city << ")" << phone.m_number;
    return out;
}

//                    класс PhoneBook
class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> data;
public:
    PhoneBook(ifstream& data_from_file) 
    {
        string lineFromFile;
        string surname, name, patronymic, number, str_add_number;
        int country, city, add_number;
        while (data_from_file)
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
            if (str_add_number == "-")
                add_number = -1;
            Person person{ surname, name, patronymic };
            PhoneNumber phone{ country, city, number, add_number };
            data.push_back(make_pair(person, phone));
        }
        data_from_file.close();
    }
    friend ostream& operator<<(ostream& out, const PhoneBook& pb);
};

ostream& operator<<(ostream& out, const PhoneBook& pb)
{
    for (const auto& [person, phone] : pb.data)
        out << person << " " << phone << endl;
    return out;
}

int main()
{
    ifstream file("PB.txt");
    PhoneBook book(file);
    cout << book;
    return 0;
}
