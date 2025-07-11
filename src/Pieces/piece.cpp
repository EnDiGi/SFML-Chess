
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/utils.h"
#include "../../include/move.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Piece::Piece(char symbol, Chessboard &board, sf::Vector2i pos, bool moved): texture(this->getSpritePath(symbol)), sprite(texture){

    this->sprite.setScale(sf::Vector2f(0.351, 0.351));

    this->initialPos = pos;

    this->moved = moved;
    this->board = &board;
    this->position = pos;

    this->symbol = symbol;
    if(std::isupper(symbol)){
        this->color = 'w';
        this->direction = 1;
    } else{
        this->color = 'b';
        this->direction = -1;
    }

    this->name = getName(symbol);
    this->setPosition();
}

Piece::~Piece(){
    ;
}

void Piece::updateMoves() {
    ;
}

void Piece::makeMove(Cell* target) {
    this->board->movePiece(this->getCell(), target);
    this->moved = true;
}

Cell* Piece::getCell(){
    return this->board->cellAt(this->position);
}

std::string Piece::getSpritePath(char symbol){
    return std::string("..\\assets\\pieces\\") + std::string(1, getColor(symbol)) + getName(symbol) + std::string(".png");
}

void Piece::setPosition(){    
    this->sprite.setPosition(this->getCell()->getPosition());
}

void Piece::updateBoardCastleRights(){
    ;
}

bool Piece::isSafe(){
    return this->isSafe(this->position);
}

bool Piece::isSafe(sf::Vector2i cellPos){

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Piece* piece = this->board->pieceAt(i ,j);

            if(piece == nullptr) continue;
            if(piece->color == this->color) continue;

            for(sf::Vector2i pos : piece->couldTake){
                if(pos == cellPos) return false;
            }
        }
    }
    return true;
}

bool Piece::isSafe(Cell grid[8][8]){
    return this->isSafe(this->position, grid);
}

bool Piece::isSafe(sf::Vector2i cellPos, Cell grid[8][8]){

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Piece* piece = grid[i][j].piece;
            if(piece == nullptr) continue;
            if(piece->color == this->color) continue;

            for(sf::Vector2i pos : piece->couldTake){
                if(pos == cellPos) return false;
            }
        }
    }
    return true;
}

bool Piece::isLegalMove(sf::Vector2i target){
    Move move(0, this, this->board->cellAt(target), false, this->board);
    return move.isLegal();
}
