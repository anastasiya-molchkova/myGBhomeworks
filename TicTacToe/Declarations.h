#ifndef DECLARATIONS_H
#define DECLARATIONS_H

// возможные состояния клетки игры в крестики-нолики:
enum class CellStatus { Empty = 0, X, O };

using cellSize = size_t;
enum class Colors { Green, Red, Yellow, Blue, Black, White };

struct CellParameters
{
    Colors color;
    cellSize length;
    cellSize width;
};

// поле для игры в крестики-нолики:
struct Field
{
    static const short size = 3;               // требует именно static!
    CellParameters cell_data;
    CellStatus cells[size][size];
};

enum class Sign { O, X };

struct GameData
{
    Field field;
    Sign player_sign;
};
struct TurnOutcome
{
    bool isOver;
    Sign victor;
    bool isDraw;
};

Sign getPlayerSign();
bool isCellAvailable(const Field& field, const int row, const int column);
void putSign(Field& field, const Sign player_sign, const size_t row, const size_t column);
void printField(const Field& field);
bool isDraw(const Field& field);
void printGameOutcome(const TurnOutcome& outcome, Sign player_sign);
TurnOutcome runGameLoop(Sign player_sign);
bool askQuestion(char positive, char negative);
bool queryPlayAgain();

#endif
