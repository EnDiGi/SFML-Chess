
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/chessboard.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Cell::Cell() : sf::RectangleShape({112.5, 112.5}){
    this->row = 0;
    this->col = 0;
    this->width = 112.5;
    this->height = 112.5;
    
    this->board = nullptr;
}

Cell::Cell(int row, int col, Chessboard &board): sf::RectangleShape({112.5, 112.5}){
    this->row = row;
    this->col = col;
    this->width = 112.5;
    this->height = 112.5;

    absPosition = sf::Vector2f(this->col * this->width, this->row * this->height);

    this->board = &board;

    this->setPosition(absPosition);
    this->setFillColor(sf::Color(0, 0, 0, 0));
}

void Cell::setPiece(Piece* piece){
    this->piece = piece;
}

bool Cell::isEmpty(){
    return this->piece == nullptr;
}