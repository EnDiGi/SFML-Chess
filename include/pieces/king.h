
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

        /**
         * Constructor for King class
         * @param symbol the symbol of the piece in FEN notation
         * @param board a pointer to the current board
         * @param pos the position (row and column)
         */
        King(char symbol, Chessboard &board, sf::Vector2i pos, bool moved);

        // Updates available moves and takes
        void updateMoves() override;

        void updateBoardCastleRights() override;
};

#endif