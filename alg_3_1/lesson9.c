#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // для кириллицы

///////////////////////////////// ЗАДАНИЕ 1

#define QUEUE_SIZE 10

// один элемент очереди - состоит из приоритета и данных
typedef struct 
{
    int priority;
    int data;
} Node;

// структура Очередь состоит из массива данных, количества элементов а также "указателей" на начало и конец очереди
typedef struct
{
    Node* queue[QUEUE_SIZE];
    int head;
    int tail;
    int items;
} Queue;

// инициализирует очередь (обнуляет)
void initQueue(Queue* q)
{
    for (int i = 0; i < QUEUE_SIZE; ++i)
        q->queue[i] = NULL;
    q->head = 0;
    q->tail = 0;
    q->items = 0;
}

// удаляет из очереди первый элемент
Node* simple_rem(Queue* q)
{
    if (q->items == 0)
        return NULL;
    else 
    {
        int idx = (q->head)++ % QUEUE_SIZE;
        Node* tmp = q->queue[idx];
        q->queue[idx] = NULL;
        (q->items)--;
        return tmp;
    }
}

// добавляет новый элемент в очередь q согласно его приоритету
void pr_ins(Node new_node, Queue* q)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = new_node.data;
    node->priority = new_node.priority;
    int flag;    // место вставки нового элемента

    // сначала обрабатываем случай, если очередь пустая
    if (q->items == 0)
    {
        q->queue[(q->tail)++] = node;
        (q->items)++;
    }
    // и если очередь уже заполнена
    else if (q->items == QUEUE_SIZE)
    {
        printf("%s \n", "Queue is full");
        return;
    }
    // иначе (в очереди есть элементы и есть место для нового)
    else
    {
        int i = 0;      // счётчик цикла
        int idx = 0;    // будет содержать индекс для вставки нового элемента
        Node* tmp;
        // ищем место для вставки
        for (i = q->head; i < q->tail; ++i)
        {
            idx = i % QUEUE_SIZE;
            if (q->queue[idx]->priority > node->priority)
                break;
            else
                idx++; // если прошли всю очередь и не нашли элемент, перед которым вставить, будем вставлять в хвост
        }
        flag = idx % QUEUE_SIZE;
        i++;                     // индекс элемента после места вставки
        // сдвигаем следующие элементы вправо на 1
        while (i <= q->tail)
        {
            idx = i % QUEUE_SIZE;
            tmp = q->queue[idx];
            q->queue[idx] = q->queue[flag];
            q->queue[flag] = tmp;
            i++;
        }
        q->queue[flag] = node;
        (q->items)++;
        (q->tail)++;
    }
}

// добавляет новый элемент в конец очереди
void simple_ins(Node new_node, Queue* q)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = new_node.data;
    node->priority = new_node.priority;

    // сначала обрабатываем случай, если очередь уже заполнена
    if (q->items == QUEUE_SIZE)
    {
        printf("%s \n", "Queue is full");
        return;
    }

    // иначе (в очереди есть место для нового)
    q->queue[q->tail % QUEUE_SIZE] = node;
    (q->tail)++;
    (q->items)++;
}

// удаляет из очереди наиболее приоритетный элемент (чем меньше - тем приоритетней)
Node* pr_rem(Queue* q)
{
    if (q->items == 0)
        return NULL;
    else
    {
        // ищем элемент с лучшим приоритетом, запоминаем его индекс
        int idx_to_del = (q->head) % QUEUE_SIZE;
        int best_priority = (q->queue[idx_to_del])->priority;
        int idx = 0;
        int counter = 0;  // это будет счётчик следующего элемента
        for (int i = q->head; i < q->tail; ++i)
        {
            idx = i % QUEUE_SIZE;
            if (((q->queue[idx])->priority) < best_priority)
            {
                best_priority = ((q->queue[idx])->priority);
                idx_to_del = idx;
                counter = (i + 1);
            }
        }

        Node* tmp = q->queue[idx_to_del];

        if (idx_to_del == ((q->head) % QUEUE_SIZE))
        {
            q->queue[idx_to_del] = NULL;
            (q->head)++;
        }
        else
        {
            int current = idx_to_del;
            // сдвигаем следующие элементы влево на 1, затирая удаляемый
            while (counter <= q->tail)
            {
                q->queue[current % QUEUE_SIZE] = q->queue[counter % QUEUE_SIZE];
                current++;
                counter++;
            }
            (q->tail)--;
        }
        (q->items)--;
        return tmp;
    }
}

// выводит элементы очереди на экран
void printQueue(Queue* q) 
{
    printf("[ ");
    for (int i = 0; i < QUEUE_SIZE; ++i) 
    {
        if (q->queue[i] == NULL)
            printf("[*, *] ");
        else
            printf("[%d, %d] ", q->queue[i]->priority, q->queue[i]->data);
    }
    printf(" ]\n");
}

void task1()
{
    printf("1. Реализация очереди с приоритетным исключением.\nЗаполним всю очередь парами приоритет-значение:\n");
    
    Queue some_queue;
    initQueue(&some_queue);

    simple_ins({ 1, 11 }, &some_queue);
    simple_ins({ 3, 22 }, &some_queue);
    simple_ins({ 4, 33 }, &some_queue);
    simple_ins({ 2, 44 }, &some_queue);
    simple_ins({ 3, 55 }, &some_queue);
    simple_ins({ 4, 66 }, &some_queue);
    simple_ins({ 5, 77 }, &some_queue);
    simple_ins({ 1, 88 }, &some_queue);
    simple_ins({ 2, 99 }, &some_queue);
    simple_ins({ 6, 100 }, &some_queue);
    printQueue(&some_queue);

    printf("Теперь удалим 7 элементов с лучшим приоритетом:\n");
    for (int i = 0; i < 7; ++i) 
    {
        Node* n = pr_rem(&some_queue);
        printf("удалён элемент [%d, %d]\n", n->priority, n->data);
    }
    printQueue(&some_queue);

    printf("Добавим ещё 6 элементов:\n");
    simple_ins({ 1, 110 }, &some_queue);
    simple_ins({ 3, 120 }, &some_queue);
    simple_ins({ 6, 130 }, &some_queue);
    simple_ins({ 2, 600 }, &some_queue);
    simple_ins({ 1, 330 }, &some_queue);
    simple_ins({ 4, 520 }, &some_queue);

    printQueue(&some_queue);

    printf("... и удалим 5 наиболее приоритетных элементов:\n");
    for (int i = 0; i < 5; ++i) 
    {
        Node* n = pr_rem(&some_queue);
        printf("удалён элемент [%d, %d] \n", n->priority, n->data);
    }
    printQueue(&some_queue);

    printf("\n\n");
}

///////////////////////////////// ЗАДАНИЕ 2
#define T char
#define STACK_SIZE 100
#define True 1 == 1
#define False 1 != 1

typedef int boolean;
int cursor = -1;
T Stack[STACK_SIZE];

// добавляет значение в стэк
boolean pushStack(T data) {
    if (cursor < STACK_SIZE) {
        Stack[++cursor] = data;
        return true;
    }
    else {
        printf("%s \n", "Stack overflow");
        return false;
    }
}

// получает значение из стэка
T popStack() {
    if (cursor != -1) {
        return Stack[cursor--];
    }
    else {
        printf("%s \n", "Stack is empty");
        return -1;
    }
}

// переводит число в двоичную запись последовательно деля число на 2 и добавляя остаток от деления слева
void convert_to_bin(int number)
{
    int length = 0;
    while (number != 0)
    {
        // получаем остаток от деления на 2 в виде символа
        char char_to_add{ ((number % 2) == 0) ? '0' : '1' };
        // смещаем то, что уже есть в двоичной записи на 1 знак вправо:
        ++length;
        pushStack(char_to_add);
        number /= 2;
    }
}

// получаем целое положительное число от пользователя в рамках диапазона 0, max
int get_positive_number(const char* text_to_user, int max)
{
    char text_number[256];
    int number = 0;
    do
    {
        printf("%s (целое положительное число не больше %d): ", text_to_user, max);
        scanf("%s", text_number);
        number = atoi(text_number);
    } while (number <= 0 || number > max);
    return (int)number;
}

// Решение первого задания - запрашиваем число и переводим его в двоичную запись
void task2()
{
    printf("2. Перевод числа в двоичную запись при помощи стэка.\n");
    int n = get_positive_number("Введите число", 10000000);
    printf("Это же число в двоичной записи: ");
    convert_to_bin(n);
    while (cursor != -1)
        printf("%c", popStack());
    printf("\n\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    task2();
    return 0;
}