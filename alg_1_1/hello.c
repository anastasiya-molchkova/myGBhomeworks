#include <stdio.h>
#include <locale.h>  // для кириллицы

int main()
{
        setlocale(LC_CTYPE, "Russian");  // для кириллицы
	printf("Привет, мир!\n\n");
	return 0;
}