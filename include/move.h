
#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "cell.h"

class Cell;
class Piece;
class Chessboard;

class Move{
    
    public:

        // The object grid before the move was made
        Cell boardBefore[8][8];
        // The object grid after the move was made
        Cell boardAfter[8][8];

        // Chessboard
        Chessboard* board;

        // The move number
        int moveNumber;

        // The piece that moved (it's also the king when castling)
        Piece* piece;

        // The target cell
        Cell* targetCell;

        // True if there was a capture
        bool capture;

        // * Castle related variables
        Piece* rook;

        std::string id;

        Move(int moveNumber, Piece* piece, Cell* target, bool capture, Chessboard* board);

        Move(int moveNumber, Piece* king, Piece* rook, bool kingSide, Chessboard* board);

        void createId();

        bool isLegal();
};



#endif