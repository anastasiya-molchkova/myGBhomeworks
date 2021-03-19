/* Консольная игра "Крестики-Нолики", но на красивом поле и с искусственным интеллектом ;)  */

#include <iostream>

// возможные состояния клетки игры в крестики-нолики:
enum class CellStatus{Empty = 0, X, O};

using cellSize = size_t;
enum class Colors{Green, Red, Yellow, Blue, Black, White};

struct CellParameters
{
	Colors color; 
	cellSize length;
	cellSize width;
}

// поле для игры в крестики-нолики:
struct Field
{
	static const short field_size = 3;               // требует именно static!
	CellParameters cell;
	CellStatus field[field_size][field_size];
};

int main()
{
    return 0;
}