
#include "../../include/pieces/rook.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Rook::Rook(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void Rook::updateMoves(){

    this->canMove = {};
    this->canTake = {};

    // * Check cells where to move and take
    // Check right... i don't know
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x, this->position.y + i};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
                this->couldTake.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                    this->couldTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }
    // Check left
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x, this->position.y - i};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
                this->couldTake.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                    this->couldTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }
    // Check up
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x - i, this->position.y};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
                this->couldTake.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                    this->couldTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }
    // Check down
    for(int i = 1; i < 8; i++){
        sf::Vector2i celltoCheck = {this->position.x + i, this->position.y};

        if(this->board->isInsideBoard(celltoCheck))
        {
            if(!this->board->squareIsOccupied(celltoCheck))
            {
                this->canMove.push_back(celltoCheck);
                this->couldTake.push_back(celltoCheck);
            } 
            else 
            {
                if(this->board->objectGrid[celltoCheck.x][celltoCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(celltoCheck);
                    this->couldTake.push_back(celltoCheck);
                }
                break;
            }
        } else {
            break;
        }
    }    
}