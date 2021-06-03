#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // для кириллицы

///////////////////////////////// ЗАДАНИЕ 1

// ниже реализация стэка на основе односвязного списка (взята с урока):
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

void printOneLinkCharNode(OneLinkNode* n)
{
    if (n == NULL) {
        printf(" ");
        return;
    }
    printf("%c", n->dat);
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

int main()
{
    setlocale(LC_CTYPE, "rus");  // для кириллицы
    task1();
    //task2();
    //task3();
    return 0;
}