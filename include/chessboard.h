
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Cell;

class Chessboard{
    private:
        sf::Texture texture;
        sf::Sprite sprite;

        void emptyCell(Cell* cell);
        
        void setCell(Cell* cellA, char pieceSymbol);
        
        void updateFEN();
        
        void updateCharGrid();
        
        void updateObjGrid();
        
        void updateGrid();
        
    public:
        // The side of the board
        int side;
        
        // Stores an 8x8 grid containg a character for each piece in the chessboard
        char charGrid[8][8];

        /*  Stores the cell object for each cell of the chessboard
            N.B.: If the cell is empty the value will be nulltpr
            N.B.: objectGrid[0][0] is the top left corner
        */
        Cell* objectGrid[8][8];

        // Stores a FEN string containing the board
        std::string fenString;

        // Stores 'w' or 'b' depending on whose turn it is
        char turn;

        std::string castleRights;

        Chessboard();

        ~Chessboard();

        void movePiece(Cell* cellA, Cell* cellB);

        bool squareIsOccupied(int x, int y);

        bool squareIsOccupied(sf::Vector2i pos);

        sf::Sprite getSprite();
};

#endif