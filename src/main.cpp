
#include <SFML/Graphics.hpp>
#include "../include/chessboard.h"
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/pieces/pawn.h"
#include "../include/moveCircle.h"
#include <iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({900, 900}), "Chess");
    window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - 50));
    std::vector<sf::Drawable*> toDraw;
    std::vector<MoveCircle> moveCircles;


    Chessboard board;

    // Start the game loop
    while (window.isOpen())
    {

        toDraw = {};

        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if(event->is<sf::Event::Closed>())
                window.close();
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                // * Checks if any cell is pressed
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                        Cell* cell = board.objectGrid[i][j];
                        if(cell->piece == nullptr){ // If the cell is empty
                            continue;
                        }
                        if(cell->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && cell->piece->color == board.turn){
                            moveCircles = {};

                            for(sf::Vector2i pos: cell->piece->canMove){
                                MoveCircle circle('m', *board.objectGrid[pos.x][pos.y], *cell->piece);
                                moveCircles.push_back(circle);
                            }
                            for(sf::Vector2i pos: cell->piece->canTake){
                                MoveCircle circle('t', *board.objectGrid[pos.x][pos.y], *cell->piece);
                                moveCircles.push_back(circle);
                            }
                        }
                    }
                }

                // * Checks if any moveCircle is pressed
                for(MoveCircle circle : moveCircles){
                    if(circle.cell->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
                        circle.move(board);
                        moveCircles.clear();                   
                        board.turn = board.turn == 'w' ? 'b' : 'w';
                    }
                }
            }
        }
 
        // Clear screen and sets it to dark gray
        window.clear(sf::Color(30, 30, 30, 255));


        toDraw.push_back(&(board.getSprite()));

        // Adds to toDraw all the pieces
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Cell* cell = board.objectGrid[i][j];
                if(cell->piece == nullptr){ // If the cell is empty
                    continue;
                }
                toDraw.push_back(&(cell->piece->sprite));
                cell->piece->updateMoves(); // Contantly updates available moves
            }
        }


        for(auto img : toDraw){
            window.draw(*img);
        }

        for(sf::CircleShape& circle : moveCircles){
            window.draw(circle);
        }

        // Update the window
        window.display();

    }
}