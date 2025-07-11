
#include "../../include/pieces/queen.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/move.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Queen::Queen(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void Queen::updateMoves(){

    this->canMove = {};
    this->canTake = {};
    this->couldTake = {};

    // * Check cells where to move and take (I copied the code form the bishop and the rook :)
    // Check down-right diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x + i, this->position.y + i};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }
    // Check down-left diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x + i, this->position.y - i};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }
    // Check up-right diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x - i, this->position.y + i};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }
    // Check up-left diagonal
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x - i, this->position.y - i};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }    
    
    // Check right... i don't know
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x, this->position.y + i};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }
    // Check left
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x, this->position.y - i};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }
    // Check up
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x - i, this->position.y};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }
    // Check down
    for(int i = 1; i < 8; i++){
        sf::Vector2i cellToCheck = {this->position.x + i, this->position.y};

        if(this->board->isInsideBoard(cellToCheck))
        {
            this->couldTake.push_back(cellToCheck);

            if(!this->board->squareIsOccupied(cellToCheck))
            {
                this->canMove.push_back(cellToCheck);
            } 
            else 
            {   
                // Checks if the piece in the cell we're currently checking is of the enemy color
                if(this->board->objectGrid[cellToCheck.x][cellToCheck.y]->piece->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces
            }
        } else {
            break; // Do not check farther outside the board
        }
    }    
}


void Queen::updateBoardCastleRights(){
    
}