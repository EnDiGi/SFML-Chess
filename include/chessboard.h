
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <stack>

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
        
        void createObjGrid();

        std::vector<Piece*> eatenPieces;

        
        public:
        // The side of the board
        int side;
        
        /*  Stores the cell object for each cell of the chessboard
            N.B.: If the cell is empty the value will be nulltpr
            N.B.: objectGrid[0][0] is the top left corner
        */
       Cell* objectGrid[8][8];
       
       // Stores a FEN string containing the board
       std::string fenString;
       
        // Contains every move played in the game
        std::stack<Move> moves;

        // Stores 'w' or 'b' depending on whose turn it is
        char turn;
        
        int turnNumber = 0;
        
        std::string castleRights;
        
        Chessboard(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0");
        
        ~Chessboard();
        
        void updateMoves(bool onlyPseudo = false);

        void movePiece(Cell* cellA, Cell* cellB, bool addMove = true, bool wasMoved = true);

        void movePiece(Piece* piece, Cell* targetCell, bool addMove = true, bool wasMoved = true);

        void addMove(Piece* piece, Cell* cell);

        void undoMove();

        void updateEnemyPseudoMoves(char color);

        bool squareIsOccupied(int x, int y);

        bool squareIsOccupied(sf::Vector2i pos);

        bool isInsideBoard(int x, int y);

        bool isInsideBoard(sf::Vector2i pos);

        bool noPieceInBetweenHorizontally(Piece* pieceA, Piece* pieceB);

        std::vector<Piece*> getPieceOnBoard(char color, std::string name);

        bool isCheckmate(char color);

        sf::Sprite& getSprite();

        Piece* pieceAt(int x, int y);

        Piece* pieceAt(sf::Vector2i pos);

        Cell* cellAt(int x, int y);

        Cell* cellAt(sf::Vector2i pos);
};

#endif