#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

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

// печатает массив
void printIntArray(int* array, int size) 
{
    char format[7];
    const int offset = 3;
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) 
    {
        printf(format, array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}

// заполняет массив случайными значениями
void fillIntRandom(int* array, int size, int border) 
{
    for (int i = 0; i < size; ++i)
        *(array + i) = rand() % border;
}

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

// находит наследника для удаляемой вершины по принципу "меньший из больших"
BinTreeIntNode* getSuccessor(BinTreeIntNode* node) 
{
    BinTreeIntNode* current = node->right;
    BinTreeIntNode* parent = node;
    BinTreeIntNode* s = node;

    while (current != NULL) 
    {
        parent = s;
        s = current;
        current = current->left;
    }
    if (s != node->right) 
    {
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}

// удаляет из дерева вершину с заданным значением (если такой нет - возвращает False)
boolean treeNodeDelete(BinTreeIntNode* root, int key) 
{
    BinTreeIntNode* current = root;
    BinTreeIntNode* parent = root;
    boolean isLeftChild = True;

    while (current->key != key) 
    {
        parent = current;
        if (key < current->key) 
        {
            current = current->left;
            isLeftChild = True;
        }
        else 
        {
            current = current->right;
            isLeftChild = False;
        }
        if (current == NULL)
            return False;
    }

    if (current->left == NULL && current->right == NULL) 
    {
        if (current == root)
            root = NULL;
        else if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (current->right == NULL) 
    {
        if (isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if (current->left == NULL) 
    {
        if (isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else 
    {
        BinTreeIntNode* successor = getSuccessor(current);
        if (current == root)
            root = successor;
        else if (isLeftChild)
            parent->left = successor;
        else
            parent->right = successor;
        successor->left = current->left;
    }
    return True;
}

// обход дерева в прямом порядке (корень - левый - правый)
void preOrderTravers(BinTreeIntNode* root) 
{
    if (root) 
    {
        printf("%2d ", root->key);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

// центрированный обход дерева (левый - корень - правый)
void inOrderTravers(BinTreeIntNode* root) 
{
    if (root) 
    {
        inOrderTravers(root->left);
        printf("%2d ", root->key);
        inOrderTravers(root->right);
    }
}

// обход дерева в обратном порядке (левый - правый - корень)
void postOrderTravers(BinTreeIntNode* root) 
{
    if (root) 
    {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        printf("%2d ", root->key);
    }
}

// построение сбалансированного дерева со случайными числами в вершинах
BinTreeIntNode* balancedTree(int n)
{
    BinTreeIntNode* newNode;
    int x;
    int nL;
    int nR;

    if (n == 0)
        return NULL;
    else
    {
        x = rand() % 100;
        nL = n / 2;
        nR = n - nL - 1;
        newNode = (BinTreeIntNode*)malloc(sizeof(BinTreeIntNode));
        newNode->key = x;
        newNode->left = balancedTree(nL);
        newNode->right = balancedTree(nR);
    }
    return newNode;
}

// бинарный поиск в двоичном дереве поиска, реализованный итеративно. Возвращает False, если значение не найдено
boolean binSearch(BinTreeIntNode* root, int value) 
{
    if (root == NULL)
        return False;
    if (root->key == value)
        return True;

    BinTreeIntNode* current = root;
    while (current->key != value) 
    {
        if (value < current->key)
            current = current->left;
        else
            current = current->right;

        if (current == NULL)
            return False;
    }
}

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
    if (tree->left == NULL && tree->right == NULL)
        return True;
    if (abs(get_height(tree->right) - get_height(tree->right)) <= 1)
        return True;
    return False;
}

void task1()
{
    printf("1. Создаём дерево.\n");
    BinTreeIntNode* tree = NULL;
    tree = treeInsert(tree, 10);
    treeInsert(tree, 8);
    treeInsert(tree, 19);
    treeInsert(tree, 5);
    treeInsert(tree, 9);
    treeInsert(tree, 16);
    treeInsert(tree, 21);
    printBinTree(tree);
    printf(" \n");
    printf("Высота дерева %d\n", get_height(tree));
    printf("Дерево сбалансировано - это %s\n\n", check_balance(tree) ? "истина" : "ложь");

    printf("Удалим несколько вершин:\n");
    treeNodeDelete(tree, 5);
    printBinTree(tree);
    printf(" \n");
    treeNodeDelete(tree, 19);
    printBinTree(tree);
    printf(" \n");
    treeNodeDelete(tree, 8);
    printBinTree(tree);
    printf("\nВысота дерева %d\n", get_height(tree));
    printf("Дерево сбалансировано - это %s\n\n", check_balance(tree) ? "истина" : "ложь");

    const int nodes = 15;
    printf("Создадим сбалансированное дерево из %d вершин:\n", nodes);
    BinTreeIntNode* balanced_tree = NULL;
    balanced_tree = balancedTree(nodes);
    printBinTree(balanced_tree);
    printf("\nВысота дерева %d\n", get_height(balanced_tree));
    printf("Дерево сбалансировано - это %s\n", check_balance(balanced_tree) ? "истина" : "ложь");
    printf(" \n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    return 0;
}