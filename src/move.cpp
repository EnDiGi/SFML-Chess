
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

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            this->boardBefore[i][j] = *board->objectGrid[i][j];
            this->boardAfter[i][j] = *board->objectGrid[i][j];
        }
    }

    this->boardAfter[piece->position.x][piece->position.y].piece = nullptr;
    this->boardAfter[target->row][target->col].piece = piece;

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

    std::vector<Piece*> kings = this->board->getPieceOnBoard(opponent(this->piece->color), "king", boardAfter);
    if(kings.empty()){
        return;
    }

    if(!(kings[0]->isSafe(this->boardAfter))){
        this->id += "+";
    }
}

bool Move::isLegal(){

    // std::cout << "checking moving a " << piece->name << " in " 
    //           << this->piece->position.x << " " << this->piece->position.y << " to " 
    //           << this->targetCell->row  << " " << this->targetCell->col << std::endl;

    std::vector<Piece*> kings = board->getPieceOnBoard(this->piece->color, "king", this->boardAfter);
    // If there isn't the king because a piece "ate" it
    if(kings.empty()){
        return false;
    }
    // Check for check
    if(!(kings[0]->isSafe(boardAfter))){
        // If after this move the king would be in check
        return false;
    }
    return true;
}