#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // для кириллицы

// ниже реализация односвязного списка (взята с урока):
#define T char
#define True 1 == 1
#define False 1 != 1
typedef int boolean;

typedef struct OneLinkNode
{
    T dat;
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

///////////////////////////////// ЗАДАНИЕ 1

boolean pushOneLinkStack(OneLinkList* stack, char value)
{
    OneLinkNode* tmp = (OneLinkNode*)malloc(sizeof(OneLinkNode));
    if (tmp == NULL) {
        printf("Stack overflow \n");
        return False;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return True;
}

T popOneLinkStack(OneLinkList* stack)
{
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    OneLinkNode* tmp = stack->head;
    char data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

// определяет, является ли принятый текст правильной скобочной последовательностью
boolean checkBrackets(char* text, const int max_size)
{
    // в стэке будем держать открывающие скобки, чтобы сравнивать закрывающую с последней
    OneLinkList* brackets = (OneLinkList*)malloc(sizeof(OneLinkList));
    initOneLinkList(brackets);

    for (int i = 0; i < max_size; i++)
    {
        char symbol = text[i];
        // если открывающая скобка - добавляем её в стэк
        if (symbol == '(' || symbol == '{' || symbol == '[')
            pushOneLinkStack(brackets, symbol);
        // если закрывающая скобка - сравниваем её с последней открывающей
        else if (symbol == ')' || symbol == '}' || symbol == ']')
        {
            if (brackets->size == 0) // нет ни одной открывающей
                return False;
            char prev_bracket = popOneLinkStack(brackets);
            if ((prev_bracket == '(') && (symbol == ')') || (prev_bracket == '{') && (symbol == '}') || (prev_bracket == '[') && (symbol == ']'))
                continue;
            else
                return False;
        }
    }
    // остались незакрытые скобки?
    if (brackets->size != 0)
        return False;
    return True;
}

// определяет, является ли введенная скобочная последовательность правильной
void task1()
{
    printf("1. Определение правильно расставленных скобок.\nВведите текст, содержащий скобки (, ), {, }, [, ]:\n");

    const int max_size = 256;
    char text_with_brackets[max_size] = {};
    fgets(text_with_brackets, max_size, stdin); // просто gets у меня не работает

    if (checkBrackets(text_with_brackets, max_size))
        printf("Введённая скобочная последовательность правильная.");
    else
        printf("Введённая скобочная последовательность неправильная.");

    printf("\n\n");
}

///////////////////////////////// ЗАДАНИЕ 2

void insert(OneLinkList *lst, int data) 
{
    OneLinkNode *new_node = (OneLinkNode*) malloc(sizeof(OneLinkNode));
    new_node->dat = data;
    new_node->next = NULL;

    OneLinkNode *current = lst->head;
    if (current == NULL) {
        lst->head = new_node;
        lst->size++;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        lst->size++;
    }
}

OneLinkNode* rm(OneLinkList *lst, int data) {
    OneLinkNode *current = lst->head;
    OneLinkNode *parent = NULL;
    if (current == NULL)
        return NULL;

    while (current->next != NULL && current->dat != data) {
        parent = current;
        current = current->next;
    }
    if (current->dat != data) {
        return NULL;
    }
    if (current == lst->head) {
        lst->head = current->next;
        lst->size--;
        return current;
    }
    parent->next = current->next;
    lst->size--;
    return current;
}

void printOneLinkCharNode(OneLinkNode* n)
{
    if (n == NULL) {
        printf("[ ]");
        return;
    }
    printf("[%c]", n->dat);
}

void printOneLinkCharList(OneLinkList* lst)
{
    OneLinkNode* current = lst->head;
    if (current == NULL) {
        printOneLinkCharNode(current);
    }
    else {
        do {
            printOneLinkCharNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", lst->size);
}

// создаёт функцию, копирующую односвязный список (без удаления первого списка)
void task2()
{
    printf("2. Копирование односвязного списка\n");
    printf("Исходный список:\n");
    OneLinkList* lst = (OneLinkList*)malloc(sizeof(OneLinkList));
    initOneLinkList(lst);
    insert(lst, 97);
    insert(lst, 98);
    insert(lst, 99);
    insert(lst, 100);
    insert(lst, 101);
    insert(lst, 102);
    printOneLinkCharList(lst);

    printf("Скопированный список:\n");
    OneLinkList* copy_lst = (OneLinkList*)malloc(sizeof(OneLinkList));
    initOneLinkList(copy_lst);
    OneLinkNode* current = lst->head;
    while (current != NULL)
    {
        insert(copy_lst, current->dat);
        current = current->next;
    }
    printOneLinkCharList(copy_lst);
    free(current); // а память для списков по традиции оставляем неосвобождённой

    printf("\n\n");
}

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    task2();
    //task3();
    return 0;
}