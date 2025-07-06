
#include "../include/move.h"
#include "../include/cell.h"
#include "../include/pieces/piece.h"

Move::Move(char color, int moveNumber, Piece* piece, Cell* target, bool capture){
    this->color = color;
    this->moveNumber = moveNumber;
    this->piece = piece;
    this->targetCell = target;
    this->capture = capture;
}