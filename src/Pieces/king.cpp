
#include "../../include/pieces/king.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>

King::King(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): Piece(symbol, board, pos, moved){
    ;
}

void King::updateMoves(){

    this->canMove = {};
    this->canTake = {};

    sf::Vector2i up = {this->position.x - 1, this->position.y};
    sf::Vector2i right = {this->position.x, this->position.y + 1};
    sf::Vector2i left = {this->position.x, this->position.y - 1};
    sf::Vector2i down = {this->position.x + 1, this->position.y};

    sf::Vector2i upRight = {up.x, right.y};
    sf::Vector2i upLeft = {up.x, left.y};
    sf::Vector2i downRight = {down.x, right.y};
    sf::Vector2i downLeft = {down.x, left.y};

    sf::Vector2i cellsToCheck[8] = {up, right, left, down, upRight, upLeft, downRight, downLeft};

    for(sf::Vector2i pos : cellsToCheck)
    {
        if(this->board->isInsideBoard(pos))
        {

            bool isCellsafe = this->isSafe(pos);

            if(!isCellsafe) continue;
            if(!this->board->squareIsOccupied(pos))
            {
                this->canMove.push_back(pos);
            } 
            else 
            {
                if(this->board->objectGrid[pos.x][pos.y]->piece->color != this->color)
                {
                    this->canTake.push_back(pos);
                }
                continue;
            }
        } else {
            continue;
        }
    }



    // * Check for castling kingside
}

bool King::isSafe(){
    return this->isSafe(this->position);
}

bool King::isSafe(sf::Vector2i cellPos){
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Piece* piece = this->board->objectGrid[i][j]->piece;
            if(piece == nullptr) continue;
            if(piece->color == this->color) continue;

            if(std::find(piece->canMove.begin(), piece->canMove.end(), cellPos) != piece->canMove.end())
            {
                return false;
            }
        }
    }

    return true;
}
