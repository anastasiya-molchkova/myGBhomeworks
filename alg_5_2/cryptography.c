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
char* encryption(char* secret_message, int key, char* alphabet, const unsigned int alphabet_size)
{
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, key);

    unsigned int message_len;
    for (message_len = 0; secret_message[message_len] != '\0'; ++message_len);

    char* cryptogram = (char*)malloc(message_len * sizeof(char));
    for (int i = 0; i < message_len; ++i)
        cryptogram[i] = alphabet_code[secret_message[i] - 'A'];
    cryptogram[message_len] = '\0';

    free(alphabet_code);
    return cryptogram;
}

// расшифровывает переданную криптограмму, зашифрованную шифром Цезаря, принимая в качестве параметра ключ-сдвиг
char* decryption(char* cryptogram, int key, char* alphabet, const unsigned int alphabet_size)
{
    char* alphabet_code = (char*)malloc(alphabet_size * sizeof(char));
    cycleShift(alphabet, alphabet_code, alphabet_size, -key);

    unsigned int message_len;
    for (message_len = 0; cryptogram[message_len] != '\0'; ++message_len);

    char* secret_message = (char*)malloc(message_len * sizeof(char));
    for (int i = 0; i < message_len; ++i)
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
    char* cryptogram = encryption(message, cesar_shift, alphabet, alphabet_size);
    puts(cryptogram);

    printf("Расшифровка:\n");
    char* result = decryption(cryptogram, cesar_shift, alphabet, alphabet_size);
    puts(result);

    free(alphabet);
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    //task2();
    return 0;
}