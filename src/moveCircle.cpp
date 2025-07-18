

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/moveCircle.h"
#include "../include/move.h"
#include "../include/utils.h"
#include "../include/chessboard.h"
#include <iostream>

MoveCircle::MoveCircle(char mode, Cell* cell, Piece* pieceToMove, int radius): sf::CircleShape(radius){
    this->mode = mode;
    this->pieceToMove = pieceToMove;
    this->cell = cell;

    if(mode == 'm'){
        this->setFillColor(sf::Color(144, 144, 144, 200));
    } else if(mode == 't'){
        this->setFillColor(sf::Color::Transparent);
        this->setRadius(55);
        this->setOutlineThickness(-10);
        this->setOutlineColor(sf::Color(144, 144, 144, 200));
    } else {
        this->setFillColor(sf::Color(66, 135, 245, 200));
    }

    
    this->setPosition(sf::Vector2f(this->cell->col * this->cell->width  + this->cell->width  / 2 - this->getRadius(), 
                                   this->cell->row * this->cell->height + this->cell->height / 2 - this->getRadius()));
}

void MoveCircle::move(Chessboard* board){
    if(this->mode != 'c' || this->pieceToMove->castled)
    {
        board->movePiece(this->pieceToMove, this->cell);
    } 
    else
    {
        bool kingSide = true;
        // -1 if the rook is on the left, 1 if it's on the right
        int direction = this->cell->col < this->pieceToMove->position.y ? -1 : 1;
        Piece* rook = board->pieceAt(cell->row, cell->col + direction);

        if(rook == nullptr){ // Handles queenside castling where the rook is a square farther
            rook = board->pieceAt(cell->row, cell->col + direction * 2);
            kingSide = false;
        }

        // * Move the pieces
        sf::Vector2i kingCell = {this->pieceToMove->position.x, this->pieceToMove->position.y + 2 * direction};
        sf::Vector2i rookCell = {this->pieceToMove->position.x, this->pieceToMove->position.y + direction};
        
        Move move(board->turnNumber, this->pieceToMove, rook, kingSide, board);
        board->moves.push(move);

        // Move the king
        board->movePiece(this->pieceToMove, board->cellAt(kingCell), false);
        // Move the rook
        board->movePiece(rook, board->cellAt(kingCell.x, kingCell.y - direction), false);

        board->turn = opponent(this->pieceToMove->color);

        this->pieceToMove->castled = true;
        rook->castled = true;
    }
}
