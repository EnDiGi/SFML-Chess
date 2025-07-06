
#include "../include/chessboard.h"
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/move.h"
#include "../include/utils.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

Chessboard::Chessboard(std::string fen): texture("..\\assets\\chessboard.png"), sprite(texture){
    this->side = 8;
    this->turn = 'w';
    this->fenString = fen;
    this->createGrid();
}

Chessboard::~Chessboard(){
    for(int i = 0; i < this->side; i++){
        for(int j = 0; j < this->side; j++){
            if(this->objectGrid[i][j]->piece != nullptr){
                delete this->objectGrid[i][j]->piece;
            }
            delete this->objectGrid[i][j];
        }
    }
    for(Move* move : this->moves){
        delete move;
    }
}

void Chessboard::movePiece(Cell* cellA, Cell *cellB){
    
    
    Piece* movingPiece = cellA->piece;
    if(movingPiece == nullptr) return;

    movingPiece->moved = true;


    if(turn == 'w') this->turnNumber++;

    Move* move = new Move(movingPiece->color, this->turnNumber, movingPiece, cellB, cellB->piece != nullptr);
    this->moves.push_back(move);

    this->setCell(cellB, movingPiece);
    cellB->piece->position = sf::Vector2i(cellB->row, cellB->col);
    this->emptyCell(cellA);

    // std::cout << std::endl;
    // for(int i = 0; i < 8; i++){
    //     for(int j = 0; j < 8; j++){
    //         std::cout << this->charGrid[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }

}

void Chessboard::movePiece(Piece* piece, Cell* targetCell){
    this->movePiece(piece->getCell(), targetCell);
}

void Chessboard::emptyCell(Cell* cell){
    this->charGrid[cell->row][cell->col] = ' ';
    cell->piece = nullptr;
}

void Chessboard::setCell(Cell* cell, Piece* piece){
    this->charGrid[cell->row][cell->col] = piece->symbol;
    delete cell->piece;
    cell->piece = getPiece(piece->symbol, *this, sf::Vector2i({cell->row, cell->col}), piece->moved);
}

bool Chessboard::squareIsOccupied(int row, int col){
    return charGrid[row][col] != ' ';
}

bool Chessboard::squareIsOccupied(sf::Vector2i pos){
    return this->squareIsOccupied(pos.x, pos.y);
}

bool Chessboard::isInsideBoard(int x, int y){
    return (x >= 0) && (x < 8) && (y >= 0) && (y < 8);
}

bool Chessboard::isInsideBoard(sf::Vector2i pos){
    return isInsideBoard(pos.x, pos.y);
}

void Chessboard::createGrid(){
    this->createCharGrid();
    this->createObjGrid();
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

/**
 * Updates the charGrid using the fen string
 */
void Chessboard::createCharGrid() {
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
                    charGrid[i][col++] = ' ';  // FEN parte dalla riga 8, quindi 7-i
                }
            } else {
                charGrid[i][col++] = ch;
            }
        }
    }
}



/**
 * Updates the object grid using the char grid
 */
void Chessboard::createObjGrid(){
    
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << this->charGrid[i][j] << " ";
        }
        std::cout << '\n';
    }


    // * Creating new cells and putting in them pieces
    for(int i = 0; i < this->side; i++){
        for(int j = 0; j < this->side; j++){

            char ch = charGrid[i][j];

            Cell* cell = new Cell(i, j, *this);
            this->objectGrid[i][j] = cell;
            
            if(ch == ' '){
                this->objectGrid[i][j]->piece = nullptr;
                continue;
            }
            cell->piece = getPiece(ch, *this, sf::Vector2i({cell->row, cell->col}), false);
        }
    }
}

std::vector<Piece*> Chessboard::getPieceOnBoard(char color, std::string name)
{

    std::vector<Piece*> pieces;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Cell* cell = this->objectGrid[i][j];

            if(cell->piece == nullptr) continue;

            if(cell->piece->name == name && cell->piece->color == color){
                pieces.push_back(cell->piece);
            }

        }
    }
    return pieces;
}

bool Chessboard::noPieceInBetweenHorizontally(Piece* pieceA, Piece* pieceB){
    sf::Vector2i pos = pieceA->position;
    
    // Checks on the right of the piece
    for(int i = 1; i < 8; i++){
        // The next position on the same row
        Cell* cellToCheck = this->objectGrid[pos.x][pos.y + i];
        if(cellToCheck->piece == pieceB) return true;
        if(cellToCheck->piece != nullptr) break; // There is a piece
    }
    
    // Checks on the left
    for(int i = 1; i < 8; i++){
        // The next position on the same row
        Cell* cellToCheck = this->objectGrid[pos.x][pos.y - i];
        if(cellToCheck->piece == pieceB) return true;
        if(cellToCheck->piece != nullptr) break; // There is a piece
    }

    return false;
}


bool Chessboard::isCheckmate(char color){
    std::vector<Piece*> kings = this->getPieceOnBoard(color, "king");
    if(kings.empty()) return true;
    Piece* king = kings[0];


    if(king->canMove == king->canTake && king->canMove.size() == 0){
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                Cell* cell = this->objectGrid[i][j];

                if(cell->piece == nullptr) continue;
                
                if(cell->piece->color != color) continue;
                
                // TODO: implement check if any piece can block the check
            }
        }
    }

    return false;
}



sf::Sprite& Chessboard::getSprite(){
    return this->sprite;
}