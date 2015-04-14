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
// board.cpp
////////////////////////////////////////////////////////////

#include "board.h"

Board::Board(sf::RenderWindow &App) : myWindow (App)
{
    // Set the colors of the board
    boardColor      = sf::Color::Color(0, 102, 153);
    redColor        = sf::Color::Color(214, 71, 0);
    yellowColor     = sf::Color::Color(235,235,0);
    emptyColor      = sf::Color::Color(224,224,224);
    lineColor       = sf::Color::Color(0, 51, 102);
    highlightColor  = sf::Color::Color(255, 153, 0);

    // Get the size of the window
    // in order to calculate the size of a token
    windowHeight = myWindow.GetHeight();
    windowWidth  = myWindow.GetWidth();

    // Get the best circle size
    if (windowHeight < windowWidth)
    {
        radius = windowHeight/(BOARD_Y_SIZE*2.0);
        // set the vertical space between circles equal
        // to 1/2 of the radius
        spaceY = 1.0/2.0 * radius;
        // set the outline of the circle as 1/15 of the radius
        outline = 1.0/15.0 * radius;
        // decrease the radius, by substracting the space
        // between circles and its outline
        radius = radius - spaceY/2.0 - outline;
        // set the horizontal space, knowing that there are
        // BOARD_X_SIZE circles and BOARD_X_SIZE + 1 spaces in a row
        spaceX = (windowWidth-(BOARD_X_SIZE*2.0)*radius)/(BOARD_X_SIZE + 1.0);
    }
    else
    {
        radius = windowWidth/(BOARD_X_SIZE*2.0);
        // set the horizontal space between circles equal
        // to 1/2 of the radius
        spaceX = 1.0/2.0 * radius;
        // set the outline of the circle as 1/15 of the radius
        outline = 1.0/15.0 * radius;
        // decrease the radius, by substracting the space
        // between circles and its outline
        radius = radius - spaceX/2.0 - outline;
        // set the horizontal space, knowing that there are
        // BOARD_Y_SIZE circles and BOARD_Y_SIZE + 1 spaces in a row
        spaceX = (windowWidth-(BOARD_Y_SIZE*2.0)*radius)/(BOARD_Y_SIZE + 1.0);
    }

    // Empty the board
    restart();
}

// Fill this destructor if needed
Board::~Board(){}

void Board::restart()
{
    // Change the value of all the elements of board to Empty
    for(int y=0; y<BOARD_Y_SIZE+1; y++)
    {
        for(int x=0; x<BOARD_X_SIZE+1; x++)
        {
            board[y][x] = Empty;
            boardOutline[y][x] = Normal;
        }
    }
}

void Board::draw()
{
    for(int y=1; y<=BOARD_Y_SIZE; y++)
    {
        // Get the center of the next row of circles
        float centerY = (spaceY + radius)*y + radius*(y-1);
        for(int x=1; x<=BOARD_X_SIZE; x++)
        {
            // Get the center of the next column of circles
            float centerX = (spaceX + radius)*x + radius*(x-1);
            // Set the color of the circle
            sf::Color fillColor;
            if(board[y][x] == Empty)
                fillColor = emptyColor;
            else if(board[y][x] == Red)
                fillColor = redColor;
            else
                fillColor = yellowColor;
            // Set the color of the tokens outline
            sf::Color outlineColor;
            if (boardOutline[y][x] == Highlight)
                outlineColor = highlightColor;
            else
                outlineColor = lineColor;
            // Draw the circle in the buffer
            myWindow.Draw(sf::Shape::Circle(centerX, centerY, radius,
                                    fillColor, outline, outlineColor));
        }
    }
}

Move Board::addTokenInColumn(unsigned int column, Token playerColor)
{
    // Search for empty spaces in the column, from bottom to top
    for(int i = BOARD_Y_SIZE; i>0; i--)
    {
        // add the token (red or yellow) if there is space in the column
        if(board[i][column] == Empty)
        {
            board[i][column] = playerColor;
            //Verify if the player has won
            if (isEndOfGame(i, column))
                return EndOfGame;
            else
                return Placed;
        }
    }
    // if it ends up here, it means the column is already full
    // and the token cannot be placed in the column
    return Full;
}

bool Board::isEndOfGame(const unsigned int y, const unsigned int x)
{
    // Search for combinations of 4 or more tokens of the same
    // color and highlight them
    // We create a temp variable to force the call of all the
    // four in a row searches, this way, all the combinations
    // of four or more tokens get highlighted
    bool t = false;
    t |= fourHorizontal(y, x);
    t |= fourVertical(y, x);
    t |= fourDiagonal(y, x);
    return t;
}

bool Board::fourHorizontal(const unsigned int y, const unsigned int x)
{
    // Search for combinations of 4 or more tokens of the same
    // color in a horizontal line
    Token tokenColor = board[y][x];
    int cnt = 1, i;
    // search right the same color tokens
    for(i = x + 1; board[y][i]==tokenColor; i++)
        cnt++;
    // search left the same color tokens
    for(i = x - 1; board[y][i]==tokenColor; i--)
        cnt++;
    // Highlight the winner row
    if(cnt>=4)
    {
        while(board[y][++i] == tokenColor)
                boardOutline[y][i] = Highlight;
        return true;
    }
    else
        return false;
}

bool Board::fourVertical(const unsigned int y, const unsigned int x)
{
    // Search for combinations of 4 or more tokens of the same
    // color in a vertical line
    Token tokenColor = board[y][x];
    int cnt = 1, i;
    // search down the same color tokens
    for(i = y + 1; board[i][x]==tokenColor; i++)
        cnt++;
    // search up the same color tokens
    for(i = y - 1; board[i][x]==tokenColor; i--)
        cnt++;
    // Highlight the winner row
    if(cnt>=4)
    {
        while(board[++i][x] == tokenColor)
                boardOutline[i][x] = Highlight;
        return true;
    }
    else
        return false;
}
bool Board::fourDiagonal(const unsigned int y, const unsigned int x)
{
    // Search for combinations of 4 or more tokens of the same
    // color in a vertical line
    Token tokenColor = board[y][x];
    bool t = false;
    int cnt = 1, i, j;
    // search down-left the same color tokens
    for(i = y + 1, j = x - 1; board[i][j]==tokenColor; i++, j--)
        cnt++;
    // search up-right the same color tokens
    for(i = y - 1, j = x + 1; board[i][j]==tokenColor; i--, j++)
        cnt++;
    // Highlight the winner diagonal
    if(cnt>=4)
    {
        while(board[++i][--j] == tokenColor)
                boardOutline[i][j] = Highlight;
        t = true;
    }
    cnt = 1;
    // search down-right the same color tokens
    for(i = y + 1, j = x + 1; board[i][j]==tokenColor; i++, j++)
        cnt++;
    // search up-left the same color tokens
    for(i = y - 1, j = x - 1; board[i][j]==tokenColor; i--, j--)
        cnt++;
    // Highlight the winner diagonal
    if(cnt>=4)
    {
        while(board[++i][++j] == tokenColor)
                boardOutline[i][j] = Highlight;
        return true;
    }
    else
        return t;
}

int Board::getWindowWidth()
{
    // Returns the current width of the board/window
    // We use this as the UI doesn't have a reference
    // to the window (App or myWindow)
    return myWindow.GetWidth();
}
