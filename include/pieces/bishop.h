
#ifndef BISHOP_H
#define BISHOP_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "piece.h"

class Chessboard;
class Cell;

// An object that represents a pawn inheriting properties from piece
class Bishop: public Piece{

    public:

        /**
         * Constructor for Bishop class
         * @param symbol the symbol of the piece in FEN notation
         * @param board a pointer to the current board
         * @param pos the position (row and column)
         */
        Bishop(char symbol, Chessboard &board, sf::Vector2i pos, bool moved);

        // Updates available moves and takes
        void updatePseudoMoves() override;
        
        void updateBoardCastleRights() override;
};

#endif