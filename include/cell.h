
#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Chessboard;
class Piece;

class Cell: public sf::RectangleShape{

    public:

        int row;
        int col;
        double width;
        double height;
        // Pointer to the chessboard
        Chessboard* board;

        // Pointer to the piece on the cell
        Piece* piece;

        Cell(int row, int col, Chessboard &board);

        void setPiece(Piece* piece);
};

#endif