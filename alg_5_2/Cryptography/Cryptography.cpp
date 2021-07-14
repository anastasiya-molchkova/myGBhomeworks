/* 1. Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
   2. Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//////////////////// ЗАДАНИЕ 1

// вспомогательная функция для сдвига алфавита, рекурсивно считаем "а по модулю b" применительно к размеру массива
int mod(int a, int b)
{
    if (a >= b)
        return mod(a - b, b);
    if (a < 0)
        return mod(b + a, b);
    return a;
}

// циклический сдвиг букв массива на переданную величину (если положительный сдвиг - влево, отрицательный - вправо)
void cycleShift(const char* input_arr, char* output_arr, const unsigned int size, const int shift)
{
    for (unsigned int i = 0; i < size; ++i)
        output_arr[i] = input_arr[mod(i + shift, size)];
}

// зашифровывает переданное сообщение шифром Цезаря, принимая в качестве параметра ключ-сдвиг
char* cesarEncryption(const char* secret_message, const int key, const char* alphabet, const unsigned int alphabet_size)
{
    // alphabet_code - сдвинутый на key символов алфавит. Первый символ соответствует А, второй - В, и так далее
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, key);

    unsigned int message_len;   // длина сообщения
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    // cryptogram - закодированное новым алфавитом сообщение secret_message
    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    for (unsigned int i = 0; i < message_len; ++i)
        cryptogram[i] = alphabet_code[secret_message[i] - 'A'];
    cryptogram[message_len] = '\0';

    free(alphabet_code);
    return cryptogram;
}

// расшифровывает переданную криптограмму, зашифрованную шифром Цезаря, принимая в качестве параметра ключ-сдвиг
char* cesarDecryption(const char* cryptogram, const int key, const char* alphabet, const unsigned int alphabet_size)
{
    // alphabet_code - дешифровка алфавита, то есть какие буквы использовать для расшифровки криптограммы, что вместо A и т.д.
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, -key);

    unsigned int message_len;   // длина сообщения
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

    // secret_message - исходное сообщение, которое разгадываем, подставляя вместо букв криптограммы их расшифровки из alphabet_code
    char* secret_message = (char*)malloc(message_len * sizeof(char));
    for (unsigned int i = 0; i < message_len; ++i)
        secret_message[i] = alphabet_code[cryptogram[i] - 'A'];
    secret_message[message_len] = '\0';
    
    free(alphabet_code);
    return secret_message;
}

// для заданного алфавита производить шифрование и расшифровку Цезаря с заданным ключом
void task1()
{
    printf("1. Шифрование и расшифровка Цезаря\n\n");

    // задаём алфавит:
    const unsigned int alphabet_size = 26;
    char* alphabet = (char*)malloc(alphabet_size * sizeof(char));
    alphabet[0] = 'A';
    for (int i = 1; i < alphabet_size; ++i)
        alphabet[i] = alphabet[0] + i;

    printf("Исходное сообщение:\n");
    const unsigned int max_message_size = 500;
    char message[max_message_size] = "THISISASECRETMESSAGEFORCESARENCRYPTION";
    puts(message);
    
    const int cesar_shift = 3;   // сдвиг алфавита для шифрования Цезаря

    printf("Криптограмма:\n");
    char* cryptogram = cesarEncryption(message, cesar_shift, alphabet, alphabet_size);
    puts(cryptogram);

    printf("Расшифровка:\n");
    char* result = cesarDecryption(cryptogram, cesar_shift, alphabet, alphabet_size);
    puts(result);
    printf("\n");

    free(alphabet);
}

//////////////////// ЗАДАНИЕ 2

// создаёт 2D массив символов
char** init2DArray(const int rows, const int cols)
{
    char** array = (char**)calloc(sizeof(char*), rows);
    for (int i = 0; i < rows; ++i)
        *(array + i) = (char*)calloc(sizeof(char), cols);
    return array;
}

// возвращает символ из двумерного массива символов по его координатам
char get2dChar(char** array, const int row, const int col)
{
    return *((*(array + row)) + col);
}

// изменяет значение для переданной строки и столбца в двумерном массиве символов на переданное значение letter
void set2dChar(char** array, const int row, const int col, const char letter)
{
    *((*(array + row)) + col) = letter;
}

// зашифровывает переданное сообщение перестановками по передаваемому ключевому слову
// для этого искходное сообщение построчно записывается в двумерный массив, его столбцы перемешиваются 
// по порядку, заданному в ключевом слове и криптограмма считывается по столбцам.
char* shuffleEncryption(const char* secret_message, const char* key_word)
{
    unsigned int message_len;  // длина сообщения
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    unsigned int columns_num;  // количество столбцов - длина ключевого слова
    for (columns_num = 0; key_word[columns_num] != '\0'; ++columns_num);

    unsigned int rows_num;     // количество строк в кодирующем массиве
    rows_num = (message_len % columns_num == 0) ? (message_len / columns_num) : (message_len / columns_num + 1);

    // создаём кодирующий двумерный массив, записываем туда сообщение построчно:
    char** encoding_array = init2DArray(rows_num, columns_num);
    for (unsigned int i = 0; i < rows_num; ++i)
        for (unsigned int j = 0; j < columns_num; ++j)
            set2dChar(encoding_array, i, j, secret_message[i * columns_num + j]);

    // создаём криптограмму, считывая её из кодирующего массива по столбцам в порядке, определённом ключевым словом
    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    unsigned int counter = 0;             // счётчик использованных букв из ключевого слова
    unsigned int idx = 0;                 // индекс для записи очередного символа в криптограмму
    char letter = 'A'; 
    while (counter < columns_num)         // будем перебирать буквы алфавита пока не встретим их все в ключевом слове
    {
        // цикл по символам ключевого слова = цикл по столбцам кодирующего массива
        for (unsigned int j = 0; j < columns_num; ++j)  
            if (key_word[j] == letter)    // нашли соответствующий этой букве столбец j
            {   // считываем этот столбец в криптограмму
                for (unsigned int i = 0; i < rows_num; ++i)
                    cryptogram[idx++] = get2dChar(encoding_array, i, j);
                ++counter;                // использовали ещё одну букву ключевого слова
                break;
            }
        ++letter;                         // переходим к следующей букве
    }
    cryptogram[message_len] = '\0';

    // освобождаем память, выделенную под кодирующий массив, он нам больше не нужен
    for (unsigned int i = 0; i < rows_num; ++i)
        free(encoding_array[i]);
    free(encoding_array);

    return cryptogram;
}

// расшифровывает переданное сообщение перестановками по передаваемому ключевому слову
char* shuffleDecryption(const char* cryptogram, const char* key_word)
{
    unsigned int message_len;  // длина сообщения
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

    unsigned int columns_num;  // количество столбцов вспомогательного двумерного массива - длина ключевого слова
    for (columns_num = 0; key_word[columns_num] != '\0'; ++columns_num);

    unsigned int rows_num;     // количество строк вспомогательного двумерного массива
    rows_num = (message_len % columns_num == 0) ? (message_len / columns_num) : (message_len / columns_num + 1);

    // создаём двумерный массив для расшифровки, записывая туда криптограмму по столбцам
    char** shuffle_array = init2DArray(rows_num, columns_num);
    for (unsigned int i = 0; i < rows_num; ++i)
        for (unsigned int j = 0; j < columns_num; ++j)
            set2dChar(shuffle_array, i, j, cryptogram[i + j * rows_num]);

    // в result будем считывать расшифрованное сообщение по строкам в хитром порядке столбцов
    char* result = (char*)malloc(message_len * sizeof(char));
    unsigned int counter = 0;             // счётчик столбцов - использованных букв из ключевого слова
    char letter = 'A';
    while (counter < columns_num)         // будем перебирать буквы алфавита пока не встретим их все в ключевом слове
    {
        for (unsigned int j = 0; j < columns_num; ++j)
            if (key_word[j] == letter)    // нашли соответствующий этой букве столбец j
            {
                // считываем очередной по порядку столбец в соответствующие столбцу j места расшифровки
                for (unsigned int i = 0; i < rows_num; ++i)
                    result[i * columns_num + j] = get2dChar(shuffle_array, i, counter);
                ++counter;                // использовали ещё одну букву ключевого слова
                break;
            }
        ++letter;                         // переходим к следующей букве
    }
    result[message_len] = '\0';

    // освобождаем память, выделенную под кодирующий массив, он нам больше не нужен
    for (unsigned int i = 0; i < rows_num; ++i)
        free(shuffle_array[i]);
    free(shuffle_array);

    return result;
}

// шифрует строку перестановками по ключевому слову, расшифровывает криптограмму с помощью этого же слова
void task2()
{
    printf("2. Шифрование и расшифровка перестановками\n\n");

    printf("Исходное сообщение:\n");
    const unsigned int max_message_size = 100;
    char message[max_message_size] = "THISISASECRETMESSAGEFORSHUFFLEENCRYPTION";
    puts(message);

    char key_word[] = "BLACK";   // ключевое слово для шифрования и расшифровки

    printf("Криптограмма:\n");
    char* cryptogram = shuffleEncryption(message, key_word);
    puts(cryptogram);

    printf("Разгаданное сообщение:\n");
    char* unraveled_message = shuffleDecryption(cryptogram, key_word);
    puts(unraveled_message);
    printf("\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    task2();
    return 0;
}
