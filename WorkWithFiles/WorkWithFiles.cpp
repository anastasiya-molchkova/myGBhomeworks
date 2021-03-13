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

void task1(const std::string& filename1, const std::string& filename2)
{
    createFile(filename1);
    std::string text1{ "In the continuing debate on whether one needs to learn C before C++, I am firmly convinced that it is best to go directly to C++.\n" };
    writeToFile(filename1, text1);

    createFile(filename2);
    std::string text2{ "C++ is safer and more expressive,and it reduces the need to focus on low - level techniques.\n" };
    writeToFile(filename2, text2);
}

std::string readFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string textFromFile;
    std::getline(file, textFromFile);
    std::cout << "Text \""<< textFromFile <<"\" has been read from " << filename << "\n";
    file.close();
    return textFromFile;
}

void task2(const std::string& filename1, const std::string& filename2, const std::string& resultFilename)
{
    std::string text1{ readFromFile(filename1) };
    std::string text2{ readFromFile(filename2) };

    // динамически выделяем память под буферный текст из двух файлов: 
    unsigned howManyChars = text1.length() + text2.length();
    char* bufferText = new char[howManyChars + 2];           //  2 - дополнительныые элементы под разделитель двух текстов и терминальный нуль

    // получаем буферный текст из двух
    for (size_t i = 0; i < text1.length(); ++i)
        bufferText[i] = text1[i];
    bufferText[text1.length()] = '\n';                      // чтобы разделить два текста
    for (size_t i = 0; i < text2.length(); ++i)
        bufferText[i + text1.length() + 1] = text2[i];
    bufferText[howManyChars + 1] = '\0';

    createFile(resultFilename);
    writeToFile(resultFilename, bufferText);

    delete[] bufferText;
}

int main()
{
    std::string filename1{ "File1.txt" };
    std::string filename2{ "File2.txt" };
    task1(filename1, filename2);

    std::string resultFile{ "Result.txt" };
    task2(filename1, filename2, resultFile);

    return 0;
}
