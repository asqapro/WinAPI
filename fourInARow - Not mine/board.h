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
// board.h
////////////////////////////////////////////////////////////

#ifndef BOARD
#define BOARD

#include <SFML/Graphics.hpp>

#define BOARD_Y_SIZE 6
#define BOARD_X_SIZE 7

// These are the kind of tokens found in the board
enum Token
{
    Empty,
    Red,
    Yellow,
};

// And these, the outline types of the tokens
enum Outline
{
    Normal,
    Highlight
};

// Returned when trying to place a token in a column
enum Move
{
    Placed,
    Full,
    EndOfGame
};

// This class has all the methods and properties to be used
// in the game board
class Board
{
    public:
        // Constructor
        Board(sf::RenderWindow &App);
        // Destructor
        ~Board();
        // Sets the board to empty tokens
        void restart();

        // Used to draw the board on screen
        void draw();

        // Called in each turn
        Move addTokenInColumn(unsigned int column, Token playerColor);

        // Gets the original window width
        int getWindowWidth();

        // The color of the gameboard
        sf::Color::Color boardColor;
    private:

        // Used to know if a player has won
        bool isEndOfGame   (const unsigned int y, const unsigned int x);
        bool fourHorizontal(const unsigned int y, const unsigned int x);
        bool fourVertical  (const unsigned int y, const unsigned int x);
        bool fourDiagonal  (const unsigned int y, const unsigned int x);

        // The matrix that represents the board in memory
        // Add borders to ease the search of a winnefr combination
        Token board[BOARD_Y_SIZE+2][BOARD_X_SIZE+2];

        Outline boardOutline[BOARD_Y_SIZE+2][BOARD_X_SIZE+2];

        // The window where to draw the board
        sf::RenderWindow &myWindow;

        // Colors of the board
        sf::Color redColor;
        sf::Color yellowColor;
        sf::Color emptyColor;
        sf::Color lineColor;
        sf::Color highlightColor;

        // Properties that define the size of a token
        float windowHeight;
        float windowWidth;
        // The size of the outline token brush
        float outline;
        // The radius of a token
        float radius;
        // The space between tokens
        float spaceY, spaceX;

};

#endif
