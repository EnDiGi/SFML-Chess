
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Chessboard;
class Cell;

class Piece{
    protected:
        // Pointer to the chessboard
        Chessboard* board;
        // The direction in which the pawn is facing. Used for calculations. 1 = white, -1 = black
        int direction;
        
        sf::Texture texture;
        
        
    public:
        sf::Sprite sprite;
        // Indicates if the piece moved. Used for castling
        bool moved = false;        
        // Contains the cells in which the piece can move
        std::vector<sf::Vector2i> canMove;
        // Contains the cells in which the piece can take other pieces
        std::vector<sf::Vector2i> canTake;
        std::string name;
        // The piece's color ('w' for white 'b' for black)
        char color;
        // The piece's symbol (k = king, q = queen, r = rook, n = knight, b = bishop) N.B.: It can be capital or lower based on color
        char symbol;
        // Stores the piece's relative to the grid (row, column)
        sf::Vector2i position;

        Piece(char symbol, Chessboard &board, sf::Vector2i pos, bool moved);

        virtual ~Piece();
        
        virtual void updateMoves();

        void makeMove(Cell* target);

        std::string getSpritePath(char symbol);

        Cell* getCell();

        void setPosition();
};

#endif