
#ifndef PAWN_H
#define PANW_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "piece.h"

class Chessboard;
class Cell;

// An object that represents a pawn inheriting properties from piece
class Pawn: public Piece{

    public:

        /**
         * Constructor for Pawn class
         * @param symbol the symbol of the piece in FEN notation
         * @param board a pointer to the current board
         * @param pos the position (row and column)
         */
        Pawn(char symbol, Chessboard &board, sf::Vector2i pos);

        // Updates available moves and takes
        void updateMoves() override;

        void makeMove(Cell* target) override;
};

#endif