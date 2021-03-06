#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>     // для abs()

/////////////////////////// НИЖЕ НУЖНЫЙ КОД С УРОКОВ
#define True (1 == 1)
#define False (1 != 1)
typedef int boolean;

typedef struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
} BinTreeIntNode;

// добавляет значение в бинарное дерево
BinTreeIntNode* treeInsert(BinTreeIntNode* t, int data)
{
    BinTreeIntNode* newNode;
    newNode = (BinTreeIntNode*)malloc(sizeof(BinTreeIntNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    BinTreeIntNode* current = t;
    BinTreeIntNode* parent = t;
    if (t == NULL)
        t = newNode;
    else
        while (current->key != data)
        {
            parent = current;
            if (current->key > data)
            {
                current = current->left;
                if (current == NULL)
                {
                    parent->left = newNode;
                    return t;
                }
            }
            else
            {
                current = current->right;
                if (current == NULL)
                {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    return t;
}

// печатает бинарное дерево в виде скобочной последовательности
void printBinTree(BinTreeIntNode* root)
{
    if (root)
    {
        printf("%d", root->key);
        if (root->left || root->right)
        {
            printf("(");
            if (root->left)
                printBinTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printBinTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

//!!!ЗДЕСЬ ЗАКАНЧИВАЕТСЯ НЕ МОЙ КОД И НАЧИНАЕТСЯ МОЙ!!!

/////////////////////////// ЗАДАНИЕ 1

// вычисляет наибольшее из двух чисел
int max(int n1, int n2)
{
    if (n1 >= n2)
        return n1;
    return n2;
}

// рекурсивно вычисляет высоту переданного бинарного дерева
int get_height(BinTreeIntNode* tree)
{
    if (tree == NULL)
        return 0;
    else
        return 1 + max(get_height(tree->right), get_height(tree->left));
}

// проверяет простую сбалансированность переданного бинарного дерева (высоты двух поддеревьев отличаются не больше, чем на 1)
boolean check_balance(BinTreeIntNode* tree)
{
    if ((tree->left == NULL) && (tree->right == NULL))
        return True;

    int left_height = get_height(tree->left);
    int right_height = get_height(tree->right);
    if (abs(left_height - right_height) <= 1)
        return True;

    return False;
}

/////////////////////////// ЗАДАНИЕ 2

// рекурсивная функция построения случайного бинарного дерева. 
// принимает ссылку на максимальное количество вершин и максимальное значение ключа 
BinTreeIntNode* build_random_binary_tree(int* max_nodes, const int max_value)
{
    if (*max_nodes <= 0)
        return NULL;     // иначе мы можем наплодить лишних вершин (из-за рекурсивности ниже)

    // сначала делаем корень дерева/поддерева:
    BinTreeIntNode* root = (BinTreeIntNode*)malloc(sizeof(BinTreeIntNode));
    root->key = rand() % max_value;
    --(*max_nodes);

    // случайным образом определяем количество ветвей для этого корня. Но ограничиваемся оставшимся количеством вершин:
    int children = (*max_nodes > 1) ? (rand() % 3) : ((*max_nodes == 1) ? 1 : 0);

    // и далее поступаем в зависимости от того, сколько нужно ветвей:
    if (children == 0)
    {
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (children == 1)
    {   // случайно определяем, правое или левое дерево строим
        if (rand() % 2)
        {
            root->left = NULL;
            root->right = build_random_binary_tree(max_nodes, max_value);
        }
        else
        {
            root->right = NULL;
            root->left = build_random_binary_tree(max_nodes, max_value);
        }
    }
    else // строим оба поддерева
    {
        root->left = build_random_binary_tree(max_nodes, max_value);
        root->right = build_random_binary_tree(max_nodes, max_value);
    }

    return root;
}

// достраивает дерево в случайную "нулевую" вершину
// на вход принимает более менее отстроенное дерево, ограничение на оставшееся количество вершин и максимальное значение ключа
void complete_random_null_branch(BinTreeIntNode* root, int* max_nodes, const int max_value)
{
    BinTreeIntNode* current = root; // изначально дерево не пустое, так как эта функция вызывается именно для достраивания 
    while (True)         // ищем нулевую вершину
    {
        if ((current->right == NULL) && (current->left == NULL))
        { // оба поддерева пустые, выбираем одно из них для достраивания случайным образом
            if (rand() % 2)
                current->left = build_random_binary_tree(max_nodes, max_value);
            else
                current->right = build_random_binary_tree(max_nodes, max_value);
            return;
        }
        else if (current->left == NULL)  // только левое - нулевое
        {
            current->left = build_random_binary_tree(max_nodes, max_value);
            return;
        }
        else if (current->right == NULL) // только правое - нулевое
        {
            current->right = build_random_binary_tree(max_nodes, max_value);
            return;
        }
        else  // оба поддерева - не пустые выбираем одно из них случайным образом и спускаемся ниже
        {
            if (rand() % 2)
                current = current->right;
            else
                current = current->left;
        }
    }
    /* // Пыталась упростить эту функцию и переписать её следующим образом:
    while (current != NULL)                    // ищем нулевую вершину
    {
        if ((current->left == NULL) && (current->right != NULL))      // только левое - нулевое
            current = current->left;
        else if ((current->right == NULL) && (current->left != NULL)) // только правое - нулевое
            current = current->right;
        else // оба поддерева - не пустые или оба пустые, выбираем одно из них случайным образом
        {
            if (rand() % 2)
                current = current->left;
            else
                current = current->right;
        }
    }
    // current == NULL
    current = build_random_binary_tree(max_nodes, max_value);
    // но так ничего не выходит. Отстроенное по нулевому указателю дерево сразу как будто "забывается" */
}

// простая АЛЬТЕРНАТИВА предыдущим двум функциям: создание случайного бинарного дерева поиска
BinTreeIntNode* get_random_search_tree(const int max_nodes, const int max_value)
{
    BinTreeIntNode* tree = NULL;
    tree = treeInsert(tree, rand() % max_value);
    for (int node = 1; node < max_nodes; ++node)
        treeInsert(tree, rand() % max_value);
    return tree;
}

// создание множества случайных бинарных деревьев, подсчёт процента сбалансированных
void task2()
{
    const int TREES = 100;
    const int MAX_VALUE = 1000;
    const int NODES = 10000;

    printf("2. Создаём %d случайных бинарных деревьев по %d вершин в каждом.\n", TREES, NODES);
    int balanced_trees = 0;
    for (int tree_idx = 0; tree_idx < TREES; ++tree_idx)
    {
        int nodes_number = NODES;    // для каждого дерева свой независимый набор вершин

        BinTreeIntNode* random_tree = build_random_binary_tree(&nodes_number, MAX_VALUE);
        while (nodes_number > 0)     // чтобы создать ровно столько вершин, сколько нужно
            complete_random_null_branch(random_tree, &nodes_number, MAX_VALUE);

        // ИЛИ как вариант создать случайные деревья поиска, тогда % сбалансированных будет больше:
        // BinTreeIntNode* random_tree = get_random_search_tree(nodes_number, MAX_VALUE);

        if (check_balance(random_tree))
            ++balanced_trees;
    }

    printf("Получено %.2lf%% сбалансированных деревьев (%d из %d).\n\n", 100 * ((double)(balanced_trees) / TREES), balanced_trees, TREES);
}

/////////////////////////// ЗАДАНИЕ 3

// бинарный поиск в двоичном дереве поиска, реализованный рекурсивно. Возвращает False, если значение не найдено
boolean binSearchRec(BinTreeIntNode* tree, const int value)
{
    if (tree == NULL)
        return False;
    if (tree->key == value)
        return True;

    BinTreeIntNode* current = tree;

    if (value < tree->key)
        return binSearchRec(tree->left, value);
    else
        return binSearchRec(tree->right, value);
}

// проверяет рекурсивную функцию бинарного поиска на случайном дереве поиска
void task3()
{
    printf("3. Создаём случайное дерево поиска.\n");

    BinTreeIntNode* search_tree = get_random_search_tree(30, 100);
    printBinTree(search_tree);
    printf(" \n");

    int search_value1 = 70;
    printf("%d %s в этом дереве \n", search_value1, binSearchRec(search_tree, search_value1) ? "есть" : "нет");
    int search_value2 = 50;
    printf("%d %s в этом дереве \n\n", search_value2, binSearchRec(search_tree, search_value2) ? "есть" : "нет");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task2();
    task3();
    return 0;
}