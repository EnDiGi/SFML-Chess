
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

void Chessboard::movePiece(Cell* cellA, Cell *cellB, bool addMove){
    
    
    Piece* movingPiece = cellA->piece;
    if(movingPiece == nullptr) return;

    movingPiece->moved = true;

    if(turn == 'w') this->turnNumber++;

    if(addMove)
    {
        Move* move = new Move(this->turnNumber, movingPiece, cellB, cellB->piece != nullptr, this);
        this->moves.push_back(move);
    }
    
    this->setCell(cellB, movingPiece);
    cellB->piece->position = sf::Vector2i(cellB->row, cellB->col);
    this->emptyCell(cellA);

    this->updateFEN();


}

void Chessboard::movePiece(Piece* piece, Cell* targetCell, bool addMove){
    this->movePiece(piece->getCell(), targetCell, addMove);
}

void Chessboard::emptyCell(Cell* cell){
    this->charGrid[cell->row][cell->col] = ' ';
    cell->piece = nullptr;
}

void Chessboard::setCell(Cell* cell, Piece* piece){
    this->charGrid[cell->row][cell->col] = piece->symbol;
    delete cell->piece;
    cell->setPiece(getPiece(piece->symbol, *this, sf::Vector2i({cell->row, cell->col}), piece->moved));
}

bool Chessboard::squareIsOccupied(int x, int y) {
    if (!isInsideBoard(x, y)) return false;
    Cell* cell = this->cellAt(x, y);
    return cell && cell->piece;
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

void Chessboard::updateFEN() {
    this->fenString = "";

    for(int i = 0; i < this->side; i++) {
        int spaces = 0;  // contatore spazi vuoti consecutivi

        for(int j = 0; j < this->side; j++) {
            char cell = charGrid[i][j];

            if(cell == ' ') {
                spaces++;
            } else {
                if(spaces > 0) {
                    this->fenString += std::to_string(spaces);
                    spaces = 0;
                }
                this->fenString += cell;
            }
        }

        if(spaces > 0) {
            this->fenString += std::to_string(spaces);
        }

        if(i != this->side - 1) this->fenString += "/";
    }

    this->fenString += " " + this->turn;

    this->castleRights = "";
    for(Piece* king : this->getPieceOnBoard('w', "king")){
        king->updateBoardCastleRights();
    }
    for(Piece* king : this->getPieceOnBoard('b', "king")){
        king->updateBoardCastleRights();
    }

    this->fenString += " " + (this->castleRights.length() > 0 ? this->castleRights : "-");
}


// Updates the charGrid using the fen string
void Chessboard::createCharGrid() {
    std::string sep = "/";
    std::string fenBoard = this->fenString.substr(0, this->fenString.find(' '));
    std::string turn = this->fenString.substr(this->fenString.find(' ') + 1, this->fenString.find(' ') + 2);
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

    this->turn = turn[0];
}



// Updates the object grid using the char grid
void Chessboard::createObjGrid(){

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

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Cell* cell = this->cellAt(i, j);

            if(cell->piece == nullptr) continue;

            if(cell->piece->name == name && cell->piece->color == color){
                pieces.push_back(cell->piece);
            }

        }
    }
    return pieces;
}

std::vector<Piece*> Chessboard::getPieceOnBoard(char color, std::string name, Cell grid[8][8])
{

    std::vector<Piece*> pieces;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            Cell cell = grid[i][j];

            if(cell.piece == nullptr) continue;

            if(cell.piece->name == name && cell.piece->color == color){
                pieces.push_back(cell.piece);
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
        Cell* cellToCheck = this->cellAt(pos.x, pos.y + i);
        if(cellToCheck->piece == pieceB) return true;
        if(cellToCheck->piece != nullptr) break; // There is a piece
    }
    
    // Checks on the left
    for(int i = 1; i < 8; i++){
        // The next position on the same row
        Cell* cellToCheck = this->cellAt(pos.x, pos.y - i);
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
                Cell* cell = this->cellAt(i, j);

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

Piece* Chessboard::pieceAt(int x, int y){
    return this->objectGrid[x][y]->piece;
}

Piece* Chessboard::pieceAt(sf::Vector2i pos){
    return this->pieceAt(pos.x, pos.y);
}

Cell* Chessboard::cellAt(int x, int y){
    return this->objectGrid[x][y];
}

Cell* Chessboard::cellAt(sf::Vector2i pos){
    return this->cellAt(pos.x, pos.y);
}