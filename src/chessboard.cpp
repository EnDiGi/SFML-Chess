
#include "../include/chessboard.h"
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/pieces/pawn.h"
#include "../include/utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

Chessboard::Chessboard(): texture("assets\\chessboard.png"), sprite(texture){
    this->side = 8;
    this->turn = 'w';
    this->fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    this->updateGrid();
}

Chessboard::~Chessboard(){
    for(int i = 0; i < this->side; i++){
        for(int j = 0; j < this->side; j++){
            delete this->objectGrid[i][j]->piece;
            delete this->objectGrid[i][j];
        }
    }
}

void Chessboard::movePiece(Cell* cellA, Cell *cellB){
    this->setCell(cellB, cellA->piece->symbol);
    this->emptyCell(cellA);
}

void Chessboard::emptyCell(Cell* cell){
    this->charGrid[cell->row][cell->col] = ' ';
    cell->piece = nullptr;
}

void Chessboard::setCell(Cell* cell, char pieceSymbol){
    this->charGrid[cell->row][cell->col] = cell->piece->symbol;
    cell->piece = getPiece(pieceSymbol, *this, sf::Vector2i({cell->row, cell->col}));
}

bool Chessboard::squareIsOccupied(int x, int y){
    return charGrid[x][y] != ' ';
}

bool Chessboard::squareIsOccupied(sf::Vector2i pos){
    return this->squareIsOccupied(pos.x, pos.y);
}

void Chessboard::updateGrid(){
    this->updateCharGrid();
    this->updateObjGrid();
}

void Chessboard::updateFEN(){

    fenString = "";

    for(int i = this->side-1; i >= 0; i--){
        
        // Consecutive empty spaces in the chessboard
        int spaces = 0;

        for(int j = this->side-1; j >= 0; j--){
            
            char cell = charGrid[i][j];

            if(cell == ' '){
                spaces++;
                continue;
            } else if(spaces != 0){
                // Adds the number of empty cells
                fenString += std::to_string(spaces);
            }
        }

        fenString += "/";
    }
}

void Chessboard::updateCharGrid() {
    std::string sep = "/";
    std::string fenBoard = this->fenString.substr(0, this->fenString.find(' '));
    std::vector<std::string> lines = split(fenBoard, sep);

    for (int i = 0; i < 8; i++) {
        const std::string& line = lines[i];
        int col = 0;

        for (char ch : line) {
            if (std::isdigit(ch)) {
                int emptySpaces = ch - '0';
                for (int k = 0; k < emptySpaces; k++) {
                    charGrid[7 - i][col++] = ' ';  // FEN parte dalla riga 8, quindi 7-i
                }
            } else {
                charGrid[7 - i][col++] = ch;
            }
        }
    }
}


void Chessboard::updateObjGrid(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << this->charGrid[i][j] << " ";
        }
        std::cout << '\n';
    }
    for(int i = 0; i < this->side; i++){
        for(int j = 0; j < this->side; j++){

            char ch = charGrid[i][j];

            Cell* cell = new Cell(i, j, *this);
            this->objectGrid[i][j] = cell;
            if(ch == ' '){
                this->objectGrid[i][j]->piece = nullptr;
                continue;
            }



            if(getName(ch) == "pawn"){
                Pawn* pawn = new Pawn(ch, *this, sf::Vector2i({i, j}));
                cell->setPiece(pawn);
            }

            
        }
    }
}

sf::Sprite Chessboard::getSprite(){
    return this->sprite;
}