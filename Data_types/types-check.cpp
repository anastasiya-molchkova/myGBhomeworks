#include <iostream>

int main()
{
	using std::cout;

	bool boolValue = false;
	cout << "Bool value False is: " << boolValue << "\n";

	int intNumber = 2147483647;
	cout << "Integer number: " << intNumber << "\n";

	short shortNumber = -32768;
	cout << "Short number: " << shortNumber << "\n";

	long Number = -2147483648;
	cout << "Long number: " << longNumber << "\n";

	unsigned long long uLongLongNumber = 18446744073709551615;
	cout << "Unsigned long long number: " << uLongLongNumber << "\n";

	int8_t fixInt1byteNumber = -128;
	cout << "int8_t number: " << fixInt1byteNumber << "\n";

	uint16_t fixIntUn2byteNumber = 65535;
	cout << "uint16_t number: " << fixIntUn2byteNumber << "\n";

	char charValue1 = 'n';
	char charValue2 = -100;
	cout << "Char value examples: " << charValue1 << " and " << charValue2 << "\n";

	float floatNumber = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	cout << "Float number: " << floatNumber << "\n";

	double doubleNumber = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	cout << "Double number: " << doubleNumber << "\n";

	long double longDoubleNumber = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
	cout << "Long double number: " << longDoubleNumber << "\n";

}