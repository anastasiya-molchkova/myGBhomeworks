//                      ОБЩИЙ ФАЙЛ С ОБЪЯВЛЕНИЯМИ НЕОБХОДИМЫХ СТРУКТУР И ОСНОВНЫХ ФУНКЦИЙ:
#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <iostream>        // для ввода-вывода данных
#include <string>          // для рисования рамки поля
#include <iomanip>         // для форматированного вывода в консоль

// возможные состояния клетки игры в крестики-нолики
enum class CellStatus { Empty = 0, X, O };

// поле для игры в крестики-нолики
struct Field
{
    size_t size = 3;
    CellStatus * cells;             // массив клеток поля. В начале игры после получения размера поля создаётся динамически
};

// знак, которым можно играть - крестик или нолик
enum class Sign { O, X };

// поле и знак, которым играет пользователь
struct GameData
{
    Field field;
    Sign player_sign;
};

// исход игры - закончена ли игра, знак победителя и ничья ли
struct TurnOutcome
{
    bool isOver;
    Sign victor;
    bool isDraw;
};

// функции, используемые в разных файлах (не все):
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
bool queryPlayAgain();

#endif
