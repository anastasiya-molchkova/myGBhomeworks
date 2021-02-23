#include <iostream>

// ЗАДАНИЕ 2, возможные состояния клетки игры в крестики-нолики:
enum class CellStatus{Empty = 0, X, O};

// ЗАДАНИЕ 4, поле для игры в крестики-нолики:
using cellSize = unsigned int;
enum class Colors{Green, Red, Yellow, Blue, Black, White};

struct TicTacToeField
{
	static const short field_size = 3;               // требует именно static!
	struct CellParameters
	{
		Colors color; 
		cellSize length;
		cellSize width;
	} cell;
	CellStatus field[field_size][field_size];
};

// ЗАДАНИЕ 5, структура с битовыми флагами для определения состояний объединения:
struct UnionCondition
{
	union SmallValue
	{
		char ch1;
		unsigned char ch2;
		int8_t int1;
		int16_t int2; 
		short shortInt;  
	} small_value;
	bool isChar1 : 1;
	bool isChar2 : 1;
	bool isInt1 : 1;
	bool isInt2 : 1;
	bool isShort : 1;
};

// ТОЧКА ВХОДА
int main()
{
	using std::cout;

// ЗАДАНИЕ 1, создание и инициализация переменных основных типов:
	bool boolValue = false;
	cout << "Bool value False is: " << boolValue << ", the size: " << sizeof(bool) << "\n";

	int intNumber = 2147483647;
	cout << "Integer number: " << intNumber << ", the size: " << sizeof(int) << "\n";

	short shortNumber = -32768;
	cout << "Short number: " << shortNumber << ", the size: " << sizeof(short) << "\n";

	long longNumber = -2147483648;
	cout << "Long number: " << longNumber << ", the size: " << sizeof(long) << "\n";

	unsigned long long uLongLongNumber = 18446744073709551615;
	cout << "Unsigned long long number: " << uLongLongNumber << ", the size: " << sizeof(uLongLongNumber) << "\n";

	int8_t fixInt1byteNumber = 65;
	// почему-то не работает с отрицательными числами и вообще работает, как char (выводит А)
	cout << "int8_t number: " << fixInt1byteNumber << ", the size: " << sizeof(int8_t) << "\n";

	uint16_t fixIntUn2byteNumber = 65535;
	cout << "uint16_t number: " << fixIntUn2byteNumber << ", the size: " << sizeof(uint16_t) << "\n";

	char charValue1 = 'n';
	char charValue2 = 50;
        // хотя char по умолчанию signed, он не работает с отрицательными числами
	cout << "Char value examples: " << charValue1 << " and " << charValue2 << ", the size: " << sizeof(char) << "\n";

	float floatNumber = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	cout << "Float number: " << floatNumber << ", the size: " << sizeof(float) << "\n";

	double doubleNumber = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	cout << "Double number: " << doubleNumber << ", the size: " << sizeof(double) << "\n";

	long double longDoubleNumber = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	cout << "Long double number: " << longDoubleNumber << ", the size: " << sizeof(long double) << "\n";

// ЗАДАНИЕ 3, массив, способный содержать возможные варианты для игры в крестики-нолики:
	CellStatus array_field[3][3]{{CellStatus::Empty, CellStatus::Empty, CellStatus::Empty}, 
                                     {CellStatus::Empty, CellStatus::Empty, CellStatus::Empty}, 
                                     {CellStatus::Empty, CellStatus::Empty, CellStatus::Empty}};

// к ЗАДАНИЮ 5, проверка размера структуры с битовыми флагами:
	UnionCondition sm = {.small_value.shortInt = 651, .isChar1 = false, .isChar2 = false, 
			     .isInt1 = false, .isInt2 = false, .isShort = true};
	cout << "Size of structure with union and its conditions: " << sizeof(sm) << "\n";

	return 0;
}