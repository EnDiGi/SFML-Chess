
#include <SFML/Graphics.hpp>
#include "../include/chessboard.h"
#include "../include/cell.h"
#include "../include/pieces/piece.h"
#include "../include/pieces/pawn.h"
#include <iostream>


bool isUnderMouse(sf::Vector2f pos, sf::Vector2f size){
    sf::Vector2i mouse = sf::Mouse::getPosition();
    if(mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y) return true;
    return false;
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({900, 900}), "Chess");
    
    Chessboard board;
    std::cout << "\nchessboard is ok\n";

    // Start the game loop
    while (window.isOpen())
    {

        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if(event->is<sf::Event::Closed>())
                window.close();
        }
 
        // Clear screen and sets it to dark gray
        window.clear(sf::Color(30, 30, 30, 255));
        window.draw(board.getSprite());
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Cell* cell = board.objectGrid[i][j];
                if(cell->piece == nullptr){ // If the cell is empty
                    continue;
                }
                window.draw(cell->piece->sprite);
            }
        }

        // Update the window
        window.display();

    }
}