
#include <SFML/Graphics.hpp>
#include "../include/chessboard.h"
#include "../include/cell.h"
#include "../include/move.h"
#include "../include/pieces/piece.h"
#include "../include/moveCircle.h"
#include "../include/utils.h"
#include <iostream>
#include <algorithm>

int main()
{

    // Load font
    sf::Font font("..\\assets\\inter.ttf");

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({1200, 900}), "Chess");
    window.setMaximumSize(sf::Vector2u(1200, 900));
    window.setMinimumSize(sf::Vector2u(1200, 900));
    window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - 50));

    std::vector<sf::Drawable*> toDraw;
    std::vector<sf::Text> moveTexts;
    std::vector<MoveCircle> moveCircles;

    sf::Text turnText(font, "White's turn", 30);
    turnText.setPosition(sf::Vector2f(910, 10));
    turnText.setFillColor(sf::Color::White);

    Chessboard board;
    for(int k = 0; k < 8; k++){
        for(int l = 0; l < 8; l++){
            if(board.pieceAt(k, l) != nullptr){
                board.pieceAt(k, l)->updateMoves();
            }
        }
    }

    // Start the game loop
    while (window.isOpen())
    {

        toDraw = {};
        moveTexts = {};

        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if(event->is<sf::Event::Closed>())
                window.close();
            
            // * Checks if any cell is pressed
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        for(int j = 0; j < 8; j++)
                        {
                            Cell* cell = board.objectGrid[i][j];
                            if(cell->piece == nullptr){ // If the cell is empty
                                continue;
                            }

                            if(cell->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && cell->piece->color == board.turn)
                            {
                                // Big O notation will suffer for this loop
                                for(int k = 0; k < 8; k++){
                                    for(int l = 0; l < 8; l++){
                                        if(board.cellAt(k, l) != cell){
                                            board.cellAt(k, l)->setFillColor(sf::Color(0, 0, 0, 0));
                                        }
                                    }
                                }

                                // Sets the selected cell to a yellow transparent color
                                cell->setFillColor(sf::Color(255, 255, 200, 70));
                                
                                moveCircles.clear();

                                for(sf::Vector2i pos: cell->piece->canMove)
                                {
                                    MoveCircle circle('m', board.cellAt(pos), cell->piece);
                                    moveCircles.push_back(std::move(circle));
                                }
                                for(sf::Vector2i pos: cell->piece->canTake)
                                {
                                    MoveCircle circle('t', board.cellAt(pos), cell->piece);
                                    moveCircles.push_back(std::move(circle));
                                }
                                for(sf::Vector2i pos: cell->piece->canCastleWith)
                                {
                                    MoveCircle circle('c', board.cellAt(pos), cell->piece);
                                    moveCircles.push_back(std::move(circle));
                                }
                            }
                        }
                    }
                    for(MoveCircle circle : moveCircles){
                        if(circle.cell->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
                            // * A move has been made
                            circle.move(&board);
                            circle.cell->setFillColor(sf::Color(0, 0, 0, 0));
                            moveCircles.clear();            
                            board.turn = opponent(circle.pieceToMove->color);

                            board.updateMoves();
                        }
                    } 
                }
            }
        }

        // Clear screen and sets it to dark gray
        window.clear(sf::Color(30, 30, 30, 255));
        toDraw.push_back(&board.getSprite());
        toDraw.push_back(&turnText);

        
        // Display the last 10 moves (5 moves for black, 5 moves for white)
        std::stack<Move> tempStack = board.moves;
        std::vector<Move> moves;

        while (!tempStack.empty()) {
            moves.push_back(tempStack.top());
            tempStack.pop();
        }

        std::reverse(moves.begin(), moves.end());

        int start = std::max(0, (int)board.moves.size() - 10);
        int row = start + 1;
        for(int i = start; i < moves.size(); i += 2)
        {
            Move whiteMove = moves[i];

            if(whiteMove.piece->color == 'b'){
                i--;
                whiteMove = moves[i];
            }

            double y = (row - start) * 70;

            sf::Text rowText(font, std::to_string(row));
            rowText.setPosition(sf::Vector2f(910, y));

            sf::Text whiteMoveText(font, whiteMove.id, 30);
            whiteMoveText.setPosition(sf::Vector2f(950, y));

            moveTexts.push_back(rowText);
            moveTexts.push_back(whiteMoveText);

            // If the last move is white's so ther isn't any black move, break the loop
            if(i == moves.size() - 1) break;

            Move blackMove = moves[i + 1];

            sf::Text blackMoveText(font, blackMove.id, 30);
            blackMoveText.setPosition(sf::Vector2f(1090, y));

            moveTexts.push_back(blackMoveText);

            row++;

        }

        // Adds to toDraw all the pieces
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++){
                Cell* cell = board.objectGrid[i][j];
                if(cell->piece == nullptr){ // If the cell is empty
                    continue;
                }
                toDraw.push_back(cell);
                toDraw.push_back(&(cell->piece->sprite));
            }
        }
        
        for(sf::Drawable* img : toDraw){
            window.draw(*img);
        }

        for(const sf::Text& text : moveTexts){
            window.draw(text);
        }

        for(sf::CircleShape& circle : moveCircles){
            window.draw(circle);
        }

        if(board.turn == 'w'){
            turnText.setString("White's turn");
        } else {
            turnText.setString("Black's turn");
        }

        // Update the window
        window.display();

    }
}