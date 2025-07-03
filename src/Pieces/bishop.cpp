
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/pieces/piece.h"
#include "../../include/pieces/bishop.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Bishop::Bishop(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void Bishop::updateMoves(){

    this->canMove = {};
    this->canTake = {};


    // * Check cells where to move and take
    // Check down-right diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x + i, this->position.y + i};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }
    // Check down-left diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x + i, this->position.y - i};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }
    // Check up-right diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x - i, this->position.y + i};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }
    // Check up-left diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x - i, this->position.y - i};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }    
}