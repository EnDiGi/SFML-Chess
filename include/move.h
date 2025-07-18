
#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "cell.h"

class Cell;
class Piece;
class Chessboard;

class Move{
    
    public:

        // Chessboard
        Chessboard* board;

        bool legal;

        // The move number
        int moveNumber;

        // The piece that moved (it's also the king when castling)
        Piece* piece;

        // The target cell
        Cell* targetCell;
        Piece* capturedPiece;

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