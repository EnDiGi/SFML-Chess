
#ifndef MOVE_H
#define MOVE_H

class Cell;
class Piece;

class Move{
    
    public:

        // The object grid before the move was made
        Cell* gridBeforeMove[8][8];

        // The color that made the move
        char color;

        // The move number
        int moveNumber;

        // The piece that moved
        Piece* piece;

        // The target cell
        Cell* targetCell;

        // True if there was a capture
        bool capture;

        Move(char color, int moveNumber, Piece* piece, Cell* target, bool capture);
};



#endif