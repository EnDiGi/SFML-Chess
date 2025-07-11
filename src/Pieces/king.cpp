
#include "../../include/pieces/king.h"
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/utils.h"
#include "../../include/pieces/rook.h"
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
    this->couldTake = {};

    bool isSafe = this->isSafe();

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



    // * Check for castling
    std::vector<Piece*> rooks = this->board->getPieceOnBoard(this->color, "rook");

    if(rooks.empty()) return;

    for(Piece* rook: rooks)
    {
        if(!this->moved && !rook->moved && // none of the piece moved
            this->position == this->initialPos && contains({{0, 4}, {7, 4}}, this->position) && // The king is on one of the starting cells
            rook->position == rook->initialPos && contains({{0, 0}, {7, 0}, {7, 7}, {0, 7}}, rook->position) && // Same for the rook
            this->board->noPieceInBetweenHorizontally(this, rook)) 
        {
            int direction = rook->position.y < this->position.y ? -1 : 1;

            sf::Vector2i step = {this->position.x, this->position.y + direction};
            sf::Vector2i castleCircleCell = {this->position.x, this->position.y + 2 * direction};

            if(isSafe && this->isSafe(castleCircleCell) && this->isSafe(step))
            {
                this->canMove.push_back(step);
                this->canCastleWith.push_back(castleCircleCell);
            }
        }
    }
}

void King::updateBoardCastleRights(){
    std::vector<Piece*> rooks = this->board->getPieceOnBoard(this->color, "rook");

    if(rooks.empty()) return;

    for(Piece* rook: rooks)
    {
        if(!this->moved && !rook->moved &&
            this->position == this->initialPos && contains({{0, 4}, {7, 4}}, this->position) &&
            rook->position == rook->initialPos && contains({{0, 0}, {7, 0}, {7, 7}, {0, 7}}, rook->position))
        {
            int direction = rook->position.y < this->position.y ? -1 : 1;
            switch (this->color) {
                case 'w':
                    switch (this->position.y - rook->position.y){
                        case 4:
                            board->castleRights += "K";
                            break;
                        case 5:
                            board->castleRights += "Q";
                            break;
                        default:
                            break;
                    }
                case 'b':
                        switch (this->position.y - rook->position.y){
                            case 4:
                                board->castleRights += "k";
                                break;
                            case 5:
                                board->castleRights += "q";
                                break;
                            default:
                                break;
                        }
                default:
                    break;
            }
        }
    }
}