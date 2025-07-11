
#include "../../include/pieces/knight.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/move.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Knight::Knight(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void Knight::updateMoves(){

    this->canMove = {};
    this->canTake = {};
    this->couldTake = {};

    sf::Vector2i cellsToCheck[8] = {
        {this->position.x - 2, this->position.y - 1},
        {this->position.x - 2, this->position.y + 1},
        {this->position.x - 1, this->position.y + 2},
        {this->position.x - 1, this->position.y - 2},
        {this->position.x + 1, this->position.y + 2},
        {this->position.x + 1, this->position.y - 2},
        {this->position.x + 2, this->position.y - 1},
        {this->position.x + 2, this->position.y + 1}
    };

    for(sf::Vector2i pos : cellsToCheck)
    {

        if(this->board->isInsideBoard(pos))
        {
            this->couldTake.push_back(pos);

            if(!this->board->squareIsOccupied(pos))
            {
                this->canMove.push_back(pos);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[pos.x][pos.y]->piece->color != this->color)
                {
                    this->canTake.push_back(pos);
                }
            }
        }
    }
}

void Knight::updateBoardCastleRights(){
    
}