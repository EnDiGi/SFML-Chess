
#include "../../include/pieces/pawn.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Pawn::Pawn(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void Pawn::updateMoves(){

    this->canMove = {};
    this->canTake = {};

    if((this->position.x == 0 && this->color == 'w') || (this->position.x == 7 && this->color == 'b'))  // If the pawn is on the last row
    {
        // TODO: Implement promotion
        std::cout << "promotion" << std::endl;
        return;
    }

    // * Check cells where to move
    // The cell in front of the pawn
    sf::Vector2i forwardCell = {this->position.x- 1*this->direction, this->position.y};
    if(this->board->isInsideBoard(forwardCell))
    {

        if(!(this->board->squareIsOccupied(forwardCell))){
            this->canMove.push_back(forwardCell);
    
            sf::Vector2i forward2Cell = {this->position.x- 2*this->direction, this->position.y};
    
            // Handle first move double shift
            if(( (this->position.x == 1 && this->color == 'b') || (this->position.x == 6 && this->color == 'w') ) && this->board->isInsideBoard(forward2Cell))
            {
                if(!(this->board->squareIsOccupied(forward2Cell)))
                {
                    this->canMove.push_back(forward2Cell);
                }
            }
        }
    }

    // * Check cells where to take
    // Checks if the pawn is on the left side of the board
    if(this->position.y != 0)
    {
        sf::Vector2i forwardLeftCell = {this->position.x - 1*this->direction, this->position.y-1};

        if(this->board->squareIsOccupied(forwardLeftCell))
        {
            Piece* forwLeftPiece = board->objectGrid[forwardLeftCell.x][forwardLeftCell.y]->piece;
            if(forwLeftPiece != nullptr)
            {
                if(board->objectGrid[forwardLeftCell.x][forwardLeftCell.y]->piece->color != this->color)
                {
                    this->canTake.push_back(forwardLeftCell);
                    this->couldTake.push_back(forwardLeftCell);
                }
            }
        }

        this->couldTake.push_back(forwardLeftCell);
    }
    // Checks if the pawn is on the right side of the board
    if(this->position.y != 7)
    {
        sf::Vector2i forwardRightCell = {this->position.x - 1*this->direction, this->position.y+1};

        if(this->board->squareIsOccupied(forwardRightCell))
        {
            Piece* forwRightPiece = board->objectGrid[forwardRightCell.x][forwardRightCell.y]->piece;
            if(forwRightPiece != nullptr)
            {
                if(board->objectGrid[forwardRightCell.x][forwardRightCell.y]->piece->color != this->color)
                {
                    this->canTake.push_back(forwardRightCell);
                    this->couldTake.push_back(forwardRightCell);
                }
            }
        }

        this->couldTake.push_back(forwardRightCell);
    }
}