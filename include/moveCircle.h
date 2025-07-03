
#ifndef MOVECRICLE_H
#define MOVECIRCLE_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Chessboard;
class Cell;
class Piece;

class MoveCircle: public sf::CircleShape{

    public:
        Cell* cell;
        Piece* pieceToMove;
        MoveCircle(char mode, Cell &cell, Piece &pieceToMove, int radius = 15);

        void move(Chessboard &board);
};

#endif