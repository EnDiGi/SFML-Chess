
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/pieces/piece.h"
#include "../../include/pieces/bishop.h"
#include "../../include/move.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Bishop::Bishop(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void Bishop::updatePseudoMoves(){

    this->canMove = {};
    this->canTake = {};
    this->couldTake = {};


    // * Check cells where to move and take
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
                if(this->board->pieceAt(cellToCheck)->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces that are not the king
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
                if(this->board->pieceAt(cellToCheck)->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces that are not the king
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
                if(this->board->pieceAt(cellToCheck)->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces that are not the king
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
                if(this->board->pieceAt(cellToCheck)->color != this->color)
                {
                    this->canTake.push_back(cellToCheck);
                }
                break; // Do not check behind enemy pieces that are not the king
            }
        } else {
            break; // Do not check farther outside the board
        }
    }    
}

void Bishop::updateBoardCastleRights(){

}