
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

        bool castled = false;
        // Contains the cells in which the piece can move
        std::vector<sf::Vector2i> canMove;
        // Contains the cells in which the piece can take other pieces
        std::vector<sf::Vector2i> canTake;
        // Contains the cell in which the piece COULD take if there it was a piece
        std::vector<sf::Vector2i> couldTake;
        // Contains the cells containing the pieces with which the pieces could castle (it's just for the king)
        std::vector<sf::Vector2i> canCastleWith;

        std::string name;
        // The piece's color ('w' for white 'b' for black)
        char color;
        // The piece's symbol (k = king, q = queen, r = rook, n = knight, b = bishop) N.B.: It can be capital or lower based on color
        char symbol;
        // Stores the piece's relative to the grid (row, column)
        sf::Vector2i position;
        // Stores the initial position of the piece (row, column)
        sf::Vector2i initialPos;

        Piece(char symbol, Chessboard &board, sf::Vector2i pos, bool moved);

        virtual ~Piece();
        
        virtual void updateMoves();

        void makeMove(Cell* target);

        std::string getSpritePath(char symbol);

        virtual void updateBoardCastleRights();

        bool isSafe();

        bool isSafe(sf::Vector2i position);

        bool isSafe(Cell grid[8][8]);

        bool isSafe(sf::Vector2i position, Cell grid[8][8]);

        bool isLegalMove(sf::Vector2i target);

        Cell* getCell();

        void setPosition();
};

#endif