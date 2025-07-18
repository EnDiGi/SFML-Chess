
#include "../include/move.h"
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/chessboard.h"
#include "../include/utils.h"
#include <string>
#include <iostream>

Move::Move(int moveNumber, Piece* piece, Cell* target, bool capture, Chessboard* board){
    // std::cout << "creating move for a " << piece->name << std::endl;
    this->moveNumber = moveNumber;
    this->piece = piece;
    this->targetCell = target;
    this->capture = capture;
    this->board = board;

    this->capturedPiece = this->targetCell->piece != nullptr ? targetCell->piece : nullptr;

    this->createId();
}

Move::Move(int moveNumber, Piece* piece, Piece* rook, bool kingSide, Chessboard* board){
    this->piece = piece;
    this->rook = rook;
    this->moveNumber = moveNumber;
    this->board = board;

    this->id = kingSide ? "O-O" : "O-O-O";

}

void Move::createId(){

    this->id = "";

    if(piece->name != "pawn") // If it's not a pawn
    {
        this->id += piece->symbol; // Adds the piece's symbol
    }
    if(this->capture)
    {
        this->id += "x";
    }
    this->id += std::string(1, getColumnLetter(this->targetCell->col));
    this->id += std::to_string(getRowNumber(this->targetCell->row));

    std::vector<Piece*> kings = this->board->getPieceOnBoard(opponent(this->piece->color), "king");
    if(kings.empty()){
        return;
    }
}

bool Move::isLegal(){

    this->board->movePiece(this->piece, this->targetCell, true, false);

    // Updates only pseudo-moves (doesn't check if they put the king in check)
    this->board->updateMoves(true);

    // std::cout << "checking moving a " << piece->name << " in " 
    //           << this->piece->position.x << " " << this->piece->position.y << " to " 
    //           << this->targetCell->row  << " " << this->targetCell->col << std::endl;

    std::vector<Piece*> kings = board->getPieceOnBoard(this->piece->color, "king");
    // If there isn't the king because a piece "ate" it or because there isn't
    if(kings.empty()){
        this->board->undoMove();
        std::cout << "no king if this move" << std::endl;
        return false;
    }
    // Check for check
    if(!(kings[0]->isSafe())){
        // If after this move the king would be in check
        this->board->undoMove();
        std::cout << "king not safe after this move" << std::endl;
        return false;
    }

    this->board->undoMove();

    this->board->updateMoves(true);

    return true;
}