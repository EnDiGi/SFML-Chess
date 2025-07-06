
#ifndef MOVECIRCLE_H
#define MOVECIRCLE_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Chessboard;
class Cell;
class Piece;

class MoveCircle: public sf::CircleShape{

    private:
        // Indicates the circle's mode (move, take or castle)
        char mode;

        // Used for castling
        Cell* rookCell;

    public:
        Cell* cell;
        Piece* pieceToMove;
        MoveCircle(char mode, Cell &cell, Piece &pieceToMove, int radius = 15);

        void move(Chessboard* board);
};

#endif