
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Cell;
class Piece;
class King;
class Move;

class Chessboard{
    private:
        sf::Texture texture;
        sf::Sprite sprite;

        void emptyCell(Cell* cell);
        
        void setCell(Cell* cellA, Piece* piece);
        
        void updateFEN();
        
        void createCharGrid();
        
        void createObjGrid();
        
        void createGrid();
        
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

        // Contains every move played in the game
        std::vector<Move*> moves;

        // Stores 'w' or 'b' depending on whose turn it is
        char turn;

        int turnNumber = 0;

        std::string castleRights;

        Chessboard(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        ~Chessboard();

        void movePiece(Cell* cellA, Cell* cellB);

        void movePiece(Piece* piece, Cell* targetCell);

        bool squareIsOccupied(int x, int y);

        bool squareIsOccupied(sf::Vector2i pos);

        bool isInsideBoard(int x, int y);

        bool isInsideBoard(sf::Vector2i pos);

        bool noPieceInBetweenHorizontally(Piece* pieceA, Piece* pieceB);

        std::vector<Piece*> getPieceOnBoard(char color, std::string name);

        bool isCheckmate(char color);

        sf::Sprite& getSprite();
};

#endif