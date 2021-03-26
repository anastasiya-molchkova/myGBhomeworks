#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <iostream>
#include <string>          // для рисования рамки поля

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
    size_t size = 3;
    CellParameters cell_data;
    CellStatus * cells;
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

GameData game_initialization();
void clear_field(Field& field);
void game_exit(GameData& game);
size_t getSize();
Sign getPlayerSign();
bool isCellAvailable(const Field& field, const int row, const int column);
void putSign(Field& field, const Sign player_sign, const size_t row, const size_t column);
void printField(const Field& field);
bool isDraw(const Field& field);
void printGameOutcome(const TurnOutcome& outcome, Sign player_sign);
TurnOutcome runGameLoop(GameData& game);
bool askQuestion(char positive, char negative);
bool queryPlayAgain();

#endif
