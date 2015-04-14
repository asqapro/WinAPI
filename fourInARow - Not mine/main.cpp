////////////////////////////////////////////////////////////
// Copyright (c) 2009 Rodrigo Castro (redkiing)
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//
// Rodrigo Castro redkiing.wordpress.com
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// main.cpp
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "board.h"
#include "uInterface.h"

int main()
{
    // Create the main window, using the best available resolution
    //sf::RenderWindow App(sf::VideoMode::GetMode(0),
    //        "Your first SFML game: 4 in a row!");

    // If you want antialiasing in your game, you can use these
    // lines of code instead of the above ones:

    unsigned int antialias = 8;
    sf:: RenderWindow App(sf::VideoMode::GetMode(0),
            "Your first SFML game: 4 in a row!",
            sf::Style::Resize|sf::Style::Close,
            sf::WindowSettings::WindowSettings ( 24, 8, antialias));


    // Reduce CPU usage by limiting the times a frame
    // is drawn per second
    App.SetFramerateLimit(30);

    // Create a 4 in a row board
    Board board(App);

    // Create the user interface
    UInterface ui(board);

    // This is the main loop
    // It will loop until you exit the program
    while (App.IsOpened())
    {
        // Here we process the events list
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
            else if (Event.Type == Event.MouseButtonReleased && Event.MouseButton.Button == sf::Mouse::Left)
                ui.placeInColumn(App.GetInput());
        }

        // Clear the screen with a color
        App.Clear(board.boardColor);

        // Here you will draw all stuff in the frame buffer
        // Draw the board
        board.draw();

        // Render the frame on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}
