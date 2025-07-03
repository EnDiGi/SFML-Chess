

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/moveCircle.h"
#include "../include/chessboard.h"
#include <iostream>

MoveCircle::MoveCircle(char mode, Cell &cell, Piece &pieceToMove, int radius): sf::CircleShape(radius){
    this->pieceToMove = &pieceToMove;
    this->cell = &cell;

    if(mode == 'm'){
        this->setFillColor(sf::Color(144, 144, 144, 200));
    } else{
        this->setFillColor(sf::Color(255, 59, 59, 200));
    }
    
    this->setPosition(sf::Vector2f(this->cell->col * this->cell->width  + this->cell->width  / 2 - 15, 
                                   this->cell->row * this->cell->height + this->cell->height / 2 - 15));
}

void MoveCircle::move(Chessboard &board){
    board.movePiece(this->pieceToMove, this->cell);
}
