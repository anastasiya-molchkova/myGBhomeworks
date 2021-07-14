/* 1) Реализовать обход в глубину с использованием стека
   2) Моделируем робот поисковой системы. Дан готовый простой граф с циклическими связями. 
      Нужно обойти этот граф двумя способами и подсчитать количество ссылок на каждый из узлов графа (полустепень захода).
            обход графа рекурсивной функцией (с подсчётом только смежных со стартовой вершин)
            обход графа по матрице смежности (с подсчётом всех вершин графа) 
      В конце обхода вывести два получившихся списка всех узлов в порядке уменьшения количества ссылок на них.*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // для кириллицы

// НУЖНЫЙ КОД С УРОКОВ:

#define True (1 == 1)
#define False (1 != 1)

typedef int boolean;

// создаёт 2D массив
int** init2DArray(int rows, int cols)
{
    int** array = (int**)calloc(sizeof(int*), rows);
    for (int i = 0; i < rows; ++i)
        *(array + i) = (int*)calloc(sizeof(int), cols);
    return array;
}

// заполняет 2D массив случайными числами
void fill2DarrayRandom(int** array, int rows, int cols, const unsigned max)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            *(*(array + i) + j) = rand() % max;
}

int get2dInt(int** array, const int row, const int col)
{
    return *((*(array + row)) + col);
}

void set2dInt(int** array, const int row, const int col, int value)
{
    *((*(array + row)) + col) = value;
}

// СТЭК на основе односвязного списка (взято из репозитория)

#define T int

typedef struct OneLinkNode
{
    int data;
    struct OneLinkNode* next;
} OneLinkNode;

typedef struct
{
    OneLinkNode* head;
    int size;
} OneLinkList;

void initOneLinkList(OneLinkList* lst)
{
    lst->head = NULL;
    lst->size = 0;
}

boolean pushOneLinkStack(OneLinkList* stack, T value) {
    OneLinkNode* tmp = (OneLinkNode*)malloc(sizeof(OneLinkNode));
    if (tmp == NULL) {
        printf("Stack overflow \n");
        return false;
    }
    tmp->data = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

T popOneLinkStack(OneLinkList* stack) {
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    OneLinkNode* tmp = stack->head;
    T data = stack->head->data;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

// ОЧЕРЕДЬ НА ОСНОВЕ ДВУСВЯЗНОГО СПИСКА (взято из репозитория)

typedef struct TwoLinkNode {
    int dat;
    struct TwoLinkNode* next;
    struct TwoLinkNode* prev;
} TwoLinkNode;

typedef struct {
    struct TwoLinkNode* head;
    struct TwoLinkNode* tail;
    int size;
} TwoLinkList;

void initTwoLinkList(TwoLinkList* lst) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

// добавление элемента в хвост очереди
boolean TwoLinkEnqueue(TwoLinkList* queue, T value) {
    TwoLinkNode* tmp = (TwoLinkNode*)malloc(sizeof(TwoLinkNode));
    if (tmp == NULL) {
        printf("Out of memory! \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = NULL;
    tmp->prev = queue->tail;

    if (queue->tail != NULL) {
        queue->tail->next = tmp;
    }
    if (queue->head == NULL) {
        queue->head = tmp;
    }

    queue->tail = tmp;
    queue->size++;
    return true;
}

// извлечение элемента из головы очереди
T TwoLinkDequeue(TwoLinkList* queue) {
    if (queue->size == 0) {
        printf("Queue is empty \n");
        return -1;
    }
    TwoLinkNode* tmp = queue->head;
    T data = queue->head->dat;

    queue->head = queue->head->next;

    if (queue->head != NULL) {
        queue->head->prev = NULL;
    }
    if (tmp == queue->tail) {
        queue->tail = NULL;
    }

    free(tmp);
    queue->size--;
    return data;
}
// ЗДЕСЬ ЗАКАНЧИВАЕТСЯ ЗАИМСТВОВАННЫЙ КОД И НАЧИНАЕТСЯ МОЙ

///////////////////// ЗАДАНИЕ 1

// печатает матрицу смежности
void printAdjMatrix(int** array, int nodes)
{
    printf("Матрица смежности: \n   ");
    // печать номеров столбцов
    for (int j = 0; j < nodes; ++j)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < nodes; ++i)
    {
        printf("%2d ", i);   // печать номеров строк
        for (int j = 0; j < nodes; ++j)
            printf("%2d ", *(*(array + i) + j));
        printf("\n");
    }
}

// обход графа в глубину со стэком. На входе матрица смежности, количество вершин и стартовая вершина для обхода:
void depthTravers(int** matrix, const int nodes, const int start)
{
    // в стэке будем держать вершины, для которых нужно обойти смежные
    OneLinkList* stack = (OneLinkList*)malloc(sizeof(OneLinkList));
    initOneLinkList(stack);  // изначально стэк пуст

    // также нам понадобится массив посещённых вершин. Там единицей будем помечать посещённые вершины
    int* visited = (int*)calloc(nodes, sizeof(int));  // изначально массив обнулён

    // добавляем начальную вершину в стэк, отмечаем как посещённую и выводим на экран
    pushOneLinkStack(stack, start);
    visited[start] = 1;
    printf("%d ", start);

    int current_node = start;
    while (stack->size != 0)
    {
        current_node = popOneLinkStack(stack);
        for (int next_node = 0; next_node < nodes; ++next_node)
            // если есть путь в соседнюю вершину и она не посещалась
            if ((get2dInt(matrix, current_node, next_node) == 1) && !visited[next_node])
            {
                visited[next_node] = 1;
                printf("%d ", next_node);
                pushOneLinkStack(stack, next_node);
            }
    }

    free(stack);
}

// создаёт случайный граф для заданного количества вершин и обходит его в глубину из нескольких вершин
void task1()
{
    printf("1. Обход графа в глубину при помощи стэка.\n\n");

    const int nodes = 10;
    int** graph = init2DArray(nodes, nodes);
    fill2DarrayRandom(graph, nodes, nodes, 2);
    printAdjMatrix(graph, nodes);

    printf("Пути обхода графа из нескольких вершин:\n");
    depthTravers(graph, nodes, 0);
    printf("\n");
    depthTravers(graph, nodes, 3);
    printf("\n");
    depthTravers(graph, nodes, 4);

    printf("\n\n");

    // освобождаем выделенную под граф память:
    for (int i = 0; i < nodes; ++i)
        free(graph[i]);
    free(graph);
}

///////////////////// ЗАДАНИЕ 2

// создаёт симметричную матрицу смежности для простого графа (без кратных рёбер и петель)
int** initSimpleGraph(const int nodes)
{
    int** array = (int**)calloc(nodes, sizeof(int*));
    for (int i = 0; i < nodes; ++i)
        *(array + i) = (int*)calloc(nodes, sizeof(int*));

    for (int i = 0; i < nodes; ++i)
        for (int j = 0; j < nodes; ++j)
        {
            if (i < j)
                set2dInt(array, i, j, rand() % 2);
            else if (i > j)
                set2dInt(array, i, j, get2dInt(array, j, i));
            // иначе (i == j) - петля, оставляем 0
        }
    return array;
}

// рекурсивная функция обхода графа в ширину, количество подсчётов захода в каждую вершину считается в массиве edges
void widthTraversRecursive(int** matrix, TwoLinkList* queue, int* visited, int* edges, int start, const int size)
{
    // ищем смежные вершины, считаем их и ставим в очередь для подсчёта их рёбер
    for (int next = 0; next < size; ++next)
        if ((get2dInt(matrix, start, next) == 1))
        {
            ++edges[start];             // считаем ребро
            if (!visited[next])
            {
                visited[next] = 1;      // посещаем смежные
                TwoLinkEnqueue(queue, next);  // добавляем в очередь, чтобы посчитать рёбра для неё
            }
        }

    // переходим к следующей вершине в очереди
    if (queue->size > 0)
        widthTraversRecursive(matrix, queue, visited, edges, TwoLinkDequeue(queue), size);
}

// обход графа по матрице смежности с подсчётом рёбер для каждой вершины (полустепень захода)
int* TraversByMatrix(int** matrix, const int size)
{
    int* visited = (int*)calloc(size, sizeof(int));  // изначально массив обнулён
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (get2dInt(matrix, i, j) == 1)
                ++visited[j]; // т.к. матрица симметрична относительно диагонали считаем рёбра только как входящие
    return visited;
}

// структура номер вершины - количество смежных с ней рёбер 
typedef struct
{
    int node;
    int edges;
} NodeEdges;

// сортирует массив вершин сортировкой вставками от наибольшего количества рёбер к наименьшему
void sort_by_inserts(NodeEdges* array, int len)
{
    NodeEdges temp;
    int pos;
    for (int i = 1; i < len; ++i)
    {
        temp.node = array[i].node;
        temp.edges = array[i].edges;
        pos = i - 1;
        while (pos >= 0 && array[pos].edges < temp.edges)
        {
            array[pos + 1].node = array[pos].node;
            array[pos + 1].edges = array[pos].edges;
            pos--;
        }
        array[pos + 1].node = temp.node;
        array[pos + 1].edges = temp.edges;
    }
}

// выводит на экран номер вершины и количество смежных с ней рёбер
void printNodeEdge(NodeEdges* a)
{
    printf("вершина %d - %d рёбер\n", a->node, a->edges);
}

// выводит на экран список вершин и количество смежных с ними рёбер
void printResult(NodeEdges* array, int len)
{
    for (int i = 0; i < len; ++i)
        printNodeEdge(array + i);
}

// обрабатывает входящий массив полустепеней захода - сортирует и печатает
void makeTraversResult(int* array, const int nodes)
{
    // результатом должен стать список номеров вершин и количеств входящих рёбер, отсортированный по убыванию
    // поэтому, чтобы не потерять номера вершин, переделаем массив в массив структур "номер вершины - количество рёбер"
    NodeEdges* result = (NodeEdges*)calloc(nodes, sizeof(NodeEdges));
    for (int i = 0; i < nodes; ++i)
    {
        result[i].node = i;
        result[i].edges = array[i];
    }
    sort_by_inserts(result, nodes);
    printResult(result, nodes);
    printf("\n\n");
    free(result);
}

// создаёт случайный простой граф для заданного количества вершин, обходит его двумя способами с подсчётом количества ссылок на каждую вершину
void task2()
{
    // задаём граф количеством вершин, генерируем матрицу смежности по условию
    const int nodes = 8;
    int** graph = initSimpleGraph(nodes);
    printAdjMatrix(graph, nodes);

    printf("\n2. Обход простого графа рекурсивно.\n\n");

    // нам понадобится массив для отметки посещённых вершин
    int* visited = (int*)calloc(nodes, sizeof(int));    // изначально массив обнулён
    // и массив для подсчёта полустепеней захода
    int* rec_edges = (int*)calloc(nodes, sizeof(int));  // изначально массив обнулён
    // очередь из вершин должна не зависить от экземпляра функции, поэтому создаём её здесь
    TwoLinkList* queue = (TwoLinkList*)malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    int start = 0;
    visited[start] = 1;

    widthTraversRecursive(graph, queue, visited, rec_edges, start, nodes);
    makeTraversResult(rec_edges, nodes);

    printf("3. Обход простого графа по матрице смежности.\n\n");

    int* edges = TraversByMatrix(graph, nodes);
    makeTraversResult(edges, nodes);

    // финальная зачистка:
    free(visited);
    free(rec_edges);
    free(edges);
    free(queue);
    // и, наконец, освобождаем выделенную память под граф:
    for (int i = 0; i < nodes; ++i)
        free(graph[i]);
    free(graph);
}

// а вот и MAIN
int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    task2();
    return 0;
}