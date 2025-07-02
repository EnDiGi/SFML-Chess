
#include "../../include/pieces/piece.h"
#include "../../include/chessboard.h"
#include "../../include/cell.h"
#include "../../include/utils.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Piece::Piece(char symbol, Chessboard &board, sf::Vector2i pos): texture(this->getSpritePath(symbol)), sprite(texture){

    this->sprite.setScale(sf::Vector2f(0.351, 0.351));

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
    ;
}

Cell* Piece::getCell(){
    return this->board->objectGrid[this->position.x][this->position.y];
}

std::string Piece::getSpritePath(char symbol){
    return std::string("assets\\pieces\\") + std::string(1, getColor(symbol)) + getName(symbol) + std::string(".png");
}

void Piece::setPosition(){    
    this->sprite.setPosition(this->getCell()->getPosition());
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    os << piece.name << " (" << piece.symbol << ")";
    return os;
}