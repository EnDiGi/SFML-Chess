
#ifndef KING_H
#define KING_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "piece.h"

class Chessboard;
class Cell;

// An object that represents a pawn inheriting properties from piece
class King: public Piece{

    public:
        // - if didn't castle, k if it castled kingside, q if it castled queenside
        char castled = '-';

        /**
         * Constructor for King class
         * @param symbol the symbol of the piece in FEN notation
         * @param board a pointer to the current board
         * @param pos the position (row and column)
         */
        King(char symbol, Chessboard &board, sf::Vector2i pos, bool moved);

        // Updates available moves and takes
        void updateMoves() override;
        
        bool isSafe();

        bool isSafe(sf::Vector2i cellPos);
};

#endif