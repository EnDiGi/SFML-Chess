
#include "../include/utils.h"
#include "../include/chessboard.h"
#include "../include/pieces/pawn.h"
#include "../include/pieces/bishop.h"
#include "../include/pieces/rook.h"
#include "../include/pieces/knight.h"
#include "../include/pieces/queen.h"
#include "../include/pieces/king.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

Piece* getPiece(char symbol, Chessboard &board, sf::Vector2i pos, bool moved){

    switch(std::tolower(symbol)){
        case 'p':
            return new Pawn(symbol, board, pos, moved);
            break;
        case 'r':
            return new Rook(symbol, board, pos, moved);
            break;
        case 'n':
            return new Knight(symbol, board, pos, moved);
            break;
        case 'b':
            return new Bishop(symbol, board, pos, moved);
            break;
        case 'k':
            return new King(symbol, board, pos, moved);
            break;
        case 'q':
            return new Queen(symbol, board, pos, moved);
            break;
        default:
            return nullptr;
            break;
    }
}

std::vector<std::string> split(std::string &string, std::string &sep) {
    std::vector<std::string> result;
    size_t pos_start = 0, pos_end;
    while ((pos_end = string.find(sep, pos_start)) != std::string::npos){
        result.push_back(string.substr(pos_start, pos_end - pos_start));
        pos_start = pos_end + sep.length();
    }
    result.push_back(string.substr(pos_start));
    return result;
}


// Returns a string containing the name of the piece given its FEN notation
std::string getName(char symbol){
    switch(std::tolower(symbol)){
        case 'k':
            return "king";
            break;
        case 'q':
            return "queen";
            break;
        case 'r':
            return "rook";
            break;
        case 'b':
            return "bishop";
            break;
        case 'n':
            return "knight";
            break;
        case 'p':
            return "pawn";
            break;
        default:
            return " ";
    }
}

char getColor(char symbol){
    return std::isupper(symbol) ? 'w' : 'b';
}

char getSymbol(char color, std::string name){
    char symbol = ' ';

    if(name == "king"){
        symbol = 'k';
    } else if(name == "queen"){
        symbol = 'q';
    } else if(name == "rook"){
        symbol = 'r';
    } else if(name == "knight"){
        symbol = 'n';
    } else if(name == "bishop"){
        symbol = 'b';
    } else if(name == "pawn"){
        symbol = 'p';
    }

    if(color == 'w'){
        symbol = std::toupper(symbol);
    }

    return symbol;
}