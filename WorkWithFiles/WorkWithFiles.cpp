/* 1. Написать программу, которая создаст два текстовых файла, по 50-100 символов в каждом
 * 2. Написать функцию, «склеивающую» эти файлы, предварительно буферизуя их содержимое в динамически выделенный сегмент памяти нужного размера.
 * 3* Написать программу, которая проверяет присутствует ли указанное пользователем при запуске программы слово в указанном пользователем файле (для простоты работаем только с латиницей).*/

#include <iostream>
#include <fstream>
#include <string>

void createFile(const std::string& filename)
{
    std::ofstream file(filename);          // создаём файл для записи
    if (!file)
        std::cerr << "Error: cannot create " << filename << '\n';
    else
        std::cout << filename << " was created.\n";
    file.close();                          // явно закрываем файл
}

void writeToFile(const std::string& filename, const std::string& text)
{
    std::ofstream file(filename);          // создаём файловую переменную
    file << text;
    std::cout << "Some text has been written to " << filename << "\n";
    file.close();
}

void task1()
{
    std::string file1name{ "File1.txt" };
    std::string file2name{ "File2.txt" };
    
    createFile(file1name);
    std::string text1{ "In the continuing debate on whether one needs to learn C before C++, I am firmly convinced that it is best to go directly to C++.\n" };
    writeToFile(file1name, text1);

    createFile(file2name);
    std::string text2{ "C++ is safer and more expressive,and it reduces the need to focus on low - level techniques.\n" };
    writeToFile(file2name, text2);
}

int main()
{
    task1();
    return 0;
}
