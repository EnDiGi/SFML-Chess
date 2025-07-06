

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/moveCircle.h"
#include "../include/chessboard.h"
#include <iostream>

MoveCircle::MoveCircle(char mode, Cell &cell, Piece &pieceToMove, int radius): sf::CircleShape(radius){
    this->mode = mode;
    this->pieceToMove = &pieceToMove;
    this->cell = &cell;

    if(mode == 'm'){
        this->setFillColor(sf::Color(144, 144, 144, 200));
    } else if(mode == 't'){
        this->setFillColor(sf::Color(255, 59, 59, 200));
    } else {
        this->setFillColor(sf::Color(66, 135, 245, 200));
    }
    
    this->setPosition(sf::Vector2f(this->cell->col * this->cell->width  + this->cell->width  / 2 - 15, 
                                   this->cell->row * this->cell->height + this->cell->height / 2 - 15));
}

void MoveCircle::move(Chessboard* board){
    if(this->mode != 'c' || this->pieceToMove->castled)
    {
        board->movePiece(this->pieceToMove, this->cell);
    } 
    else
    {
        // -1 if the rook is on the left, 1 if it's on the right
        int direction = this->cell->col < this->pieceToMove->position.y ? -1 : 1;
        Piece* rook = board->objectGrid[cell->row][cell->col + direction]->piece;

        if(rook == nullptr){ // Handles queenside castling where the rook is a square farther
            rook = board->objectGrid[cell->row][cell->col + direction * 2]->piece;
        }

        // * Move the pieces
        sf::Vector2i kingCell = {this->pieceToMove->position.x, this->pieceToMove->position.y + 2 * direction};
        sf::Vector2i rookCell = {this->pieceToMove->position.x, this->pieceToMove->position.y + direction};
        // Move the king
        board->movePiece(this->pieceToMove, board->objectGrid[kingCell.x][kingCell.y]);
        std::cout << "king moved. all ok!" << std::endl;
        // Move the rook
        board->movePiece(rook, board->objectGrid[kingCell.x][kingCell.y - direction]);
        std::cout << "rook moved! YEEEEEES" << std::endl;
        
        // Fake move bacause after two moves the turns remains the same
        board->movePiece(this->pieceToMove, this->pieceToMove->getCell());

        this->pieceToMove->castled = true;
        rook->castled = true;
    }
}
