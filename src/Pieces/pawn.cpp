
#include "../../include/pieces/pawn.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Pawn::Pawn(char symbol, Chessboard &board, sf::Vector2i pos): Piece(symbol, board, pos){
    this->updateMoves();
}

void Pawn::updateMoves(){
    this->canMove.clear();

    if(this->position.x == 0 || (this->position.x == this->board->side-1 && this->direction==-1)) return; // White on last row or black on first


    // * Check cells where to move
    // The cell in front of the pawn
    sf::Vector2i forwardCell = {this->position.x- 1*this->direction, this->position.y};
    if(!this->board->squareIsOccupied(forwardCell)){
        this->canMove.push_back(forwardCell);
    }


    // * Check cells where to take
    // Checks if the pawn is on the left side of the board
    if(0 < this->position.y){
        sf::Vector2i forwardLeftCell = {this->position.x - 1*this->direction, this->position.y-1};
        if(!this->board->squareIsOccupied(forwardLeftCell)){
            this->canTake.push_back(forwardLeftCell);
        }
    }
    // Checks if the pawn is on the right side of the board
    if(this->position.y < this->board->side-1){
        sf::Vector2i forwardRightCell = {this->position.x - 1*this->direction, this->position.y+1};
        if(!this->board->squareIsOccupied(forwardRightCell)){
            this->canTake.push_back(forwardRightCell);
        }
    }
}

void Pawn::makeMove(Cell* target){
    this->board->movePiece(this->getCell(), target);
}