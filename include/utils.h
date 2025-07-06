
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Piece;

class Pawn;

class Rook;

class Knight;

class Bishop;

class King;

class Queen;

class Chessboard;

std::vector<std::string> split(std::string &string, std::string &sep);

char getColor(char symbol);

std::string getName(char symbol);

char getSymbol(char color, std::string name);

Piece* getPiece(char symbol, Chessboard &board, sf::Vector2i position, bool moved);

char getColumnLetter(int col);

int getRowNumber(int row);

#endif