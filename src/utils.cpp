
#include "../include/utils.h"
#include <iostream>
#include "../include/chessboard.h"
#include "../include/pieces/pawn.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


Piece* getPiece(char symbol, Chessboard &board, sf::Vector2i pos){

    switch(std::tolower(symbol)){
        case 'p':
            return new Pawn(symbol, board, pos);
            break;
        // case 'r':
        //     return new Rook(symbol, board, pos);
        //     break;
        // case 'n':
        //     return new Knight(symbol, board, pos);
        //     break;
        // case 'b':
        //     return new Bishop(symbol, board, pos);
        //     break;
        // case 'k':
        //     return new King(symbol, board, pos);
        //     break;
        // case 'q':
        //     return new Queen(symbol, board, pos);
        //     break;
        default:
            return new Pawn(symbol, board, pos);
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