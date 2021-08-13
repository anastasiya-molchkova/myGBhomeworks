/* 1.	Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров 
        и запускать исключение DivisionByZero, если второй параметр равен 0. 
        В функции main выводить результат вызова функции div в консоль, а также ловить исключения. 
   2.	Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, 
        инициализирующий x значением параметра. 
        Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) 
        и имеющий метод set с единственным вещественным параметром a. 
        Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. 
        В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. 
        Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0. 
        В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.
   3.	Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, 
        означающий задание переместиться на соседнюю позицию. 
        Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, 
        и IllegalCommand, если подана неверная команда (направление не находится в нужном диапазоне). 
        Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения. 
        Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов, 
        а также выводящую подробную информацию о всех возникающих ошибках. */

#include <iostream>
#include <string>

/////////////////////// TASK 1

class DivisionByZero
{
public:
    DivisionByZero() {}
    static std::string message;
};

std::string DivisionByZero::message{ "ERROR: division by zero!\n" };

template <typename T>
T div(const T a, const T b)
{
    if (b == 0)
        throw DivisionByZero();
    T result = a / b;
    return result;
}

void task1()
{
    std::cout << "Task 1, with exception of division by zero.\n";
    try
    {
        int n1 = 100;
        int n2 = 6;
        std::cout << "Result of division " << n1 << " by " << n2 << " is ";
        std::cout << div<int>(n1, n2) << std::endl;
        n2 = 0;
        std::cout << "Result of division " << n1 << " by " << n2 << " is ";
        std::cout << div<int>(n1, n2) << std::endl;
    }
    catch (const DivisionByZero& err)
    {
        std::cerr << err.message;
    }
    catch (...)
    {
        std::cerr << "... something bad happened, we don't know what exactly.\n";
    }
    std::cout << std::endl;
}

/////////////////////// TASK 2

class Ex
{
private:
    double x;
public:
    Ex() = delete;
    Ex(const double n): x(n) {}
    double get_parameter() const
    {
        return x;
    }
};

class Bar
{
private:
    double y;
public:
    Bar() : y(0.0) {}
    void set (const double a)
    {
        if (y + a > 100)
            throw Ex(a * y);
        else 
            y = a;
    }
};

// получаем от пользователя целое число
int getNumber(const std::string& text_to_user, const int stop_number)
{
    std::cout << text_to_user << " (" << stop_number << " to stop): ";
    int answer;
    std::cin >> answer;

    while (std::cin.fail() || (std::cin.peek() != '\n'))
    {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Try again, please: ";
        std::cin >> answer;
    }
    std::cin.ignore(32767, '\n');
    return answer;
}

void task2()
{
    std::cout << "Task 2, with an exception in a class constructor.\n";
    Bar bar{ Bar() };
    int n{ -1 };         // параметр для bar.set()
    while (true)
    {
        try 
        {
            n = getNumber("Enter an integer number", 0);
            if (n == 0)
                break;
            bar.set(static_cast<double>(n));
        }
        catch ( const Ex& exception)
        {
            std::cerr << " STOP: exceptional parameter is " << exception.get_parameter() << ", " << n << " + previous parameter for Bar > 100!\n";
        }
        catch (...)
        {
            std::cerr << "... something bad happened, we don't know what exactly.\n";
        }
    }
    std::cout << std::endl;
}

/////////////////////// TASK 3

const int FIELD_SIZE = 10;

enum DIRECTIONS { UP = 1, DOWN, LEFT, RIGHT, MAXdirections };

std::string text_direction(const DIRECTIONS to)
{
    switch (to)
    {
    case DOWN:
        return "DOWN";
    case LEFT:
        return "LEFT";
    case RIGHT:
        return "RIGHT";
    default:
        return "UP";
    }
}

struct Coordinates
{
    int x;
    int y;
};

class OffTheField
{
private:
    DIRECTIONS command;
    Coordinates current_position;
public:
    OffTheField() = delete;
    OffTheField(const DIRECTIONS direction, Coordinates& current_x_y) :
        command(direction), current_position{ current_x_y } {}
    void print_message() const
    {
        std::cerr << "Command " << text_direction(command) << " is imposible for current position (" 
            << current_position.x << ", " << current_position.y << ")!\n";
    }
};

class IllegalCommand
{
private:
    int command;
    Coordinates current_position;
public:
    IllegalCommand() = delete;
    IllegalCommand(const int wrong_direction, Coordinates& current_x_y) :
        command(wrong_direction), current_position{current_x_y} {}
    void print_message() const
    {
        std::cerr << "Command " << command << " is illegal, there is no such direction!\n"
                  << "Current position is: (" << current_position.x << ", " << current_position.y << ")\n";
    }
};

class Robot
{
private:
    Coordinates position { FIELD_SIZE / 2, FIELD_SIZE / 2 };
public:
    Robot() = default;
    void move_to_the_next_position(const int potential_direction)
    {
        if ((potential_direction < DIRECTIONS::UP) || (potential_direction >= DIRECTIONS::MAXdirections))
            throw IllegalCommand(potential_direction, position);
        else
        {
            Coordinates future_coordinates{ position };
            DIRECTIONS move = static_cast<DIRECTIONS>(potential_direction);
            switch (move)
            {
            case UP:
                --future_coordinates.y;
                break;
            case DOWN:
                ++future_coordinates.y;
                break;
            case LEFT:
                --future_coordinates.x;
                break;
            case RIGHT:
                ++future_coordinates.x;
                break;
            default:
                throw IllegalCommand(potential_direction, position);
                break;
            }
            if (future_coordinates.x < 1 || future_coordinates.x > FIELD_SIZE ||
                future_coordinates.y < 1 || future_coordinates.y > FIELD_SIZE)
                throw OffTheField(move, position);
            else
            {
                position.x = future_coordinates.x;
                position.y = future_coordinates.y;
            }
        }
    }
    void print_coordinates()
    {
        std::cout << "current robot position: (" << position.x << ", " << position.y << ")\n";
    }
};

void task3()
{
    std::cout << "Task 3, with a robot management on the field " << FIELD_SIZE << "x" << FIELD_SIZE << ".\n";
    Robot robocop{ Robot() };
    robocop.print_coordinates();
    std::cout << "Move the robot to:\n\tUP - " << UP << "     DOWN - " << DOWN
              << "\n\tLEFT - " << LEFT << "   RIGHT - " << RIGHT << "\n";
    int users_choice;
    while (true)
    {
        users_choice = getNumber("Enter the direction", 0);
        if (users_choice == 0)
            break;
        try
        {
            robocop.move_to_the_next_position(users_choice);
            robocop.print_coordinates();
        }
        catch (const IllegalCommand& err)
        {
            err.print_message();
        }
        catch (const OffTheField& err)
        {
            err.print_message();
        }
        catch (...)
        {
            std::cerr << "... something bad happened, we don't know what exactly.\n";
        }
    }
    std::cout << std::endl;
}

int main()
{
    task1();
    task2();
    task3();

    return 0;
}