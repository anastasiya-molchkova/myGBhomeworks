#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//////////////////// ЗАДАНИЕ 1

// вспомогательная функция, рекурсивно считаем "а по модулю b" применительно к размеру массива
int mod(int a, int b)
{
    if (a >= b)
        return mod(a - b, b);
    if (a < 0)
        return mod(b + a, b);
    return a;
}

// сдвиг букв массива влево на переданную величину
void cycleShift(char* input_arr, char* output_arr, const unsigned int size, const int shift)
{
    for (size_t i = 0; i < size; ++i)
        output_arr[i] = input_arr[mod(i + shift, size)];
}

// зашифровывает переданное сообщение шифром Цезаря, принимая в качестве параметра ключ-сдвиг
char* cesarEncryption(char* secret_message, int key, char* alphabet, const unsigned int alphabet_size)
{
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, key);

    unsigned int message_len;
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    for (unsigned int i = 0; i < message_len; ++i)
        cryptogram[i] = alphabet_code[secret_message[i] - 'A'];
    cryptogram[message_len] = '\0';

    free(alphabet_code);
    return cryptogram;
}

// расшифровывает переданную криптограмму, зашифрованную шифром Цезаря, принимая в качестве параметра ключ-сдвиг
char* cesarDecryption(char* cryptogram, int key, char* alphabet, const unsigned int alphabet_size)
{
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, -key);

    unsigned int message_len;
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

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

    const unsigned int alphabet_size = 26;
    char* alphabet = (char*)malloc(alphabet_size * sizeof(char));
    alphabet[0] = 'A';
    for (int i = 1; i < alphabet_size; ++i)
        alphabet[i] = alphabet[0] + i;

    printf("Исходное сообщение:\n");
    const unsigned int max_message_size = 500;
    char message[max_message_size] = "THISISASECRETMESSAGEFORCESARENCRYPTION";
    puts(message);

    const int cesar_shift = 3;

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

// создаёт 2D массив
char** init2DArray(int rows, int cols)
{
    char** array = (char**)calloc(sizeof(char*), rows);
    for (int i = 0; i < rows; ++i)
        *(array + i) = (char*)calloc(sizeof(char), cols);
    return array;
}

char get2dChar(char** array, const int row, const int col)
{
    return *((*(array + row)) + col);
}

void set2dChar(char** array, const int row, const int col, char letter)
{
    *((*(array + row)) + col) = letter;
}

// зашифровывает переданное сообщение перестановками по передаваемому ключевому слову
char* shuffleEncryption(char* secret_message, char* key_word)
{
    unsigned int message_len;  // длина сообщения
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    unsigned int columns_num;
    for (columns_num = 0; key_word[columns_num] != '\0'; ++columns_num);

    unsigned int rows_num;
    rows_num = (message_len % columns_num == 0) ? (message_len / columns_num) : (message_len / columns_num + 1);

    char** initial_array = init2DArray(rows_num, columns_num);
    for (unsigned int i = 0; i < rows_num; ++i)
        for (unsigned int j = 0; j < columns_num; ++j)
            set2dChar(initial_array, i, j, secret_message[i * columns_num + j]);

    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    unsigned int counter = 0;
    unsigned int idx = 0;
    char letter = 'A';
    while (letter <= 'Z' && counter < columns_num)
    {
        for (unsigned int j = 0; j < columns_num; ++j)
            if (key_word[j] == letter)
            {
                for (unsigned int i = 0; i < rows_num; ++i)
                    cryptogram[idx++] = get2dChar(initial_array, i, j);
                ++counter;
                break;
            }
        ++letter;
    }
    cryptogram[message_len] = '\0';

    for (unsigned int i = 0; i < rows_num; ++i)
        free(initial_array[i]);
    free(initial_array);

    return cryptogram;
}

// расшифровывает переданное сообщение перестановками по передаваемому ключевому слову
char* shuffleDecryption(char* cryptogram, char* key_word)
{
    unsigned int message_len; // длина сообщения
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

    unsigned int columns_num;
    for (columns_num = 0; key_word[columns_num] != '\0'; ++columns_num);

    unsigned int rows_num;
    rows_num = (message_len % columns_num == 0) ? (message_len / columns_num) : (message_len / columns_num + 1);

    char** shuffle_array = init2DArray(rows_num, columns_num);
    for (unsigned int i = 0; i < rows_num; ++i)
        for (unsigned int j = 0; j < columns_num; ++j)
            set2dChar(shuffle_array, i, j, cryptogram[i + j * rows_num]);

    char* result = (char*)malloc(message_len * sizeof(char));
    unsigned int counter = 0;
    char letter = 'A';
    while (letter <= 'Z' && counter < columns_num)
    {
        for (unsigned int j = 0; j < columns_num; ++j)
            if (key_word[j] == letter)
            {
                unsigned int column = 0;
                while (key_word[column] != letter)
                    ++column;
                for (unsigned int i = 0; i < rows_num; ++i)
                    result[i * columns_num + column] = get2dChar(shuffle_array, i, counter);
                ++counter;
                break;
            }
        ++letter;
    }
    result[message_len] = '\0';

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

    //free(cryptogram);
    //free(unraveled_message);
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    task2();
    return 0;
}