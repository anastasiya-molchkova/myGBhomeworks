/* Домашняя работа к 8 уроку ООП по механизму обработки исключений */

#include <iostream>
#include <string>

/////////////////////// TASK 1
/*   1.	Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров
        и запускать исключение DivisionByZero, если второй параметр равен 0.
        В функции main выводить результат вызова функции div в консоль, а также ловить исключения. */

// класс ошибки для выбрасывания исключения
class DivisionByZero
{
public:
    DivisionByZero() {}
    static std::string message;
};
// определение статической переменной класса вне класса:
std::string DivisionByZero::message{ "ERROR: division by zero!\n" };

// шаблонная функция деления двух чисел
template <typename T>
T div(const T a, const T b)
{
    if (b == 0)                 // делить на ноль нельзя
        throw DivisionByZero();
    T result = a / b;
    return result;
}

// главная функция для выполнения задания №1
void task1()
{
    std::cout << "Task 1, with exception of division by zero.\n";
    try
    {// просто пара примеров вызова шаблонной функции - без исключения и с ним:
        int n1 = 100;
        int n2 = 6;
        std::cout << "Result of division " << n1 << " by " << n2 << " is ";
        std::cout << div<int>(n1, n2) << std::endl;
        
        n2 = 0;
        std::cout << "Result of division " << n1 << " by " << n2 << " is ";
        std::cout << div<int>(n1, n2) << std::endl;
    }
    // обработка известного исключения и всех остальных:
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
/*   2.	Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, 
        инициализирующий x значением параметра. 
        Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) 
        и имеющий метод set с единственным вещественным параметром a. 
        Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. 
        В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. 
        Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0. 
        В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения. */

// класс ошибки для выбрасывания исключения
class Ex
{
private:
    double x;
public:
    Ex() = delete;              // конструктор без параметров запрещён
    Ex(const double n): x(n) {}
    double get_parameter() const
    {
        return x;
    }
};

// класс Bar, метод set которого может выбрасывать исключения
class Bar
{
private:
    double y;
public:
    Bar() : y(0.0) {}
    void set (const double a)
    { // метод реализован по условию задания
        if (y + a > 100)     
            throw Ex(a * y);
        else 
            y = a;
    }
};

// функция для получения от пользователя целого числа без примесей
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

// главная функция для выполнения задания №2
void task2()
{
    std::cout << "Task 2, with an exception in a class method.\n";
    Bar bar{ Bar() };    // создаём метод класса по конструктору без параметров, параметр класса обнулён
    int n{ -1 };         // параметр для bar.set()
    while (true)
    {
        try 
        {// получаем параметр для передачи в bar.set() от пользователя, пока он не введёт 0
            n = getNumber("Enter an integer number", 0);
            if (n == 0)
                break;
            bar.set(static_cast<double>(n));
        }
        // обработка известного исключения и всех остальных:
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
/*   3.	Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод,
        означающий задание переместиться на соседнюю позицию.
        Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки,
        и IllegalCommand, если подана неверная команда (направление не находится в нужном диапазоне).
        Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения.
        Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов,
        а также выводящую подробную информацию о всех возникающих ошибках. */

// я решила сделать параметры поля и набор направлений движения вне класса робота, т.к. они нужны и для классов-исключений тоже
const int FIELD_SIZE = 10;

enum DIRECTIONS { UP = 1, DOWN, LEFT, RIGHT, MAXdirections };

// функция, которая позволяет напечатать направление движения, переводя его в строку
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

// структура координат на поле. Начало координат - в верхнем левом угле 
struct Coordinates
{
    int x;
    int y;
};

// класс ошибки для выбрасывания исключения "Выход за пределы поля"
class OffTheField
{
private:
    DIRECTIONS command;
    Coordinates current_position;
public:
    OffTheField() = delete;    // конструктор без параметров - запрещён
    OffTheField(const DIRECTIONS direction, const Coordinates& current_x_y) :
        command(direction), current_position{ current_x_y } {}
    // вывод сообщения об ошибке должен сообщать о переданной команде и текущих координатах
    void print_message() const
    {
        std::cerr << "Command " << text_direction(command) << " is imposible for current position (" 
            << current_position.x << ", " << current_position.y << ")!\n";
    }
};

// класс ошибки для выбрасывания исключения "Несуществующее направление движения"
class IllegalCommand
{
private:
    int command;
    Coordinates current_position;
public:
    IllegalCommand() = delete;  // конструктор без параметров - запрещён
    IllegalCommand(const int wrong_direction, const Coordinates& current_x_y) :
        command(wrong_direction), current_position{current_x_y} {}
    // вывод сообщения об ошибке должен сообщать о переданной команде и текущих координатах
    void print_message() const
    {
        std::cerr << "Command " << command << " is illegal, there is no such direction!\n"
                  << "Current position is: (" << current_position.x << ", " << current_position.y << ")\n";
    }
};

class Robot
{
private:
    Coordinates position { FIELD_SIZE / 2, FIELD_SIZE / 2 };  // по умолчанию робот находится в центре поля
public:
    Robot() = default;  // конструктор по умолчанию для создания робота без параметров
    
    // главный метод класса, который может выбрасывать исключения
    void move_to_the_next_position(const int potential_direction)
    {
        // если полученную команду нельзя трактовать как направление из перечня направлений
        if ((potential_direction < DIRECTIONS::UP) || (potential_direction >= DIRECTIONS::MAXdirections))
            throw IllegalCommand(potential_direction, position);
        
        else // полученную команду можно трактовать как направление
        {
            DIRECTIONS move = static_cast<DIRECTIONS>(potential_direction);
            Coordinates future_coordinates{ position };  // координаты после выполнения команды
            switch (move)
            {
            case UP:
                // движение вверх означает уменьшение координаты по вертикали, так как ось координат Y направлена вниз
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
            // проверяем, случился ли выход за пределы поля после исполнения команды
            if (future_coordinates.x < 1 || future_coordinates.x > FIELD_SIZE ||
                future_coordinates.y < 1 || future_coordinates.y > FIELD_SIZE)
                throw OffTheField(move, position);
            else  // всё нормально, остались в пределах поля -> изменяем текущие координаты робота
            {
                position.x = future_coordinates.x;
                position.y = future_coordinates.y;
            }
        }
    }
    // метод для вывода текущих координат робота на экран
    void print_coordinates() const
    {
        std::cout << "current robot position: (" << position.x << ", " << position.y << ")\n";
    }
};

// главная функция для выполнения задания №3
void task3()
{
    std::cout << "Task 3, with a robot management on the field " << FIELD_SIZE << " x " << FIELD_SIZE << ".\n";
    Robot robocop{ Robot() };
    robocop.print_coordinates();
    // краткая инструкция для пользователя, как управлять роботом:
    std::cout << "Move the robot to:\n\tUP - " << UP << "     DOWN - " << DOWN
              << "\n\tLEFT - " << LEFT << "   RIGHT - " << RIGHT << "\n";
    int users_choice;
    while (true)  // пока пользователю не надоест
    {
        // останавливаемся, если пользователь введёт 0
        users_choice = getNumber("Enter the direction", 0);
        if (users_choice == 0)
            break;
        try
        {
            robocop.move_to_the_next_position(users_choice);
            robocop.print_coordinates();
        }
        // обработка известных исключений и всех остальных:
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

// MAIN
int main()
{
    task1();
    task2();
    task3();
    return 0;
}